﻿// ConcurentServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS 1;
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1;
#include <iostream>
#include "Global.h"
#include "AcceptServer.h"
#include "DispathServer.h"
#include "GarbageCleaner.h"
#include "ConsolePipe.h"
#include "ResponseServer.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian"); // устанавлваем кодировку
	SetConsoleTitle(L"Concurrent Server"); // заголовок консольного окна
	cout << "ConcurrentServer started:" << endl;

	//устанавливаем номер tcp-порта, взяв его из параметров среды или оставляю неизменным значение по умолчанию
	if (argc > 1)
	{
		int tmp = atoi(argv[1]);
		if (tmp >= 0 && tmp <= 65535)
		{
			port = atoi(argv[1]);
			cout << "Used TCP-port:   " << port << ";" << endl;
		}
		else
		{
			cout << "Wrong TCP-port;" << endl;
		}
	}
	else
	{
		cout << "Used TCP-port:   " << port << "  (default);" << endl;
	}

	//устанавливаем номер udp-порта, взяв его из параметров среды или оставляю неизменным значение по умолчанию
	if (argc > 2)
	{
		int tmp = atoi(argv[2]);
		if (tmp >= 0 && tmp <= 65535)
		{
			uport = atoi(argv[2]);
			cout << "Used UDP-port:  " << uport << ";" << endl;
		}
		else
		{
			cout << "Wrong UDP-port;" << endl;
		}
	}
	else
	{
		cout << "Used UDP-port:   " << uport << "  (default);" << endl;
	}

	//устанавливаем имя загружаемой библиотеки
	if (argc > 3)
	{
		dllname = argv[3];
	}

	//устанваливаем имя именованного канала
	if (argc > 4)
	{
		npname = argv[4];
		cout << "CallNamedPipe:   " << npname << ";" << endl;
	}
	else
	{
		cout << "CallNamedPipe:   " << npname << "  (default);" << endl;
	}

	//устанваливаем позывной сервера
	if (argc > 5)
	{
		ucall = argv[5];
		cout << "Pozyvnoi:   " << ucall << ";" << endl;
	}
	else
	{
		cout << "Pozyvnoi:        " << ucall << "  (default);" << endl;
	}

	srand((unsigned)time(NULL));

	volatile TalkersCmd  cmd = Start; //команда управления сервером

	InitializeCriticalSection(&scListContact); //инициалзируем критическую секцию


	st1 = LoadLibrary(L"ServiceLibrary"); //загружаем dll
	vList.push_back(st1);
	ts1 = (HANDLE(*)(char*, LPVOID))GetProcAddress(st1, "SSS"); //импортируем функцию
	vArray.push_back(ts1);
	if (st1 == NULL) cout << "Fail DLL;" << endl;
	else cout << "Loaded DLL:      " << dllname << ";" << endl << endl;

	//создаем потоки
	hAcceptServer = CreateThread(NULL, NULL, AcceptServer, (LPVOID)&cmd, NULL, NULL); //соединение с сервером
	HANDLE hDispathServer = CreateThread(NULL, NULL, DispathServer, (LPVOID)&cmd, NULL, NULL); //обрабатывает сообщения, которые приходят и отправляет обратно
	HANDLE hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner, (LPVOID)&cmd, NULL, NULL); //удаление ненужных клиентов, которые не работают с сервером
	HANDLE hConsolePipe = CreateThread(NULL, NULL, ConsolePipe, (LPVOID)&cmd, NULL, NULL); //консоль управления сервером
	HANDLE hResponseServer = CreateThread(NULL, NULL, ResponseServer, (LPVOID)&cmd, NULL, NULL); //поиск клиентов через широковещательный запрос

	//устанавливаем приоритеты
	SetThreadPriority(hGarbageCleaner, THREAD_PRIORITY_BELOW_NORMAL);
	SetThreadPriority(hDispathServer, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hConsolePipe, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hResponseServer, THREAD_PRIORITY_ABOVE_NORMAL);
	SetThreadPriority(hAcceptServer, THREAD_PRIORITY_HIGHEST);


	//ждем завершения потоков
	WaitForSingleObject(hAcceptServer, INFINITE);
	WaitForSingleObject(hDispathServer, INFINITE);
	WaitForSingleObject(hGarbageCleaner, INFINITE);
	WaitForSingleObject(hConsolePipe, INFINITE);
	WaitForSingleObject(hResponseServer, INFINITE);

	//закрываем дескрипторы (освобождаем ресурсы)
	CloseHandle(hAcceptServer);
	CloseHandle(hDispathServer);
	CloseHandle(hGarbageCleaner);
	CloseHandle(hConsolePipe);
	CloseHandle(hResponseServer);

	DeleteCriticalSection(&scListContact); //удаляем критическую секцию

	FreeLibrary(st1); //выгружаем библиотеку

	system("pause");
	return 0;
}