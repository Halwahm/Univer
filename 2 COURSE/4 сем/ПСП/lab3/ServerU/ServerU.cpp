﻿#include <iostream>
#include <clocale>
#include <ctime>

#include "ErrorMsgText.h"
#include "Winsock2.h"

#pragma warning(disable : 4996)
#pragma comment(lib, "WS2_32.lib")  

int main()
{
    setlocale(LC_ALL, "rus");

    WSADATA wsaData;

    SOCKET  sS;
    SOCKADDR_IN serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(2000);
    serv.sin_addr.s_addr = INADDR_ANY;

    try {
        cout << "ServerU\n\n";

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw  SetErrorMsgText("WSAStartup: ", WSAGetLastError());
        }

  
        if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
            throw  SetErrorMsgText("socket: ", WSAGetLastError());
        }
        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) {
            throw  SetErrorMsgText("bind: ", WSAGetLastError());
        }

        SOCKADDR_IN clientInfo;
        memset(&clientInfo, 0, sizeof(clientInfo));
        char ibuf[50];
        int lc = sizeof(clientInfo), lb = 0, lobuf = 0;
        clock_t start, end;
        bool flag = true;

        while (true) {
            Sleep(10);
            
            if ((lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clientInfo, &lc)) == SOCKET_ERROR) {
                throw  SetErrorMsgText("recvfrom: ", WSAGetLastError());
            }
            if (flag) {
                flag = false;
                start = clock();
            }

            

            if (strcmp(ibuf, "") == 0) {
                end = clock();
                flag = true;
                cout << "\nTime for sendto and recvfrom: " << ((double)(end - start) / CLK_TCK) << " c\n\n";
                
            }
            else {
                cout << ibuf << endl;
            }
            
        }

    }
    catch (basic_string<char> error_msg_text) {
        cout << endl << error_msg_text;
    }

    system("pause");
    return 0;
}