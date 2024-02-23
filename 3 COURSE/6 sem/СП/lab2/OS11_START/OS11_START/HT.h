#pragma once
#include <Windows.h>

// API HT - программный интерфейс для доступа к НТ-хранилищу 
//          НТ-хранилище предназначено для хранения данных в ОП в формате ключ/значение
//          Персистестеность (сохранность) данных обеспечивается с помощью snapshot-менханизма 
//          Create - создать  и открыть HT-хранилище для использования   
//          Open   - открыть HT-хранилище для использования
//          Insert - создать элемент данных
//          Delete - удалить элемент данных    
//          Get    - читать  элемент данных
//          Update - изменить элемент данных
//          Snap   - выпонить snapshot
//          Close  - выполнить Snap и закрыть HT-хранилище для использования
//          GetLastError - получить сообщение о последней ошибке

#pragma pack(push, 1)
struct HTControl
{
	// структура хранения управляющих характеристик

	HTControl()
	{
		this->Capacity = 5000;
		this->SecSnapshotInterval = 10; // секунд
		this->MaxKeyLength = 4;
		this->MaxPayloadLength = 10;
	}

	HTControl(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength)
	{
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
	}

	int Capacity;               // емкость хранилища в количестве элементов 
	int SecSnapshotInterval;    // переодичность сохранения в сек. 
	int MaxKeyLength;           // максимальная длина ключа
	int MaxPayloadLength;       // максимальная длина данных
};
#pragma pack(pop)


#pragma pack(push, 1)
struct HTHANDLE    // блок управления HT
{
	HTHANDLE()
	{
		this->htc.Capacity = 5000;
		this->htc.SecSnapshotInterval = 10; // секунд
		this->htc.MaxKeyLength = 4;
		this->htc.MaxPayloadLength = 10;
		strcpy(this->FileName, ".\\temp\\HTspace.dat");
	}
	HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
	{
		this->htc.Capacity = Capacity;
		this->htc.SecSnapshotInterval = SecSnapshotInterval;
		this->htc.MaxKeyLength = MaxKeyLength;
		this->htc.MaxPayloadLength = MaxPayloadLength;
		strcpy(this->FileName, FileName);
	}
	HTControl htc; // структура хранения управляющих характеристик

	char    FileName[512];          // имя файла 
	HANDLE  File = NULL;                   // File HANDLE != 0, если файл открыт
	HANDLE  FileMapping = NULL;            // Mapping File HANDLE != 0, если mapping создан  
	LPVOID  Addr;                   // Addr != NULL, если mapview выполнен  
	char    LastErrorMessage[512];  // сообщение об последней ошибке или 0x00  
	time_t  lastsnaptime;           // дата последнего snap'a (time()) 

	CRITICAL_SECTION csection; // критическая секция доступа к snapshot-обработчику
	HANDLE snapthread = NULL; // дескриптор потока snapshot-механизма
	HANDLE snap_stop_Event = NULL; // дескриптор события управления остановом snapshot-механизма
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Element   // элемент 
{
	Element()
	{

	}
	Element(const void* key, int keylength) // for Get                                          
	{
		this->key = key;
		this->keylength = keylength;
		this->payload = NULL;
		this->payloadlength = 0;
	}
	Element(const void* key, int keylength, const void* payload, int payloadlength) // for Insert
	{
		this->key = key;
		this->keylength = keylength;
		this->payload = payload;
		this->payloadlength = payloadlength;
	}
	Element(Element* oldelement, const void* newpayload, int newpayloadlength) // for update
	{
		this->key = oldelement->key;
		this->keylength = oldelement->keylength;
		this->payload = newpayload;
		this->payloadlength = newpayloadlength;
	}
	const void*     key;                 // значение ключа 
	int             keylength;           // размер ключа
	const void*     payload;             // данные 
	int             payloadlength;       // размер данных
};
#pragma pack(pop)

extern "C" __declspec(dllimport) HTHANDLE*  Create   //  создать HT             
(
	int	  Capacity,					   // емкость хранилища
	int   SecSnapshotInterval,		   // переодичность сохранения в сек.
	int   MaxKeyLength,                // максимальный размер ключа
	int   MaxPayloadLength,            // максимальный размер данных
	const char  FileName[512]          // имя файла 
); 	// != NULL успешное завершение  

extern "C" __declspec(dllimport) HTHANDLE*   Open     //  открыть HT - через OpenFileMapping()
(
	const char FileName[512],
	char* resultInfo
); 	// != NULL успешное завершение 

extern "C" __declspec(dllimport) BOOL Snap         // выполнить Snapshot
(
	const HTHANDLE*    hthandle           // управление HT (File, FileMapping)
);


extern "C" __declspec(dllimport) BOOL Close        // Snap и закрыть HT  и  очистить HTHANDLE
(
	const HTHANDLE*    hthandle, // управление HT (File, FileMapping)
	char* resultInfo 
);	//  == TRUE успешное завершение   


extern "C" __declspec(dllimport) BOOL Insert      // добавить элемент в хранилище
(
	const HTHANDLE* hthandle,            // управление HT
	const Element*  element              // элемент
);	//  == TRUE успешное завершение 


extern "C" __declspec(dllimport) BOOL Delete      // удалить элемент в хранилище
(
	const HTHANDLE* hthandle,            // управление HT (ключ)
	const Element*  element              // элемент 
);	//  == TRUE успешное завершение 

extern "C" __declspec(dllimport) Element* Get     //  читать элемент в хранилище
(
	const HTHANDLE* hthandle,            // управление HT
	const Element*  element              // элемент 
); 	//  != NULL успешное завершение 


extern "C" __declspec(dllimport) BOOL Update     //  именить элемент в хранилище
(
	const HTHANDLE* hthandle,            // управление HT
	Element*  oldelement,          // старый элемент (ключ, размер ключа)
	const void*     newpayload,          // новые данные  
	int             newpayloadlength     // размер новых данных
); 	//  != NULL успешное завершение 

char* GetLastError  // получить сообщение о последней ошибке
(
	HTHANDLE* ht                         // управление HT
);

extern "C" __declspec(dllimport) void print                               // распечатать элемент 
(
	const Element*  element              // элемент 
);

//extern "C" __declspec(dllimport) 
void SnapThread
(
	void* pAddr
);