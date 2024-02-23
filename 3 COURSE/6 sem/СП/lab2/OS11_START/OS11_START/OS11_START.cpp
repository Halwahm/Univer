// HT-Storage Start filename=xxxxx, snapshotinterval=xx capacity = xxxx, maxkeylength = xxx, maxdatalength = xxx

#pragma comment(lib, "D:\\My Files\\Univer\\3 COURSE\\6 sem\\СП\\lab2\\OS11_START\\OS11_START\\OS11HTAPI.lib")

#include <iostream>
#include <conio.h>
#include <ctime>
#include "HT.h"

using namespace std;

// поддержка управления стартом хранилища
HANDLE hMutexStart = NULL;
const char hMutexStartName[] = "Local\\HTFMAP_STARTED_MUTEX";


int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "ru");

	if (argc != 2) // + 1 параметр как имя самой программы
	{
		cout << endl << "ошибочное число параметров командной строки: " << endl << endl;
		cout << "пример: OS11_START.exe filename";
		return -1;
	}

	HTHANDLE* ht = NULL;

	char errorInfo[255] = "";

	try
	{
		HANDLE f = CreateFile(argv[1],
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (f == INVALID_HANDLE_VALUE)
		{
			strcpy(errorInfo, "ошибка открытия файла хранилища для чтения");
			throw "ошибка открытия файла хранилища для чтения";
		}

		char buffparams[sizeof(HTControl)] = "";

		// считываем в буфер параметры хранилища
		DWORD numberOfBytesRead = 0;

		if (!ReadFile(f, buffparams, sizeof(buffparams), &numberOfBytesRead, NULL))
		{
			strcpy(errorInfo, "ошибка чтения файла");
			throw "ошибка чтения файла";
		}
		// закрываем дескриптор файла
		CloseHandle(f);

		// получаем структуру хранения управляющих характеристик из прочитанного буфера
		HTControl htc = *((HTControl *)buffparams);

		
		int htcapacity = htc.Capacity;
		int secsnapshot = htc.SecSnapshotInterval;
		int maxkeylen = htc.MaxKeyLength;
		int maxpayloadlen = htc.MaxPayloadLength;

		cout << "HT-Storage Start filename= " << argv[1] << ", snapshotinterval = " << secsnapshot << ", capacity = " << htcapacity << ", maxkeylength = " << maxkeylen << ", maxdatalength = " << maxpayloadlen;

		ht = Create(htcapacity, secsnapshot, maxkeylen, maxpayloadlen, argv[1]);

		// разрешаем другим процессам доступ к хранилищу
		if (hMutexStart == NULL) hMutexStart = CreateMutex(NULL, false, hMutexStartName);

		cout << endl << endl  << "нажмите любую клавишу для завершения работы приложения" << endl << endl;

		while (true)
		{
			// printf("\nсостояние хранилища: стартовано. последний spanshot в %s", ctime(&(ht->lastsnaptime)));
			Sleep(secsnapshot);
			if (_getch()) break;
		}


		// выполняет сохранение образа и завершает работу

		if (!Close(ht, errorInfo))
		{
			strcpy(errorInfo, "ошибка закрытия экземпляра хранилища");
			throw "ошибка закрытия экземпляра хранилища";
		}

	}
	catch (...)
	{
		cout << errorInfo << endl;
	}

	CloseHandle(hMutexStart); // закрываем доступ других процессов к хранилищу

}
