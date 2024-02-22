#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "Winsock2.h"
#include "WSAErrors.h"
#include "stringList.h"
#pragma comment(lib, "WS2_32.lib")

struct GETSINCHRO {
	char cmd[5];
	int curvalue;
};
struct SETSINCHRO {
	char cmd[5];
	int correction;
};
stringList ipList = stringList();
void MessagingWithClient(SOCKET server, bool* online) {
	SOCKADDR_IN from;
	memset(&from, 0, sizeof(from)); // обнулить память
	int recvLen = 0;
	GETSINCHRO getS = GETSINCHRO();
	memset(&getS, 0, sizeof(getS));
	int lfrom = sizeof(from);
	if (recvLen = recvfrom(server, (char*)&getS, sizeof(getS), NULL, (sockaddr*)&from, &lfrom) == SOCKET_ERROR) {
		throw SetErrorMsgText("recvfrom Error:", WSAGetLastError());
	}
	if (strcmp(getS.cmd, "DISC") == 0) {
		std::string ip = std::string(inet_ntoa(from.sin_addr));
		ipList.remove(ipList.indexOf(ip), NULL);
		std::cout << "Клиент " << ip << htons(from.sin_port) << " отключился\n";
	}
	if (strcmp(getS.cmd,"SINC") == 0) {
		std::string ip = std::string(inet_ntoa(from.sin_addr));
		stringNode* node;
		bool first = false;
		if (ipList.contain(ip)) {
			node = ipList.get(ip);
		}
		else {
			node = new stringNode();
			node->ip = ip;
			node->avgCorrection = 0;
			node->count = 0;
			ipList.push(node);
			node = ipList.get(ip);
			first = true;
		}
		SETSINCHRO setS = SETSINCHRO();
		setS.cmd[0] = 'S';
		setS.cmd[1] = 'I';
		setS.cmd[2] = 'N';
		setS.cmd[3] = 'C';
		setS.cmd[4] = '\0';
		setS.correction = clock() - getS.curvalue;
		if (!first) {
			node->count++;
			node->avgCorrection = (node->avgCorrection * (node->count - 1) + setS.correction) / node->count;
		}
		if (sendto(server, (char*)&setS, sizeof(setS), NULL, (sockaddr*)&from, sizeof(from)) == SOCKET_ERROR)
			throw SetErrorMsgText("recvfrom Error:", WSAGetLastError());
		std::cout << "Выполнен запрос на синхронизацию для клиента: " << inet_ntoa(from.sin_addr) << htons(from.sin_port) << std::endl;
		if (!first) {
		std::cout << "						на величену (correction): " << setS.correction << std::endl;
		std::cout << "						номер запроса: " << node->count << std::endl;
		std::cout << "						средняя величина исправления: " << node->avgCorrection << std::endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	WSADATA wsaData;
	try
	{
		//Инициализируем динамическую библиотеку
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup Error:", WSAGetLastError());
		//Создаём сокет и начинаем работу
		SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (serverSocket == INVALID_SOCKET) {
			throw SetErrorMsgText("socket Error:", WSAGetLastError());
		}
		else {
			bool serverOnline = true;
			SOCKADDR_IN serverAddres;
			serverAddres.sin_family = AF_INET;
			serverAddres.sin_port = htons(2000);
			serverAddres.sin_addr.s_addr = INADDR_ANY;
			if (bind(serverSocket, (LPSOCKADDR)&serverAddres, sizeof(serverAddres)) == SOCKET_ERROR)
				throw SetErrorMsgText("bind Error:", WSAGetLastError());
			std::cout << "Сервер работает на " << inet_ntoa(serverAddres.sin_addr) << ":" << htons(serverAddres.sin_port) << std::endl;
			while (serverOnline) {
				MessagingWithClient(serverSocket, &serverOnline);
			}

			if (closesocket(serverSocket) == SOCKET_ERROR)
				throw SetErrorMsgText("closesocket Error:", WSAGetLastError());
		}
		//Завершаем работу с библиотекой WS2_32.DDL
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup Error:", WSAGetLastError());
	}
	catch (std::string errorMsgText)
	{
		std::cout << std::endl << errorMsgText;
	}
	system("pause");
}