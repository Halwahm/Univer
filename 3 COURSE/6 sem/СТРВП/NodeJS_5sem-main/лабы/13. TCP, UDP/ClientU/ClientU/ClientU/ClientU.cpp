﻿#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <clocale>
#include <ctime>

#include "ErrorMsgText.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

#define PORT 4000

using namespace std;

//Для демонстрации потери сообщений закомментить recvfrom

int main()
{
    setlocale(LC_ALL, "rus");

    WSADATA wsaData;
    SOCKET cC;

    try {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw  SetErrorMsgText("Startup: ", WSAGetLastError());
        }
        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
            throw  SetErrorMsgText("socket: ", WSAGetLastError());
        }

        SOCKADDR_IN serv;
        int ls = sizeof(serv);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(PORT);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");

        char ibuf[50] = "server: принято ";
        int  libuf = 0, lobuf = 0;

        string obuf = "C++";

        if ((libuf = sendto(cC, obuf.c_str(), obuf.length() + 1, NULL,
            (SOCKADDR*)&serv, sizeof(serv))) == SOCKET_ERROR) {
            throw  SetErrorMsgText("sendto: ", WSAGetLastError());
        }

        if ((lobuf = recvfrom(cC, ibuf, sizeof(ibuf), NULL, (sockaddr*)&serv, &ls)) == SOCKET_ERROR) {
            throw  SetErrorMsgText("recvfrom:", WSAGetLastError());
        }

        cout << ibuf << endl;
        
        

        if (closesocket(cC) == SOCKET_ERROR) {
            throw SetErrorMsgText("closesocket: ", WSAGetLastError());
        }
        if (WSACleanup() == SOCKET_ERROR) {
            throw  SetErrorMsgText("Cleanup: ", WSAGetLastError());
        }
    }
    catch (string errorMsgText) {
        cout << endl << errorMsgText;
    }

    system("pause");
    return 0;
}