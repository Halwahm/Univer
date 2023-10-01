
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1;
#pragma comment(lib, "WS2_32.lib")
#include "GetServer.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle(L"Client"); // заголовок консольного окна
	int port = 0;
	SOCKET ClientSocket;
	WSADATA wsaData;
	try
	{

		// Инициализируем Winsocket
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());
		// Создаем сокет
		if ((ClientSocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket:", WSAGetLastError());

		int ch = 0;
		bool fin = false;
		int cCall = 0;

		int max = 100, lobuf = 1;
		char obuf[50] = "";
		char ibuf[50] = "";
		int bport = 2000;

		char Call[50]; //запрос клиента
		//char Error[50] = "ErrorInquiry";
		char Name[50] = "server"; //имя сервера
		char Calls[50] = ""; //позывной

		SOCKADDR_IN Server = { 0 };
		Server.sin_family = AF_INET;
		Server.sin_port = htons(port);

		SOCKADDR_IN Server_IN; //параметры сокета сервера
		int Flen = sizeof(Server);
		int chs = 0;
		cout << "1 - Enter name of server" << endl << "2 - Pozyvnoi" << endl << "> ";
		cin >> chs;
		if (chs == 1)
		{
			cout << "Enter: ";
			cin >> Name;
			hostent* s = gethostbyname(Name);
			if (s == NULL) throw "Server not found;";
			cout << "Enter port of server: ";
			cin >> port;
			Server_IN.sin_addr = *(struct in_addr*)s->h_addr_list[0];
		}
		else if (chs == 2)
		{
			cout << "Enter pozyvnoi: ";
			cin >> Calls;
			SOCKET cC; //серверный сокет
			if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
				throw SetErrorMsgText("Socket:", WSAGetLastError());

			int optval = 1;
			if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST,
				(char*)&optval, sizeof(int)) == SOCKET_ERROR)
				throw SetErrorMsgText("Opt:", WSAGetLastError());
			struct timeval timeout;
			timeout.tv_sec = 10;
			timeout.tv_usec = 0;
			if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
				throw SetErrorMsgText("Opt:", WSAGetLastError());

			SOCKADDR_IN all; //параметры сокета sS
			all.sin_family = AF_INET; //используется IP-адресация 
			all.sin_port = htons(bport); //порт для широковещания
			all.sin_addr.s_addr = INADDR_BROADCAST; //всем
			SOCKADDR_IN clnt; //параметры сокета клиента
			memset(&clnt, 0, sizeof(clnt)); //обнулить память
			int lc = sizeof(clnt); //размер SOCKADDR_IN

			bool bsr = GetServer(Calls, &clnt, &lc, &cC, &all);
			if (bsr == false) throw "Server not found;";
			else
			{
				Server_IN.sin_addr.s_addr = clnt.sin_addr.s_addr;
				if (closesocket(cC) == SOCKET_ERROR)
					throw SetErrorMsgText("Closesocket:", WSAGetLastError());
				cout << "Enter port of server: ";
				cin >> port;
			}

		}
		else throw "Wrong code";

		// Параметры сокета сервера
		Server_IN.sin_family = AF_INET; //используется IP-адресация 
		Server_IN.sin_port = htons(port); //TCP-порт

		// Установить соединение с сокетом
		if ((connect(ClientSocket, (sockaddr*)&Server_IN, sizeof(Server_IN))) == SOCKET_ERROR)
			throw "Fail connection;";
		else {
			while (!fin)
			{
				cout << "Service: " << endl << "1 - Rand" << endl << "2 - Time" << endl << "3 - Echo" << endl << "> ";
				cin >> cCall;
				if (cCall == 1 || cCall == 2 || cCall == 3)
				{
					fin = true;
					break;
				}

				else
				{
					if (closesocket(ClientSocket) == SOCKET_ERROR)
						throw SetErrorMsgText("Closesocket:", WSAGetLastError());
					throw "Wrong code;";
				}
			}

			switch (cCall)
			{
			case 1:
				strcpy(Call, "Rand");
				cout << "Enter Rand command or other:" << endl;
				break;
			case 2:
				strcpy(Call, "Time");
				cout << "Enter Time command or other:" << endl;
				break;
			case 3:
				strcpy(Call, "Echo");
				cout << "Enter string or exit :" << endl;
				break;
			default:
				strcpy(Call, "Echo");
			}

			// Отправляем запрос серверу
			if ((lobuf = send(ClientSocket, Call, sizeof(Call), NULL)) == SOCKET_ERROR)
				throw SetErrorMsgText("Send:", WSAGetLastError());
			char rCall[50];
			if ((lobuf = recv(ClientSocket, rCall, sizeof(rCall), NULL)) == SOCKET_ERROR)
				throw SetErrorMsgText("Recv:", WSAGetLastError());

			if (strcmp(Call, rCall) != 0)
				throw "Fail of server";
			else
			{
				bool Check = true;
				fin = false;

				u_long nonblk = 1;
				if (SOCKET_ERROR == ioctlsocket(ClientSocket, FIONBIO, &nonblk))
					throw SetErrorMsgText("Ioctlsocket:", WSAGetLastError());
				clock_t StartTime = clock();
				bool rcv = true;

				char iib[50];
				std::cout << "->";
				std::cin >> iib;

				while (!fin)
				{
					if (rcv)
					{
						// Отправка сообщения
						if ((lobuf = send(ClientSocket, iib, sizeof(iib), NULL)) == SOCKET_ERROR)
							/*throw SetErrorMsgText("Send:",WSAGetLastError());*/
							throw "Error;";
						rcv = false;
					}
					// Принимаем сообщение

					if ((recv(ClientSocket, obuf, sizeof(obuf), NULL)) == SOCKET_ERROR)
					{
						switch (WSAGetLastError())
						{
						case WSAEWOULDBLOCK: Sleep(100); break;
						case WSAECONNABORTED: throw "Connection with server aborted (timeout)";
						default: throw SetErrorMsgText("Recv:", WSAGetLastError());
						}
					}
					else
					{
						if (SystemMessage(obuf))
						{
							printf("Server stopped connection: %s\n", obuf);
							break;
						}
						else
							// Выводим полученное сообщение
							printf("Received message:[%s]\n", obuf);
						rcv = true;
						std::cout << "->";
						std::cin >> iib;
					}

				}

				clock_t FinishTime = clock();
				printf("Time: %lf sec.\n", (double)(FinishTime - StartTime) / CLOCKS_PER_SEC);

			}
		}
		// Закрываем сокет
		if (closesocket(ClientSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("Closesocket:", WSAGetLastError());

		// Очищаем ресурсы
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (char* errorMsgText)
	{
		cout << errorMsgText << endl;
	}
	catch (std::string errorMsgText)
	{
		cout << errorMsgText << endl;
	}
	catch (const char* errorMsgText)
	{
		cout << errorMsgText << endl;
	}

	system("pause");
	return 0;
}