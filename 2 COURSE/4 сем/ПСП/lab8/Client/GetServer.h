#pragma once
#include <WinSock2.h>
#include <iostream>
bool SystemMessage(char* ch)
{
	bool result = false;
	char Timeout[50] = "Close: timeout;", Close[50] = "Close: finish;", Abort[50] = "Close: Abort;";
	if (strcmp(ch, Timeout) == NULL) result = true;
	else if (strcmp(ch, Abort) == NULL) result = true;
	else if (strcmp(ch, Close) == NULL) result = true;
	return result;
}

std::string GetErrorMsgText(int code)
{
	std::string msgText;
	switch (code) // �������� ���� �������� 
	{
	case WSAEINTR: msgText = "WSAEINTR"; break;                      //������ ������� ��������
	case WSAEACCES: msgText = "WSAEACCES"; break;                    //���������� ����������
	case WSAEFAULT: msgText = "WSAEFAULT"; break;                    //��������� �����
	case WSAEINVAL: msgText = "WSAEINVAL"; break;                    //������ � ���������
	case WSAEMFILE: msgText = "WSAEMFILE"; break;                    //������� ����� ������ �������
	case WSAEWOULDBLOCK: msgText = "WSAEWOULDBLOCK"; break;          //������ �������� ����������
	case WSAEINPROGRESS: msgText = "WSAEINPROGRESS"; break;          //�������� � �������� ��������
	case WSAEALREADY: msgText = "WSAEALREADY"; break;                //�������� ��� �����������
	case WSAENOTSOCK: msgText = "WSAENOTSOCK"; break;                //����� ����� �����������
	case WSAEDESTADDRREQ: msgText = "WSAEDESTADDRREQ"; break;        //��������� ����� ������������
	case WSAEMSGSIZE: msgText = "WSAEMSGSIZE"; break;                //��������� ������� �������
	case WSAEPROTOTYPE: msgText = "WSAEPROTOTYPE"; break;            //������������ ��� ��������� ��� ������
	case WSAENOPROTOOPT: msgText = "WSAENOPROTOOPT"; break;          //������ � ����� ���������
	case WSAEPROTONOSUPPORT: msgText = "WSAEPROTONOSUPPORT"; break;  //�������� �� ��������������
	case WSAESOCKTNOSUPPORT: msgText = "WSAESOCKTNOSUPPORT"; break;  //��� ������ �� ��������������
	case WSAEOPNOTSUPP: msgText = "WSAEOPNOTSUPP"; break;            //�������� �� ��������������
	case WSAEPFNOSUPPORT: msgText = "WSAEPFNOSUPPORT"; break;        //��� ���������� �� ��������������
	case WSAEAFNOSUPPORT: msgText = "WSAEAFNOSUPPORT"; break;        //��� ������� �� �������������� ����������
	case WSAEADDRINUSE: msgText = "WSAEADDRINUSE"; break;            //����� ��� ������������
	case WSAEADDRNOTAVAIL: msgText = "WSAEADDRNOTAVAIL"; break;      //����������� ����� �� ����� ���� �����������
	case WSAENETDOWN: msgText = "WSAENETDOWN"; break;                //���� ���������
	case WSAENETUNREACH: msgText = "WSAENETUNREACH"; break;          //���� �� ���������
	case WSAENETRESET: msgText = "WSAENETRESET"; break;              //���� ��������� ����������
	case WSAECONNABORTED: msgText = "WSAECONNABORTED"; break;        //����������� ����� �����
	case WSAECONNRESET: msgText = "WSAECONNRESET"; break;            //����� �������������
	case WSAENOBUFS: msgText = "WSAENOBUFS"; break;                  //�� ������� ������ ��� �������
	case WSAEISCONN: msgText = "WSAEISCONN"; break;                  //����� ��� ���������
	case WSAENOTCONN: msgText = "WSAENOTCONN"; break;                //����� �� ���������
	case WSAESHUTDOWN: msgText = "WSAESHUTDOWN"; break;              //������ ��������� send: ����� �������� ������
	case WSAETIMEDOUT: msgText = "WSAETIMEDOUT"; break;              //���������� ���������� �������� �������
	case WSAECONNREFUSED: msgText = "WSAECONNREFUSED"; break;        //���������� ���������
	case WSAEHOSTDOWN: msgText = "WSAEHOSTDOWN"; break;              //���� � ����������������� ���������
	case WSAEHOSTUNREACH: msgText = "WSAEHOSTUNREACH"; break;        //��� �������� ��� �����
	case WSAEPROCLIM: msgText = "WSAEPROCLIM"; break;                //������� ����� ���������
	case WSASYSNOTREADY: msgText = "WSASYSNOTREADY"; break;          //���� �� ��������
	case WSAVERNOTSUPPORTED: msgText = "WSAVERNOTSUPPORTED"; break;  //������ ������ ����������
	case WSANOTINITIALISED: msgText = "WSANOTINITIALISED"; break;    //�� ��������� ������������� WS2_32.DLL
	case WSAEDISCON: msgText = "WSAEDISCON"; break;                  //����������� ����������
	case WSATYPE_NOT_FOUND: msgText = "WSATYPE_NOT_FOUND"; break;    //����� �� ������
	case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND"; break;    //���� �� ������
	case WSATRY_AGAIN: msgText = "WSATRY_AGAIN"; break;              //������������������ ���� �� ������
	case WSANO_RECOVERY: msgText =
		"WSANO_RECOVERY"; break;                                     //�������������� ������
	case WSANO_DATA: msgText = "WSANO_DATA"; break;                  //��� ������ ������������ ����
	case WSA_INVALID_HANDLE: msgText = "WSA_INVALID_HANDLE"; break;  //��������� ���������� ������� � �������
	case WSA_INVALID_PARAMETER: msgText = "WSA_INVALID_PARAMETER"; break; //���� ��� ����� ���������� � �������
	case WSA_IO_INCOMPLETE: msgText = "WSA_IO_INCOMPLETE"; break;         //������ �����-������ �� � ���������� ���������
	case WSA_IO_PENDING: msgText = "WSA_IO_PENDING"; break;               //�������� ���������� �����
	case WSA_NOT_ENOUGH_MEMORY: msgText = "WSA_NOT_ENOUGH_MEMORY"; break; //�� ���������� ������
	case WSA_OPERATION_ABORTED: msgText = "WSA_OPERATION_ABORTED"; break; //�������� ����������
	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
	default: msgText = "***ERROR***"; break;
	};
	return msgText;
}

std::string SetErrorMsgText(std::string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}

bool GetServer(
	char* call, //[in] �������� ������� 
	SOCKADDR_IN* from, //[out] ��������� �� SOCKADDR_IN
	int* flen, //[out] ��������� �� ������ from 
	SOCKET* cC, //�����
	SOCKADDR_IN* all
)
{
	char ibuf[50], //����� ����� 
		obuf[50]; //����� ������
	int libuf = 0, //���������� �������� ����
		lobuf = 0; //���������� ������������ ����

	if ((lobuf = sendto(*cC, call, strlen(call) + 1, NULL,
		(sockaddr*)all, sizeof(*all))) == SOCKET_ERROR)
		throw SetErrorMsgText("Sendto:", WSAGetLastError());
	if ((libuf = recvfrom(*cC, ibuf, sizeof(ibuf), NULL, (sockaddr*)from, flen)) == SOCKET_ERROR)
		if (WSAGetLastError() == WSAETIMEDOUT) {
			std::cout << "��������� ����� �������� ������" << "\n";
			return false;
		}
		else throw SetErrorMsgText("Recv:", WSAGetLastError());
	if (strcmp(call, ibuf) == 0) {
		//cout�"/////////////////////////////"�endl;
		// cout�"ip: "�inet_ntoa((*from).sin_addr);
		return true;
	}
	else {
		return false;
	}
}