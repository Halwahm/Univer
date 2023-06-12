#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <clocale>
#include <ctime>

#include "ErrorMsgText.h"

#include "Winsock2.h"                
#pragma comment(lib, "WS2_32.lib")   
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    WSADATA wsaData;
    SOCKET cC;
    SOCKADDR_IN serv;
    
    serv.sin_family = AF_INET;
    serv.sin_port = htons(2000);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    try {
        cout << "ClientT\n\n";

        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
            throw  set_error_msg_text("Startup: ", WSAGetLastError());
        }
        if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) {
            throw  set_error_msg_text("socket: ", WSAGetLastError());
        }
        if ((connect(cC, reinterpret_cast<sockaddr*>(&serv), sizeof(serv))) == SOCKET_ERROR) {
            throw set_error_msg_text("connect: ", WSAGetLastError());
        }

        char ibuf[50] = "server: принято ";
        int  libuf = 0, lobuf = 0;

        int message_amount;
        cout << "Amount of messages to send: ";
        cin >> message_amount;

        const clock_t start = clock();
        for (int i = 1; i <= message_amount; i++) {
            std::string obuf = "Hello from Client " + std::to_string(i);

            if ((lobuf = send(cC, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL)) == SOCKET_ERROR) {
                throw set_error_msg_text("send: ", WSAGetLastError());
            }

            if ((libuf = recv(cC, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
                throw set_error_msg_text("recv: ", WSAGetLastError());
            }

            std::cout << ibuf << '\n';
        }
        const clock_t end = clock();
        const std::string obuf = "";

   
        if ((lobuf = send(cC, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL)) == SOCKET_ERROR) {
            throw set_error_msg_text("send: ", WSAGetLastError());
        };

        cout << "Full time of recv/send exchange: " << (static_cast<double>(end - start) / CLK_TCK) << " c\n";

        if (closesocket(cC) == SOCKET_ERROR) {
            throw set_error_msg_text("closesocket: ", WSAGetLastError());
        }
        if (WSACleanup() == SOCKET_ERROR) {
            throw  set_error_msg_text("Cleanup: ", WSAGetLastError());
        }
    }
    catch (std::string error_msg_text) {
        WSACleanup();
        cout << '\n' << error_msg_text;
    }
    return 0;
}