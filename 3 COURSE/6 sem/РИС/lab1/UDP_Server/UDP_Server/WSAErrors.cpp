#include "WSAErrors.h"

std::string SetErrorMsgText(std::string message, int code) {
	std::string errorMsg;
	switch (code)
	{
	case WSAEINTR: errorMsg = "Работа функции прервана (WSAEINTR)"; break;
	case WSAEACCES: errorMsg = "Разрешение отвергнуто (WSAEACCES)"; break;
	case WSAEFAULT: errorMsg = "Ошибочный адрес (WSAEFAULT)"; break;
	case WSAEINVAL: errorMsg = "Ошибка в аргументе (WSAEINVAL)"; break;
	case WSAEMFILE: errorMsg = "Слишком много файлов открыто (WSAEMFILE)"; break;
	case WSAEWOULDBLOCK: errorMsg = "Ресурс временно недоступен (WSAEWOULDBLOCK)"; break;
	case WSAEINPROGRESS: errorMsg = "Операция в процессе развития (WSAEINPROGRESS)"; break;
	case WSAEALREADY: errorMsg = "Операция уже выполняется (WSAEALREADY)"; break;
	case WSAENOTSOCK: errorMsg = "Сокет задан неправильно (WSAENOTSOCK)"; break;
	case WSAEDESTADDRREQ: errorMsg = "Требуется адрес расположения (WSAEDESTADDRREQ)"; break;
	case WSAEMSGSIZE: errorMsg = "Сообщение слишком длинное (WSAEMSGSIZE)"; break;
	case WSAEPROTOTYPE: errorMsg = "Неправильный тип протокола для сокета (WSAEPROTOTYPE)"; break;
	case WSAENOPROTOOPT: errorMsg = "Ошибка в опции протокола (WSAENOPROTOOPT)"; break;
	case WSAEPROTONOSUPPORT: errorMsg = "Протокол не поддерживается (WSAEPROTONOSUPPORT)"; break;
	case WSAESOCKTNOSUPPORT: errorMsg = "Тип сокета не поддерживается (WSAESOCKTNOSUPPORT)"; break;
	case WSAEOPNOTSUPP: errorMsg = "Операция не поддерживается (WSAEOPNOTSUPP)"; break;
	case WSAEPFNOSUPPORT: errorMsg = "Тип протоколов не поддерживается (WSAEAFNOSUPPORT)"; break;
	case WSAEAFNOSUPPORT: errorMsg = "Тип адресов не поддерживается протоколом (WSAEWOULDBLOCK)"; break;
	case WSAEADDRINUSE: errorMsg = "Адрес уже используется (WSAEADDRINUSE)"; break;
	case WSAEADDRNOTAVAIL: errorMsg = "Запрошенный адрес не может быть использован (WSAEADDRNOTAVAIL)"; break;
	case WSAENETDOWN: errorMsg = "Сеть отключена (WSAENETDOWN)"; break;
	case WSAENETUNREACH: errorMsg = "Сеть не достижима (WSAENETUNREACH)"; break;
	case WSAENETRESET: errorMsg = "Сеть разорвала соединение (WSAENETRESET)"; break;
	case WSAECONNABORTED: errorMsg = "Программный отказ связи (WSAECONNABORTED)"; break;
	case WSAECONNRESET: errorMsg = "Связь восстановлена (WSAECONNRESET)"; break;
	case WSAENOBUFS: errorMsg = "Не хватает памяти для буферов (WSAENOBUFS)"; break;
	case WSAEISCONN: errorMsg = "Сокет уже подключен (WSAEISCONN)"; break;
	case WSAENOTCONN: errorMsg = "Сокет не подключен (WSAENOTCONN)"; break;
	case WSAESHUTDOWN: errorMsg = "Нельзя выполнить send : сокет завершил работу (WSAESHUTDOWN)"; break;
	case WSAETIMEDOUT: errorMsg = "Закончился отведенный интервал времени (WSAETIMEDOUT)"; break;
	case WSAECONNREFUSED: errorMsg = "Соединение отклонено (WSAECONNREFUSED)"; break;
	case WSAEHOSTDOWN: errorMsg = "Хост в неработоспособном состоянии (WSAEHOSTDOWN)"; break;
	case WSAEHOSTUNREACH: errorMsg = "Нет маршрута для хоста (WSAEHOSTUNREACH)"; break;
	case WSAEPROCLIM: errorMsg = "Слишком много процессов (WSAEPROCLIM)"; break;
	case WSASYSNOTREADY: errorMsg = "Сеть не доступна (WSASYSNOTREADY)"; break;
	case WSAVERNOTSUPPORTED: errorMsg = "Данная версия недоступна (WSAVERNOTSUPPORTED)"; break;
	case WSANOTINITIALISED: errorMsg = "Не выполнена инициализация WS2_32.DLL (WSANOTINITIALISED)"; break;
	case WSAEDISCON: errorMsg = "Выполняется отключение (WSAEDISCON)"; break;
	case WSATYPE_NOT_FOUND: errorMsg = "Класс не найден (WSATYPE_NOT_FOUND)"; break;
	case WSAHOST_NOT_FOUND: errorMsg = "Хост не найден (WSAHOST_NOT_FOUND)"; break;
	case WSATRY_AGAIN: errorMsg = "Неавторизированный хост не найден (WSATRY_AGAIN)"; break;
	case WSANO_RECOVERY: errorMsg = "Неопределенная ошибка (WSANO_RECOVERY)"; break;
	case WSANO_DATA: errorMsg = "Нет записи запрошенного типа (WSANO_DATA)"; break;
	case WSA_INVALID_HANDLE: errorMsg = "Указанный дескриптор события с ошибкой (WSA_INVALID_HANDLE)"; break;
	case WSA_INVALID_PARAMETER: errorMsg = "Один или более параметров с ошибкой (WSA_INVALID_PARAMETER)"; break;
	case WSA_IO_INCOMPLETE: errorMsg = "Объект ввода - вывода не в сигнальном состоянии (WSA_IO_INCOMPLETE)"; break;
	case WSA_IO_PENDING: errorMsg = "Операция завершится позже (WSA_IO_PENDING)"; break;
	case WSA_NOT_ENOUGH_MEMORY: errorMsg = "Не достаточно памяти (WSA_NOT_ENOUGH_MEMORY)"; break;
	case WSA_OPERATION_ABORTED: errorMsg = "Операция отвергнута (WSA_OPERATION_ABORTED)"; break;
	case WSASYSCALLFAILURE: errorMsg = "Аварийное завершение системного вызова (WSASYSCALLFAILURE)"; break;
	default: errorMsg = "Не известная ошибка"; break;
	}
	return message + " " + errorMsg;
}