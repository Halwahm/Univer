#include "stdafx.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>

#define IP_SERVER "192.168.134.8"

using namespace std;
using namespace chrono;

string GetErrorMsgText(int code)
{
    string msgText;
    switch (code)
    {
    case WSAEINTR: msgText = "WSAEINTR";
        break;
    case WSAEACCES: msgText = "WSAEACCES";
        break;
    case WSAEFAULT: msgText = "WSAEFAULT";
        break;
    case WSAEINVAL: msgText = "WSAEINVAL";
        break;
    case WSAEMFILE: msgText = "WSAEMFILE";
        break;
    case WSAEWOULDBLOCK: msgText = "WSAEWOULDBLOCK";
        break;
    case WSAEINPROGRESS: msgText = "WSAEINPROGRESS";
        break;
    case WSAEALREADY: msgText = "WSAEALREADY";
        break;
    case WSAENOTSOCK: msgText = "WSAENOTSOCK";
        break;
    case WSAEDESTADDRREQ: msgText = "WSAEDESTADDRREQ";
        break;
    case WSAEMSGSIZE: msgText = "WSAEMSGSIZE";
        break;
    case WSAEPROTOTYPE: msgText = "WSAEPROTOTYPE";
        break;
    case WSAENOPROTOOPT: msgText = "WSAENOPROTOOPT";
        break;
    case WSAEPROTONOSUPPORT: msgText = "WSAEPROTONOSUPPORT";
        break;
    case WSAESOCKTNOSUPPORT: msgText = "WSAESOCKTNOSUPPORT";
        break;
    case WSAEOPNOTSUPP: msgText = "WSAEOPNOTSUPP";
        break;
    case WSAEPFNOSUPPORT: msgText = "WSAEPFNOSUPPORT";
        break;
    case WSAEAFNOSUPPORT: msgText = "WSAEAFNOSUPPORT";
        break;
    case WSAEADDRINUSE: msgText = "WSAEADDRINUSE";
        break;
    case WSAEADDRNOTAVAIL: msgText = "WSAEADDRNOTAVAIL";
        break;
    case WSAENETDOWN: msgText = "WSAENETDOWN";
        break;
    case WSAENETUNREACH: msgText = "WSAENETUNREACH";
        break;
    case WSAENETRESET: msgText = "WSAENETRESET";
        break;
    case WSAECONNABORTED: msgText = "WSAECONNABORTED";
        break;
    case WSAECONNRESET: msgText = "WSAECONNRESET";
        break;
    case WSAENOBUFS: msgText = "WSAENOBUFS";
        break;
    case WSAEISCONN: msgText = "WSAEISCONN";
        break;
    case WSAENOTCONN: msgText = "WSAENOTCONN";
        break;
    case WSAESHUTDOWN: msgText = "WSAESHUTDOWN";
        break;
    case WSAETIMEDOUT: msgText = "WSAETIMEDOUT";
        break;
    case WSAECONNREFUSED: msgText = "WSAECONNREFUSED";
        break;
    case WSAEHOSTDOWN: msgText = "WSAEHOSTDOWN";
        break;
    case WSAEHOSTUNREACH: msgText = "WSAEHOSTUNREACH";
        break;
    case WSAEPROCLIM: msgText = "WSAEPROCLIM";
        break;
    case WSASYSNOTREADY: msgText = "WSASYSNOTREADY";
        break;
    case WSAVERNOTSUPPORTED: msgText = "WSAVERNOTSUPPORTED";
        break;
    case WSANOTINITIALISED: msgText = "WSANOTINITIALISED";
        break;
    case WSAEDISCON: msgText = "WSAEDISCON";
        break;
    case WSATYPE_NOT_FOUND: msgText = "WSATYPE_NOT_FOUND";
        break;
    case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND";
        break;
    case WSATRY_AGAIN: msgText = "WSATRY_AGAIN";
        break;
    case WSANO_RECOVERY: msgText = "WSANO_RECOVERY";
        break;
    case WSANO_DATA: msgText = "WSANO_DATA";
        break;
    case WSA_INVALID_HANDLE: msgText = "WSA_INVALID_HANDLE";
        break;
    case WSA_INVALID_PARAMETER: msgText = "WSA_INVALID_PARAMETER";
        break;
    case WSA_IO_INCOMPLETE: msgText = "WSA_IO_INCOMPLETE";
        break;
    case WSA_IO_PENDING: msgText = "WSA_IO_PENDING";
        break;
    case WSA_NOT_ENOUGH_MEMORY: msgText = "WSA_NOT_ENOUGH_MEMORY";
        break;
    case WSA_OPERATION_ABORTED: msgText = "WSA_OPERATION_ABORTED";
        break;
    case WSAEINVALIDPROCTABLE: msgText = "WSAEINVALIDPROCTABLE";
        break;
    case WSAEINVALIDPROVIDER: msgText = "WSAEINVALIDPROVIDER";
        break;
    case WSAEPROVIDERFAILEDINIT: msgText = "WSAEPROVIDERFAILEDINIT";
        break;

    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE";
        break;
    default: msgText = "***ERROR***";
        break;
    };
    return msgText;
};

string SetErrorMsgText(string msgText, int code)
{
    string error = msgText + GetErrorMsgText(code);
    error.append(" ").append(to_string(code));
    return error;
};

char* get_message(int msg)
{
    switch (msg)
    {
    case 1: return "Echo";
    case 2: return "Time";
    case 3: return "Random";
    case 4: return "close";
    default:
        return "";
    }
}

int _tmain(int argc, char* argv[])
{
    SOCKET cS;
    WSADATA wsaData;
    setlocale(0, "rus");
    try
    {
        if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());
        if ((cS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        SOCKET cC;
        if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(2000);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");
        if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
            throw SetErrorMsgText("connect:", WSAGetLastError());

        while (true)
        {
            char message[50],
                 obuf[50];
            int libuf = 0,
                lobuf = 0;

            puts("Choose");
            int service;
            puts("1 - Echo\n2 - Time\n3 - Random\n4 - close socket");

            scanf("%d", &service);
            char* outMessage = new char[5];
            strcpy(outMessage, get_message(service));

            if ((lobuf = send(cC, outMessage, strlen(outMessage) + 1, NULL)) == SOCKET_ERROR)
                throw SetErrorMsgText("send:", WSAGetLastError());

            printf("sended: %s\n", outMessage);

            if ((libuf = recv(cC, message, sizeof(message), NULL)) == SOCKET_ERROR)
                throw SetErrorMsgText("recv:", WSAGetLastError());

            if (service == 4)
            {
                break;
            }

            if (!strcmp(message, "TimeOUT"))
            {
                puts("time out");
                return -1;
            }
            if (service == 1)
            {
                for (int j = 10; j >= 0; --j)
                {
                    Sleep(1000);
                    sprintf(outMessage, "%d", j);
                    if ((lobuf = send(cC, outMessage, strlen(outMessage) + 1, NULL)) == SOCKET_ERROR)
                        throw SetErrorMsgText("send:", WSAGetLastError());
                    printf("send: %s\n", outMessage);
                    if ((libuf = recv(cC, message, sizeof(message), NULL)) == SOCKET_ERROR)
                        throw SetErrorMsgText("recv:", WSAGetLastError());
                    printf("receive: %s\n", message);
                }
            }
            else if (service == 2 || service == 3)
            {
                printf("receive: %s\n", message);
            }
        }

        if (closesocket(cS) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        printf("\n%s", errorMsgText.c_str());
    }
    system("pause");
    return 0;
}
