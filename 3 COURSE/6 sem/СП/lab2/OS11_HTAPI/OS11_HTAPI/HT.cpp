#include "pch.h"

#include "HT.h"
#include <Windows.h>
#include <time.h>
#include "HTSupport.h"
#include <stdio.h>
#include <stdlib.h>

char commonErrorDescription[2048] = "";

const char fileMappingName[] = "Local\\HTFMAP";

// поддержка синхронизации доступа к хранилищу разными процессами
HANDLE hMutex = NULL;
const char hMutexName[] = "Local\\HTFMAP_MUTEX";

extern "C" __declspec(dllexport) HTHANDLE* Create(
	int	  Capacity,					   // емкость хранилища
	int   SecSnapshotInterval,		   // переодичность сохранения в сек.
	int   MaxKeyLength,                // максимальный размер ключа
	int   MaxPayloadLength,            // максимальный размер данных
	const char  FileName[512]          // имя файла 
)
{
	HTHANDLE* ht = NULL;

	try
	{
		// 

		if (hMutex == NULL) hMutex = CreateMutex(NULL, false, hMutexName); 

		//

		ht = new HTHANDLE(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName);

		InitializeCriticalSection(&ht->csection);

		ht->File = CreateFile(FileName,
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (ht->File == INVALID_HANDLE_VALUE)
		{
			strcpy(ht->LastErrorMessage, "ошибка создания или открытия файла");
			throw "ошибка создания или открытия файла";
		}

		// предразместим память для всего хранилища
		DWORD HTMaximumSize = sizeof(HTControl) + Capacity * (MaxKeyLength + MaxPayloadLength);

		// создает или открывает именованный или безымянный объект отображенного в памяти (проецируемого) файла для заданного файла.
		ht->FileMapping = CreateFileMapping(ht->File,
			NULL,
			PAGE_READWRITE,
			0,
			HTMaximumSize,
			fileMappingName
		);
		if (ht->FileMapping == NULL)
		{
			strcpy(ht->LastErrorMessage, "ошибка создания отображения файла в памяти");
			throw "ошибка создания отображения файла в памяти";
		}

		// MapViewOfFile отображает представление проецируемого файла в адресное пространство вызывающего процесса

		ht->Addr = MapViewOfFile(ht->FileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		// процеируемый объект (файл), доступ к операциям чтения-записи, старшее слово смещения, младшее, число отображаемый байтов (0 - весь файл)

		if (ht->Addr == NULL)
		{
			strcpy(ht->LastErrorMessage, "ошибка сопоставления представления файла с адресным пространством процесса");
			throw "ошибка сопоставления представления файла с адресным пространством процесса";
		}

		time(&(ht->lastsnaptime)); 		// time() возвращает текущее время системы как значение time_t

		// сохраним в начало памяти (файла) данные нашей управляющей структуры

		memcpy(ht->Addr, (const void*)(&(ht->htc)), sizeof(HTControl));

		// 

		ht->snap_stop_Event = CreateEvent(NULL, // не наследуется дочерними процессами
			false, // auto-reset event
			false,
			NULL);

		// запуск snap-обработки для экземпляра хранилища
		// CreateThread() дескриптор защиты, начальный размер стека, функция потока, параметр потока, опции создания, идентификатор потока

		ht->snapthread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&SnapThread, (LPVOID)ht, NULL, NULL);

	}
	catch (const char* em)
	{
		strcpy(commonErrorDescription, "отказ - исключение в Create(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}

		delete[] ht;
		ht = NULL;
	}

	return ht;
}

extern "C" __declspec(dllexport) BOOL Close(const HTHANDLE* hthandle, char* resultInfo)
{
	bool retval = true;

	try
	{
		if (hthandle == NULL)
		{
			strcpy(resultInfo, "попытка закрытия несуществующего объекта");
			throw "попытка закрытия несуществующего объекта";
		}

		Snap(hthandle);

		if (hthandle->Addr != NULL)
			if (!UnmapViewOfFile(hthandle->Addr)) throw "ошибка закрытия отображения файла в памяти";

		if (hthandle->FileMapping != NULL)
			if (!CloseHandle(hthandle->FileMapping)) throw "ошибка закрытия дескриптора отображения файла в памяти";

		if (hthandle->File != NULL)
			if (!CloseHandle(hthandle->File)) throw "ошибка закрытия дескриптора файла";

		// требуем останова потока snap
		if (hthandle->snap_stop_Event != NULL)
			SetEvent(hthandle->snap_stop_Event); // переводим событие в сигнальное состояние

		if (hthandle->snapthread != NULL)
		{ 
			DWORD wres = WaitForSingleObject(hthandle->snapthread, 3000); // 3 секунды ждем завершения работы потока snap
			if (wres == WAIT_TIMEOUT) TerminateThread(hthandle->snapthread, -1); // не дождались самостоятельного завершения потоком своей работы - принудительно прерываем поток
			if (!CloseHandle(hthandle->snapthread)) throw "ошибка закрытия дескриптора потока";
		}

		DeleteCriticalSection((LPCRITICAL_SECTION)&(hthandle->csection));

		if (hthandle->snap_stop_Event != NULL)
			if (!CloseHandle(hthandle->snap_stop_Event)) throw "ошибка закрытия дескриптора события";

		// закрытие объекта синхронизации доступа к хранилищу
		if (hMutex != NULL)
			if (!CloseHandle(hMutex)) throw "ошибка закрытия объекта синхронизации доступа к хранилищу";

	}
	catch (const char* em)
	{
		retval = false;
		strcpy(commonErrorDescription, "отказ - исключение в Close(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	return retval;
}

// ИСПОЛЬЗУЕТСЯ ОТКРЫТАЯ АДРЕСАЦИЯ
extern "C" __declspec(dllexport) BOOL Insert(const HTHANDLE* hthandle, const Element*  element)
{
	bool result = true;

	try
	{
		// синхронизация мультипроцессного доступа к хранилищу
		WaitForSingleObject(hMutex, INFINITE); // ждем освобождения доступа к хранилищу
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // сбрасываем предыдущую диагностику

		// проверка на ограничение максимальной размерности ключа и полезных данных

		if (element->keylength > hthandle->htc.MaxKeyLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "превышена максимальная размерность ключа");
			throw "превышена максимальная размерность ключа";
		}

		if (element->payloadlength > hthandle->htc.MaxPayloadLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "превышена максимальная размерность полезных данных");
			throw "превышена максимальная размерность полезных данных";
		}

		// проверяем по ключу наличие дубликата в хранилище

		if (Get(hthandle, new Element(element->key, element->keylength)) != NULL)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "обнаружен дубликат ключа в хранилище - отказ добавления элемента");
			throw "обнаружен дубликат ключа в хранилище - отказ добавления элемента";
		}

		char* memfile = (char*)hthandle->Addr;

		// берем хеш от значения ключа
		int idx = BuildHash(element->key, strlen((const char*)(element->key)) + 1);

		// если hash больше количества слотов в хранилище, то начинаем обработку с 1го слота
		idx = (idx <= hthandle->htc.Capacity ? idx : 1); // номер текущего слота	

		if (*(memfile + sizeof(HTControl) + (idx - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength)) == '\0') { // слот не занят

			memcpy(memfile + sizeof(HTControl) + (idx - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), element->key, element->keylength);
			memcpy(memfile + sizeof(HTControl) + (idx - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, element->payload, element->payloadlength);

		}

		else { // слот занят - ищем первый свободный слот начиная с данного

			int slotcounter = 0; // счетчик просмотренных слотов

			int k = idx;
			while (*(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength)) != '\0') {

				if (++k > hthandle->htc.Capacity) k = 1; // при достижении последнего слота - переходим в начало

				if (++slotcounter >= hthandle->htc.Capacity)
				{
					// хранилище переполнено

					strcpy((char*)(hthandle->LastErrorMessage), "невозможно вставить элемент в храналище - хранилище заполнено");
					throw "невозможно вставить элемент в храналище - хранилище заполнено";

				}
			}

			// теперь k хранит номер первого пустого слота
			memcpy(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), element->key, element->keylength);
			memcpy(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, element->payload, element->payloadlength);

		}

	}
	catch (const char* em)
	{
		if (hMutex != NULL) ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

		result = false;
		strcpy(commonErrorDescription, "отказ - исключение в Insert(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}

	}

	if (hMutex != NULL) ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

	return result;
}

extern "C" __declspec(dllexport) Element* Get(const HTHANDLE* hthandle, const Element* element)
{
	Element* newelem = NULL;

	try
	{
		// синхронизация мультипроцессного доступа к хранилищу
		// WaitForSingleObject(hMutex, INFINITE); // ждем освобождения доступа к хранилищу
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // сбрасываем предыдущую диагностику

		// проверка на ограничение максимальной размерности ключа

		if (element->keylength > hthandle->htc.MaxKeyLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "превышена максимальная размерность ключа");
			throw "превышена максимальная размерность ключа";
		}

		// берем хеш от значения ключа
		int idx = BuildHash(element->key, strlen((const char*)(element->key)) + 1);

		char* memfile = (char*)hthandle->Addr;

		//
		// если hash больше количества слотов в хранилище, то начинаем обработку с 1го слота
		int k = (idx <= hthandle->htc.Capacity ? idx : 1); // номер текущего слота	
		int slotcheck = 0; // кол-во просмотренных слотов

		do {

			// до тех пока значения ключа в слоте не совпадет с требуемым либо не будут просмотрены все слоты

			char* slotkey = new char[hthandle->htc.MaxKeyLength];
			ZeroMemory(slotkey, hthandle->htc.MaxKeyLength);

			memcpy(slotkey, memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), hthandle->htc.MaxKeyLength);

			if (strcmp(slotkey, (const char *)element->key) == 0) { // найден элемент по ключу

				newelem = new Element(element->key, element->keylength);

				newelem->payload = new char[hthandle->htc.MaxPayloadLength];
				ZeroMemory((void *)(newelem->payload), hthandle->htc.MaxPayloadLength);
				memcpy((void *)(newelem->payload), memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, hthandle->htc.MaxPayloadLength);
				newelem->payloadlength = strlen((char *)(newelem->payload)) + 1; // нулевой байт (символ конца строки) также часть полезных данных

				break;

			}

			if (++k > hthandle->htc.Capacity) k = 1; // при достижении последнего слота - переходим в начало

		} while (++slotcheck != hthandle->htc.Capacity);

		if (newelem == NULL)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "элемент не найден");
			throw "элемент не найден";
		}
	}
	catch (const char* em)
	{
		newelem = NULL;
		
		strcpy(commonErrorDescription, "отказ - исключение в Get(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}


	return newelem;
}

extern "C" __declspec(dllexport) BOOL Update(const HTHANDLE* hthandle, Element* oldelement, const void* newpayload, int newpayloadlength)
{
	bool result = false;

	Element* newelem = new Element(oldelement, newpayload, newpayloadlength);

	try
	{
		// синхронизация мультипроцессного доступа к хранилищу
		WaitForSingleObject(hMutex, INFINITE); // ждем освобождения доступа к хранилищу
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // сбрасываем предыдущую диагностику

		// проверка на ограничение максимальной размерности полезных данных

		if (newelem->payloadlength > hthandle->htc.MaxPayloadLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "превышена максимальная размерность полезных данных");
			throw "превышена максимальная размерность полезных данных";
		}

		// берем хеш от значения ключа
		int idx = BuildHash(newelem->key, strlen((const char*)(newelem->key)) + 1);

		char* memfile = (char*)hthandle->Addr;

		// ищем требуемый слот по значению ключа

		// если hash больше количества слотов в хранилище, то начинаем обработку с 1го слота
		int k = (idx <= hthandle->htc.Capacity ? idx : 1); // номер текущего слота		

		int slotcheck = 0; // кол-во просмотренных слотов

		do {

			// до тех пока значения ключа в слоте не совпадет с требуемым либо не будут просмотрены все слоты

			char* slotkey = new char[hthandle->htc.MaxKeyLength];
			ZeroMemory(slotkey, hthandle->htc.MaxKeyLength);

			memcpy(slotkey, memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), hthandle->htc.MaxKeyLength);

			if (strcmp(slotkey, (const char *)oldelement->key) == 0) { // найден элемент по ключу

				memcpy(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, newelem->payload, newelem->payloadlength);

				result = true; // элемент найден и обновлен

				break; // while

			} // найден элемент по ключу

			if (++k > hthandle->htc.Capacity) k = 1; // при достижении последнего слота - переходим в начало

		} while (++slotcheck != hthandle->htc.Capacity);

		if (!result) // элемент для обновления не найден
		{
			strcpy((char*)(hthandle->LastErrorMessage), "попытка обновления несуществующего элемента");
			throw "попытка обновления несуществующего элемента";
		}

	}
	catch (const char* em)
	{
		if (hMutex != NULL) ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

		result = false;

		strcpy(commonErrorDescription, "отказ - исключение в Update(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	if (hMutex != NULL) ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

	return result;
}

extern "C" __declspec(dllexport) BOOL Delete(const HTHANDLE* hthandle, const Element*  element)
{
	bool result = false;

	try
	{
		// синхронизация мультипроцессного доступа к хранилищу
		WaitForSingleObject(hMutex, INFINITE); // ждем освобождения доступа к хранилищу
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // сбрасываем предыдущую диагностику

		// проверка на ограничение максимальной размерности ключа
		if (element->keylength > hthandle->htc.MaxKeyLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "превышена максимальная размерность ключа");
			throw "превышена максимальная размерность ключа";
		}

		// берем хеш от значения ключа
		int idx = BuildHash(element->key, strlen((const char*)(element->key)) + 1);

		char* memfile = (char*)hthandle->Addr;

		//

		// ищем требуемый слот по значению ключа

		// если hash больше количества слотов в хранилище, то начинаем обработку с 1го слота
		int k = (idx <= hthandle->htc.Capacity ? idx : 1); // номер текущего слота	

		int slotcheck = 0; // кол-во просмотренных слотов

		do {

			// до тех пока значения ключа в слоте не совпадет с требуемым либо не будут просмотрены все слоты

			char* slotkey = new char[hthandle->htc.MaxKeyLength];
			ZeroMemory(slotkey, hthandle->htc.MaxKeyLength);

			memcpy(slotkey, memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), hthandle->htc.MaxKeyLength);

			if (strcmp(slotkey, (const char *)element->key) == 0) { // найден элемент по ключу

				ZeroMemory(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), (hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength));

				result = true; // элемент найден и удален

				break; // while

			} // // найден элемент по ключу

			if (++k > hthandle->htc.Capacity) k = 1; // при достижении последнего слота - переходим в начало

		} while (++slotcheck != hthandle->htc.Capacity);

		if (!result) // элемент для удаления не найден
		{
			strcpy((char*)(hthandle->LastErrorMessage), "попытка удаления несуществующего элемента");
			throw "попытка удаления несуществующего элемента";
		}

	}
	catch (const char* em)
	{
		if (hMutex != NULL) ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

		result = false;

		strcpy(commonErrorDescription, "отказ - исключение в Delete(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	if (hMutex != NULL) ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

	return result;
}

extern "C" __declspec(dllexport) HTHANDLE* Open(const char FileName[512], char* resultInfo)
{
	HTHANDLE* ht = NULL;

	try
	{
		//

		if (hMutex == NULL) hMutex = OpenMutex(SYNCHRONIZE, false, hMutexName);

		//

		HANDLE f = CreateFile(FileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (f == INVALID_HANDLE_VALUE)
		{
			strcpy(resultInfo, "ошибка открытия файла хранилища для чтения");
			throw "ошибка открытия файла хранилища для чтения";
		}

		char buffparams[sizeof(HTControl)] = "";

		// считываем в буфер параметры хранилища
		DWORD numberOfBytesRead = 0;

		if (!ReadFile(f, buffparams, sizeof(buffparams), &numberOfBytesRead, NULL))
		{
			strcpy(resultInfo, "ошибка чтения файла");
			throw "ошибка чтения файла";
		}
		// закрываем дескриптор файла
		//CloseHandle(f);

		// получаем структуру хранения управляющих характеристик из прочитанного буфера
		HTControl htc = *((HTControl *)buffparams);

		ht = new HTHANDLE(htc.Capacity, htc.SecSnapshotInterval, htc.MaxKeyLength, htc.MaxPayloadLength, FileName);

		InitializeCriticalSection(&ht->csection);
		ht->File = f;

		// открываем существующий File Mapping
		ht->FileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, fileMappingName);

		if (ht->FileMapping == NULL)
		{
			strcpy(ht->LastErrorMessage, "ошибка открытия отображения файла в памяти");
			throw "ошибка открытия отображения файла в памяти";
		}

		ht->Addr = MapViewOfFile(ht->FileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		if (ht->Addr == NULL)
		{
			strcpy(ht->LastErrorMessage, "ошибка сопоставления представления файла с адресным пространством процесса");
			throw "ошибка сопоставления представления файла с адресным пространством процесса";
		}

		time(&(ht->lastsnaptime)); 		// time() возвращает текущее время системы как значение time_t

		ht->snap_stop_Event = CreateEvent(NULL, // атрибуты защиты
			false, // auto-reset event
			false, // в несигнальном состоянии
			NULL); // имя

		// ht->snapthread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&SnapThread, (LPVOID)ht, NULL, NULL);

	}
	catch (const char* em)
	{
		strcpy(commonErrorDescription, "отказ - исключение в Open(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	return ht;
}

extern "C" __declspec(dllexport) BOOL Snap(const HTHANDLE* hthandle)
{
	// синхронизация мультипроцессного доступа к хранилищу
	// WaitForSingleObject(hMutex, INFINITE); // ждем освобождения доступа к хранилищу
	//

	EnterCriticalSection((LPCRITICAL_SECTION)(&hthandle->csection));

	bool retval = true;
	try
	{
		// производим запись на диск диапазона байт в сопоставленном представлении файла

		if (!FlushViewOfFile(hthandle->Addr, sizeof(HTControl) + hthandle->htc.Capacity * (hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength)))
		{
			throw "ошибка вызова FlushViewOfFile()";
		}

		// запишем все буферные данные файла хранилища в файл

		if (!FlushFileBuffers(hthandle->File))
		{
			throw "ошибка вызова FlushFileBuffers()";
		}

		// отметим время snapshot

		time((time_t*)(&(hthandle->lastsnaptime))); 		// time() возвращает текущее время системы как значение time_t
		printf("\nspanshot в %s", ctime(&(hthandle->lastsnaptime)));
	}
	catch (const char* em)
	{
		strcpy(commonErrorDescription, "отказ - исключение в Snap(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\nкод ошибки: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}

		strcpy(((HTHANDLE*)hthandle)->LastErrorMessage, "отказ при выполнении snapshot хранилища");
	}

	LeaveCriticalSection((LPCRITICAL_SECTION)(&hthandle->csection));

	// ReleaseMutex(hMutex); // освобождаем доступ к хранилищу

	return retval;
}

extern "C" __declspec(dllexport) void print(const Element* element)
{
	printf("ключ: %s значение: %s", element->key, element->payload);
}
 
// extern "C" __declspec(dllexport) 
void SnapThread(void* paramAddr)
{
	// потоковая процедура (выполняется в рамках отдельного потока) - snap-обработка для экземпляра хранилища

	while (true)
	{
		Snap((HTHANDLE*)paramAddr);

		if (WaitForSingleObject(((HTHANDLE*)paramAddr)->snap_stop_Event, 100) == WAIT_OBJECT_0)
		{
			// поступило событие о прекращении работы потока, выходим из цикла
			break;
		}

		Sleep(((HTHANDLE*)paramAddr)->htc.SecSnapshotInterval * 1000); // мсек
	}

}

__declspec(dllexport) char* GetLastError(HTHANDLE* ht)
{
	return ht->LastErrorMessage;
}

__declspec(dllexport) char* GetLastError(HTHANDLE* ht, int htlen)
{
	return ht->LastErrorMessage;
}