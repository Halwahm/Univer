#include "WSAErrors.h"

std::string SetErrorMsgText(std::string message, int code) {
	std::string errorMsg;
	switch (code)
	{
	case WSAEINTR: errorMsg = "������ ������� �������� (WSAEINTR)"; break;
	case WSAEACCES: errorMsg = "���������� ���������� (WSAEACCES)"; break;
	case WSAEFAULT: errorMsg = "��������� ����� (WSAEFAULT)"; break;
	case WSAEINVAL: errorMsg = "������ � ��������� (WSAEINVAL)"; break;
	case WSAEMFILE: errorMsg = "������� ����� ������ ������� (WSAEMFILE)"; break;
	case WSAEWOULDBLOCK: errorMsg = "������ �������� ���������� (WSAEWOULDBLOCK)"; break;
	case WSAEINPROGRESS: errorMsg = "�������� � �������� �������� (WSAEINPROGRESS)"; break;
	case WSAEALREADY: errorMsg = "�������� ��� ����������� (WSAEALREADY)"; break;
	case WSAENOTSOCK: errorMsg = "����� ����� ����������� (WSAENOTSOCK)"; break;
	case WSAEDESTADDRREQ: errorMsg = "��������� ����� ������������ (WSAEDESTADDRREQ)"; break;
	case WSAEMSGSIZE: errorMsg = "��������� ������� ������� (WSAEMSGSIZE)"; break;
	case WSAEPROTOTYPE: errorMsg = "������������ ��� ��������� ��� ������ (WSAEPROTOTYPE)"; break;
	case WSAENOPROTOOPT: errorMsg = "������ � ����� ��������� (WSAENOPROTOOPT)"; break;
	case WSAEPROTONOSUPPORT: errorMsg = "�������� �� �������������� (WSAEPROTONOSUPPORT)"; break;
	case WSAESOCKTNOSUPPORT: errorMsg = "��� ������ �� �������������� (WSAESOCKTNOSUPPORT)"; break;
	case WSAEOPNOTSUPP: errorMsg = "�������� �� �������������� (WSAEOPNOTSUPP)"; break;
	case WSAEPFNOSUPPORT: errorMsg = "��� ���������� �� �������������� (WSAEAFNOSUPPORT)"; break;
	case WSAEAFNOSUPPORT: errorMsg = "��� ������� �� �������������� ���������� (WSAEWOULDBLOCK)"; break;
	case WSAEADDRINUSE: errorMsg = "����� ��� ������������ (WSAEADDRINUSE)"; break;
	case WSAEADDRNOTAVAIL: errorMsg = "����������� ����� �� ����� ���� ����������� (WSAEADDRNOTAVAIL)"; break;
	case WSAENETDOWN: errorMsg = "���� ��������� (WSAENETDOWN)"; break;
	case WSAENETUNREACH: errorMsg = "���� �� ��������� (WSAENETUNREACH)"; break;
	case WSAENETRESET: errorMsg = "���� ��������� ���������� (WSAENETRESET)"; break;
	case WSAECONNABORTED: errorMsg = "����������� ����� ����� (WSAECONNABORTED)"; break;
	case WSAECONNRESET: errorMsg = "����� ������������� (WSAECONNRESET)"; break;
	case WSAENOBUFS: errorMsg = "�� ������� ������ ��� ������� (WSAENOBUFS)"; break;
	case WSAEISCONN: errorMsg = "����� ��� ��������� (WSAEISCONN)"; break;
	case WSAENOTCONN: errorMsg = "����� �� ��������� (WSAENOTCONN)"; break;
	case WSAESHUTDOWN: errorMsg = "������ ��������� send : ����� �������� ������ (WSAESHUTDOWN)"; break;
	case WSAETIMEDOUT: errorMsg = "���������� ���������� �������� ������� (WSAETIMEDOUT)"; break;
	case WSAECONNREFUSED: errorMsg = "���������� ��������� (WSAECONNREFUSED)"; break;
	case WSAEHOSTDOWN: errorMsg = "���� � ����������������� ��������� (WSAEHOSTDOWN)"; break;
	case WSAEHOSTUNREACH: errorMsg = "��� �������� ��� ����� (WSAEHOSTUNREACH)"; break;
	case WSAEPROCLIM: errorMsg = "������� ����� ��������� (WSAEPROCLIM)"; break;
	case WSASYSNOTREADY: errorMsg = "���� �� �������� (WSASYSNOTREADY)"; break;
	case WSAVERNOTSUPPORTED: errorMsg = "������ ������ ���������� (WSAVERNOTSUPPORTED)"; break;
	case WSANOTINITIALISED: errorMsg = "�� ��������� ������������� WS2_32.DLL (WSANOTINITIALISED)"; break;
	case WSAEDISCON: errorMsg = "����������� ���������� (WSAEDISCON)"; break;
	case WSATYPE_NOT_FOUND: errorMsg = "����� �� ������ (WSATYPE_NOT_FOUND)"; break;
	case WSAHOST_NOT_FOUND: errorMsg = "���� �� ������ (WSAHOST_NOT_FOUND)"; break;
	case WSATRY_AGAIN: errorMsg = "������������������ ���� �� ������ (WSATRY_AGAIN)"; break;
	case WSANO_RECOVERY: errorMsg = "�������������� ������ (WSANO_RECOVERY)"; break;
	case WSANO_DATA: errorMsg = "��� ������ ������������ ���� (WSANO_DATA)"; break;
	case WSA_INVALID_HANDLE: errorMsg = "��������� ���������� ������� � ������� (WSA_INVALID_HANDLE)"; break;
	case WSA_INVALID_PARAMETER: errorMsg = "���� ��� ����� ���������� � ������� (WSA_INVALID_PARAMETER)"; break;
	case WSA_IO_INCOMPLETE: errorMsg = "������ ����� - ������ �� � ���������� ��������� (WSA_IO_INCOMPLETE)"; break;
	case WSA_IO_PENDING: errorMsg = "�������� ���������� ����� (WSA_IO_PENDING)"; break;
	case WSA_NOT_ENOUGH_MEMORY: errorMsg = "�� ���������� ������ (WSA_NOT_ENOUGH_MEMORY)"; break;
	case WSA_OPERATION_ABORTED: errorMsg = "�������� ���������� (WSA_OPERATION_ABORTED)"; break;
	case WSASYSCALLFAILURE: errorMsg = "��������� ���������� ���������� ������ (WSASYSCALLFAILURE)"; break;
	default: errorMsg = "�� ��������� ������"; break;
	}
	return message + " " + errorMsg;
}