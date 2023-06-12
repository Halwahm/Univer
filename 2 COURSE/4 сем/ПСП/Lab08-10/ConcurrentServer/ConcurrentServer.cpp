#include "stdafx.h"
#include "Winsock2.h"
#include "ErrorFunctions.h"
#include <string>
#include <list>
#include <time.h>
#include <iostream>

#define AS_SQ 10
#define IP_SERVER "192.168.134.8"
using namespace std;

SOCKET sS;
int serverPort;
char dllName[50];
char namedPipeName[10];

volatile long connectionCount = 0; // чтобы компилятор не оптимизировал нужно чтобы разные потоки получали один кол-во памяти при обраб-ке этих переменных
volatile long sayNoCount = 0; // long чтобы переменная была кратна четырем (выровнена на границу слова)
volatile long successConnections = 0;
volatile long currentActiveConnections = 0;

HANDLE hAcceptServer, hConsolePipe, hGarbageCleaner, hDispatchServer, hResponseServer;
HANDLE hClientConnectedEvent = CreateEvent(NULL,
	FALSE,
	FALSE,
	L"ClientConnected");;

DWORD WINAPI AcceptServer(LPVOID pPrm);
DWORD WINAPI ConsolePipe(LPVOID pPrm);
DWORD WINAPI GarbageCleaner(LPVOID pPrm);
DWORD WINAPI DispatchServer(LPVOID pPrm);
DWORD WINAPI ResponseServer(LPVOID pPrm);

CRITICAL_SECTION scListContact; // содержит всю информацию о подключ клиента

enum TalkersCommand {
	START, STOP, EXIT, STATISTICS, WAIT, SHUTDOWN, GETCOMMAND, LOAD_LIB, UNLOAD_LIB
};
volatile TalkersCommand  previousCommand = GETCOMMAND; // предыдущая команда которая пришла с консоли

#pragma region Contact
struct Contact
{
	enum TE {
		EMPTY,
		ACCEPT,
		CONTACT
	}    type;
	enum ST {
		WORK,
		ABORT,
		TIMEOUT,
		FINISH
	}      sthread;

	SOCKET      s;
	SOCKADDR_IN prms;
	int         lprms;
	HANDLE      hthread;
	HANDLE      htimer;
	HANDLE		serverHThtead;

	char msg[50];
	char srvname[15];

	Contact(TE t = EMPTY, const char* namesrv = "")
	{
		ZeroMemory(&prms, sizeof(SOCKADDR_IN));
		lprms = sizeof(SOCKADDR_IN);
		type = t;
		strcpy(srvname, namesrv);
		msg[0] = 0x00;
	};

	void SetST(ST sth, const char* m = "")
	{
		sthread = sth;
		strcpy(msg, m);
	}
};
typedef list<Contact> ListContact;
#pragma endregion

ListContact contacts;

bool  GetRequestFromClient(char* name, short port, SOCKADDR_IN* from, int* flen);

bool AcceptCycle(int sq) // принятие сокета и добавление его в ListContact
{
	bool rc = false;
	Contact c(Contact::ACCEPT, "EchoServer");
	while (sq-- > 0 && !rc)
	{
		if ((c.s = accept(sS, (sockaddr*)&c.prms, &c.lprms)) == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
				throw  SetErrorMsgText("accept:", WSAGetLastError());
		}
		else
		{
			rc = true;
			EnterCriticalSection(&scListContact); // тут использована крит секция чтобы одновременно не добавлялось (Accept) и удалялось (Garbage)
			contacts.push_front(c); // добавление сокета в ListContact (список подключения)
			LeaveCriticalSection(&scListContact);
			puts("contact connected");
			InterlockedIncrement(&connectionCount); // увеличть на единицу. Атомарные ф-ии нужны чтобы выполнять дей-я над переменными в разных потоках последоватьно. потому что если делать другие типы синхр-ии то может быть дорого
		}
	}
	return rc;
};

void openSocket() { // для конфигурации и настройки сокета
	SOCKADDR_IN serv;
	sockaddr_in clnt;
	u_long nonblk = 1; // не блокируем сокет

	if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
		throw  SetErrorMsgText("socket:", WSAGetLastError());

	int lclnt = sizeof(clnt);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(serverPort);
	serv.sin_addr.s_addr = INADDR_ANY;

	if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
		throw  SetErrorMsgText("bind:", WSAGetLastError());
	if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
		throw  SetErrorMsgText("listen:", WSAGetLastError());
	if (ioctlsocket(sS, FIONBIO, &nonblk) == SOCKET_ERROR) // переключает сокет в режим без блокировки. это нужно для того чтобы accept не останавливал потоr до получения сокета. это нужно для того, если мы бы бахнули accept, поток находится в ожид состоянии, потом stop (не будет выполняться пока не закончится д-е accept), потом введенная команда нового сокета может затереть stop)
		throw SetErrorMsgText("ioctlsocket:", WSAGetLastError());
}

void closeSocket() { // закрывает сокет
	if (closesocket(sS) == SOCKET_ERROR)
		throw  SetErrorMsgText("closesocket:", WSAGetLastError());
}

void CommandsCycle(TalkersCommand& cmd) // Для обработки команд управления (которые пришли с RConsole кроме stastics) в рамках потока AcceptServer
{
	int  sq = 0; // максимальным количеством итераций выполнения функции accept
	while (cmd != EXIT)
	{
		switch (cmd)
		{
		case START: cmd = GETCOMMAND;
			if (previousCommand != START) {
				sq = AS_SQ;
				puts("Start command");
				openSocket();
				previousCommand = START;
			}
			else puts("start already in use");
			break;
		case STOP:  cmd = GETCOMMAND;
			if (previousCommand != STOP) {
				sq = 0;
				puts("Stop command");
				closeSocket();
				previousCommand = STOP;
			}
			else puts("stop already in use");

			break;
		case WAIT:  cmd = GETCOMMAND;
			sq = 0;
			puts("Wait command\n" \
				"socket closed for waiting other clients");
			closeSocket();
			while (contacts.size() != 0);
			printf("size of contacts %d\n", contacts.size());
			cmd = START;
			previousCommand = WAIT;
			puts("socket is open");

			break;
		case SHUTDOWN:
			sq = 0;
			puts("SHUTDOWN command\n" \
				"........shutting down...........");
			closeSocket();
			while (contacts.size() != 0);
			printf("size of contacts %d\n", contacts.size());
			cmd = EXIT;
			break;
		case GETCOMMAND:  cmd = GETCOMMAND;

			break;
		};
		if (cmd != STOP) {

			if (AcceptCycle(sq)) // sq - максимальным количеством итераций   выполнения функции accept (в режиме без блокировки) 
			{
				cmd = GETCOMMAND;
				SetEvent(hClientConnectedEvent); // Перевести событие в сигнальное состояние 
			}
			else SleepEx(0, TRUE); // асинхронно ожидать другие потоки
		}
	};
};

DWORD WINAPI AcceptServer(LPVOID pPrm) // клиент осуществляет процедуру подключения через этот поток потом идет запуск потока DispatchServer
{
	DWORD rc = 0;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());
		CommandsCycle(*((TalkersCommand*)pPrm)); // обработка команды с консоли упр-я

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		printf("\n%s", errorMsgText.c_str());
	}
	puts("shutdown acceptServer");
	ExitThread(rc);
}

TalkersCommand set_param(char* param) {
	if (!strcmp(param, "start")) return START;
	if (!strcmp(param, "stop")) return STOP;
	if (!strcmp(param, "exit")) return EXIT;
	if (!strcmp(param, "wait")) return WAIT;
	if (!strcmp(param, "shutdown")) return SHUTDOWN;
	if (!strcmp(param, "statistics")) return STATISTICS;
	if (!strcmp(param, "getcommand")) return GETCOMMAND;
	if (strstr(param, "UNLOAD_LIB")) return UNLOAD_LIB;
	if (strstr(param, "LOAD_LIB")) return LOAD_LIB;
}
typedef void* (*FUNCTION)(char*, LPVOID);
FUNCTION ts;

volatile bool is_load_library = false;
std::list<HMODULE> list_of_dlls;
std::list<FUNCTION> list_of_functions;

HMODULE st;
SOCKET sSUDP;

DWORD WINAPI ConsolePipe(LPVOID pPrm) // ввод команд управления, введенных оператором удаленной консоли RConsole,  а также вывод на консоль RConsole  простейших диагностических сообщений.
{
	DWORD rc = 0;
	char rbuf[100];
	DWORD dwRead, dwWrite;
	HANDLE hPipe;
	try
	{
		char namedPipeConnectionString[50];
		sprintf(namedPipeConnectionString, "\\\\.\\pipe\\%s", namedPipeName);
		if ((hPipe = CreateNamedPipeA(namedPipeConnectionString, // создание именованного канала
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_WAIT,
			1, NULL, NULL,
			INFINITE, NULL)) == INVALID_HANDLE_VALUE)
			throw SetPipeError("create:", GetLastError());
		if (!ConnectNamedPipe(hPipe, NULL))
			throw SetPipeError("connect:", GetLastError());
		TalkersCommand& param = *((TalkersCommand*)pPrm);
		
		while (param != EXIT) {
			puts("Connecting to Named Pipe Client ...");
			ConnectNamedPipe(hPipe, NULL);
			while (ReadFile(hPipe, rbuf, sizeof(rbuf), &dwRead, NULL))
			{
				printf("main client message:  %s\n", rbuf);
				param = set_param(rbuf);
				if (param == LOAD_LIB)
				{
					is_load_library = true;
					EnterCriticalSection(&scListContact); // крит секция чтобы не удалялось добавлялось одновременно
					list_of_dlls.push_front(LoadLibraryA(strstr(rbuf, "Win")));
					list_of_functions.push_front((FUNCTION)GetProcAddress(list_of_dlls.front(), "SSS"));
					LeaveCriticalSection(&scListContact);
				}
				else if (param == UNLOAD_LIB)
				{
					is_load_library = false;
					EnterCriticalSection(&scListContact);
					list_of_dlls.pop_front();
					list_of_functions.pop_front();
					LeaveCriticalSection(&scListContact);
				}
				if (param == STATISTICS)
				{
					char sendStastistics[200];
					sprintf(sendStastistics, "\nStatistics\n"\
						"count of connectings :    %d\n" \
						"count of denides:        %d\n" \
						"success end:             %d\n" \
						"count of active connections : %d\n" \
						"", connectionCount, sayNoCount, successConnections, contacts.size());
					WriteFile(hPipe, sendStastistics, sizeof(sendStastistics), &dwWrite, NULL);
				}
				
				if (param != STATISTICS)
					WriteFile(hPipe, rbuf, strlen(rbuf) + 1, &dwWrite, NULL);
				if (param == EXIT || param == SHUTDOWN) {
					break;
				}
			}
			DisconnectNamedPipe(hPipe);
			if (param == EXIT || param == SHUTDOWN) {
				break;
			}
		}
	}
	catch (string ErrorPipeText)
	{
		printf("\n%s", ErrorPipeText.c_str());
		return -1;
	}
	CloseHandle(hPipe);
	puts("shutdown ConsolePipe");
	ExitThread(rc);
}

DWORD WINAPI GarbageCleaner(LPVOID pPrm) // параметр это область памяти в ктр хран-ся команда управления. Обеспечивает очистку неисп-х эл-в
{
	DWORD rc = 0;
	while (*((TalkersCommand*)pPrm) != EXIT) { // цикл сканирования списка ListContact
		int listSize = 0;
		int howMuchClean = 0;
		if (contacts.size() != 0) {
			for (auto i = contacts.begin(); i != contacts.end();) {
				if (i->type == i->EMPTY) {
					EnterCriticalSection(&scListContact);
					if (i->sthread == i->FINISH)
						InterlockedIncrement(&successConnections); // увеличить на 1
					if (i->sthread == i->ABORT || i->sthread == i->TIMEOUT)
						InterlockedIncrement(&sayNoCount);
					i = contacts.erase(i); // очистка контактов от эл-а i
					howMuchClean++;
					listSize = contacts.size();
					LeaveCriticalSection(&scListContact);
				}
				else ++i;
			}
		}
	}
	puts("shutdown garbageCleaner");
	ExitThread(rc);
}

void CALLBACK ASWTimer(LPVOID Prm, DWORD, DWORD) { // для задания макс время обслуживания клиента
	Contact* contact = (Contact*)(Prm);
	printf("ASWTimer is calling %p\n", contact->hthread);
	TerminateThread(contact->serverHThtead, NULL); // отложить поток
	send(contact->s, "TimeOUT", strlen("TimeOUT") + 1, NULL);
	EnterCriticalSection(&scListContact);
	CancelWaitableTimer(contact->htimer); // отмена таймера если обслужив-й сервер завершится до истеч уст макс интерв
	contact->type = contact->EMPTY;
	contact->sthread = contact->TIMEOUT;
	LeaveCriticalSection(&scListContact);
}

DWORD WINAPI DispatchServer(LPVOID pPrm) // создает новый поток для всех команд и после нее запускается TimeServer или RandomServer; принимает от клиента запрос (команду) на обслуживание и после него запускается потом ServiceServer
{
	DWORD rc = 0;    	
	TalkersCommand& command = *(TalkersCommand*)pPrm;
	while (command != EXIT)
	{
		if (command == STOP) continue;
		
		WaitForSingleObject(hClientConnectedEvent, INFINITE); // позволяет потоку ожидать, пока объект синхронизации (такой как мьютекс или событие) не станет сигнальным
		ResetEvent(hClientConnectedEvent); // сбрасывает состояние объекта события в несигнальное состояние.

		while (true) {
			for (auto i = contacts.begin(); i != contacts.end(); i++) {
				if (i->type == i->ACCEPT) { // type описывает состояние соединения с клиентом на этапе подключения

					char serviceType[10]; // тип вызыв-ой ф-ии в файле PrototypeService.h: TimeServer или RandomServer
					if (recv(i->s, serviceType, sizeof(serviceType), NULL) < 1) // s - для хранения параметров соединения
						continue;

					cout << "New command - " << serviceType << endl;
							
					strcpy(i->msg, serviceType); // для записи  диагностирующего сообщения 
						
					if (!strcmp(i->msg, "close")) {
						if ((send(i->s, "echo: close", strlen("echo: close") + 1, NULL)) == SOCKET_ERROR)
							throw  SetErrorMsgText("send:", WSAGetLastError());
						i->sthread = i->FINISH; // описывает состояние соединения с клиентом на этапе обслуживания
						i->type = i->EMPTY;
						continue;
					}
					if (strcmp(i->msg, "Echo") && strcmp(i->msg, "Time") && strcmp(i->msg, "Random")) { // случай неправильных запросов
						if ((send(i->s, "ErrorInquiry", strlen("ErrorInquiry") + 1, NULL)) == SOCKET_ERROR) // если неправильный запрос
							throw  SetErrorMsgText("send:", WSAGetLastError());
						i->sthread = i->ABORT;
						i->type = i->EMPTY;
						if (closesocket(i->s) == SOCKET_ERROR)
							throw  SetErrorMsgText("closesocket:", WSAGetLastError());
					} else {
						i->type = i->CONTACT;
						i->hthread = hAcceptServer; // Для хранения дескриптора обсуживающего потока
						i->serverHThtead = ts(serviceType, (LPVOID) & (*i));
						i->htimer = CreateWaitableTimer(0, FALSE, 0); //создает объект таймера
						LARGE_INTEGER Li;
						int seconds = 60;
						Li.QuadPart = -(10000000 * seconds); // наносек = 60 * 10 сек
						SetWaitableTimer(i->htimer, &Li, 0, ASWTimer, (LPVOID) & (*i), FALSE); // для перевода в активное состояние 
						// дескриптер таймера, время срабатывания, период вр-ни, проц заверш, парам заверш, парам проц, управл питанием
						SleepEx(0, TRUE); // асинхрнно ожидать другие потоки
					}
				}
			}
			Sleep(200);
		}
	}
	puts("shutdown dispatchServer");
	ExitThread(rc);
}

bool PutAnswerToClient(char* name, sockaddr* to, int* lto) {

	char msg[] = "You can connect to server ";
	if ((sendto(sSUDP, msg, sizeof(msg) + 1, NULL, to, *lto)) == SOCKET_ERROR)
		throw  SetErrorMsgText("sendto:", WSAGetLastError());
	return false;
}

bool GetRequestFromClient(char* name, short port, SOCKADDR_IN* from, int* flen)
{
	SOCKADDR_IN clnt;
	int lc = sizeof(clnt);
	ZeroMemory(&clnt, lc); //для заполнения блока памяти нулевыми значениями.
	char ibuf[500];
	int  lb = 0;
	int optval = 1;
	int TimeOut = 10;
	setsockopt(sSUDP, SOL_SOCKET, SO_BROADCAST , (char*)&optval, sizeof(int));
	setsockopt(sSUDP, SOL_SOCKET, SO_RCVTIMEO , (char*)&TimeOut, sizeof(TimeOut));
	while (true) {
		if ((lb = recvfrom(sSUDP, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) return false;
		ibuf[lb] = '\0';
		cout << ibuf << endl;
		if (!strcmp(name, ibuf)) {
			*from = clnt;
			*flen = lc;
			return true;
		}
		puts("\nbad name");
	}
	
}

DWORD WINAPI ResponseServer(LPVOID pPrm) // для  приема  позывного  на широковещательные запросы клиента, предназначенные для поиска сервера в локальной сети; исполняет команду и в случае необходимости обменивается данными с клиентом, запускается после DispatchServer
{
	DWORD rc = 0;
	WSADATA wsaData;
	SOCKADDR_IN serv;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		throw  SetErrorMsgText("Startup:", WSAGetLastError());
	if ((sSUDP = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw  SetErrorMsgText("socket:", WSAGetLastError());
	serv.sin_family = AF_INET;
	serv.sin_port = htons(serverPort);
	serv.sin_addr.s_addr = INADDR_ANY;

	if (bind(sSUDP, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
		throw  SetErrorMsgText("bind:", WSAGetLastError());


	SOCKADDR_IN some_server;
	int serverSize = sizeof(some_server);

	SOCKADDR_IN from;
	int lc = sizeof(from);
	ZeroMemory(&from, lc);
	int numberOfClients = 0;
	while (*(TalkersCommand*)pPrm != EXIT)
	{
		try
		{
			if (GetRequestFromClient("Hello", serverPort, &from, &lc))
			{
				printf("\nconnected Client: %d, port: %d, address: %s", ++numberOfClients, htons(from.sin_port), inet_ntoa(from.sin_addr));
				PutAnswerToClient("Hello", (sockaddr*)&from, &lc);
			}
		}
		catch (string errorMsgText)
		{
			printf("\n%s", errorMsgText.c_str());
		}
	}
	if (closesocket(sSUDP) == SOCKET_ERROR)
		throw  SetErrorMsgText("closesocket:", WSAGetLastError());
	if (WSACleanup() == SOCKET_ERROR)
		throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	ExitThread(rc);
}

int main(int argc, char* argv[])
{

	if (argc == 2) {
		serverPort = atoi(argv[1]);
	}
	else if (argc == 3) {
		serverPort = atoi(argv[1]);
		strcpy(dllName, argv[2]);
	}
	else if (argc == 4) {
		serverPort = atoi(argv[1]);
		strcpy(dllName, argv[2]);
		strcpy(namedPipeName, argv[3]);
	}
	else {
		serverPort = 2000;
		strcpy(dllName, "Win32Project1.dll"); // загрузка дин библиотеки в проекте Win32Project1/PrototypeService.h
		strcpy(namedPipeName, "BOX");
	}
	printf("server port %d\n", serverPort);

	st = LoadLibraryA(dllName); // загрузка с помощью LoadLibraryA
	ts = (HANDLE(*)(char*, LPVOID))GetProcAddress(st, "SSS"); // импортируем ф-ю SSS

	volatile TalkersCommand  cmd = START; // volatile чтобы компилятор не оптимизировал (чтобы потоки исп-ие cmd AcceptServer и ConsolePipe испо-ли один-е размеры памяти)

	InitializeCriticalSection(&scListContact);

	hAcceptServer = CreateThread(NULL, NULL, AcceptServer,
									(LPVOID)&cmd, NULL, NULL);	
	hConsolePipe = CreateThread(NULL, NULL, ConsolePipe,
									(LPVOID)&cmd, NULL, NULL);
	hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner,
									(LPVOID)&cmd, NULL, NULL);
	hDispatchServer = CreateThread(NULL, NULL, DispatchServer,
									(LPVOID)&cmd, NULL, NULL);
	hResponseServer = CreateThread(NULL, NULL, ResponseServer,
									(LPVOID)&cmd, NULL, NULL);
	
	
	SetThreadPriority(hGarbageCleaner, THREAD_PRIORITY_BELOW_NORMAL);
	SetThreadPriority(hDispatchServer, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hConsolePipe, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hResponseServer, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hAcceptServer, THREAD_PRIORITY_HIGHEST);


	WaitForSingleObject(hAcceptServer, INFINITE); // чтобы эти потоки не завершились до конца main
	CloseHandle(hAcceptServer);
	WaitForSingleObject(hConsolePipe, INFINITE);
	CloseHandle(hConsolePipe);
	WaitForSingleObject(hGarbageCleaner, INFINITE);
	CloseHandle(hGarbageCleaner);
	
	TerminateThread(hDispatchServer, 0);
	puts("shutdown dispatchServer");
	TerminateThread(hResponseServer, 0);
	puts("shutdown responseServer");
	CloseHandle(hDispatchServer);
	CloseHandle(hResponseServer);


	DeleteCriticalSection(&scListContact);
	FreeLibrary(st);
	return 0;
};

