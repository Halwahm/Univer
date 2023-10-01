#define _CRT_SECURE_NO_WARNINGS 1;
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1;
#include <iostream>
#include <WinSock2.h>
#include "StringConvert.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleTitle(L"Remote Console"); // заголовок консольного окна

	try
	{
		char ReadBuf[50] = "";// Буффер для примема сообшения от сервера
		char WriteBuf[2] = "";// Буффер для отправки сообщения серверу
		DWORD nBytesRead;
		DWORD nBytesWrite;

		int Code = 0;// Код команды

		char serverName[256];
		char PipeName[512];
		bool result;


		std::cout << "Enter server name: ";
		std::cin >> serverName;
		if (serverName == "") {
			serverName[0] = '.';
			serverName[1] = '\0';
		}
		result = sprintf(PipeName, "\\\\%s\\pipe\\smc", serverName);
		printf("\nCommands:\n 1 - Start  \t \n 2 - Stop  \t \n 3 - Exit  \t \n 4 - Statistics  \n 5 - Wait  \t\n 6 - Shutdown  \t \n 7 - Finish RConsole\t\n 8 - LoadLib \t\n 9 - CloseLib \n\n");

		BOOL fSuccess;

		SECURITY_ATTRIBUTES SecurityAttributes;
		SECURITY_DESCRIPTOR SecurityDescriptor;

		fSuccess = InitializeSecurityDescriptor(
			&SecurityDescriptor,
			SECURITY_DESCRIPTOR_REVISION);

		if (!fSuccess) {
			throw new std::string("InitializeSecurityDescriptor(): Ошибка");
		}

		fSuccess = SetSecurityDescriptorDacl(
			&SecurityDescriptor,
			TRUE,
			NULL,
			FALSE);

		if (!fSuccess) {
			throw new std::string("SetSecurityDescriptorDacl(): Ошибка");
		}

		SecurityAttributes.nLength = sizeof(SecurityAttributes);
		SecurityAttributes.lpSecurityDescriptor = &SecurityDescriptor;
		SecurityAttributes.bInheritHandle = FALSE;

		HANDLE hNamedPipe = CreateFile(get_wstring(PipeName).c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, &SecurityAttributes);

		do
		{
			printf("Command: ");
			scanf("%d", &Code);
			if (Code > 0 && Code < 7)
			{
				sprintf(WriteBuf, "%d", Code - 1);
				if (!WriteFile(hNamedPipe, WriteBuf, strlen(WriteBuf) + 1, &nBytesWrite, NULL))
					throw "WriteFile: Ошибка ";
				if (ReadFile(hNamedPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
					std::cout << ReadBuf << std::endl;
				else
					throw "ReadFile: Ошибка ";

			}
			else if (Code == 8 || Code == 9)
			{
				sprintf(WriteBuf, "%d", Code - 1);
				if (!WriteFile(hNamedPipe, WriteBuf, strlen(WriteBuf) + 1, &nBytesWrite, NULL));
				char dllName[50];
				printf("DLL Name: ");
				std::cin >> dllName;
				if (!WriteFile(hNamedPipe, dllName, strlen(dllName) + 1, &nBytesWrite, NULL))
					throw "WriteFile: Ошибка ";
				if (ReadFile(hNamedPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
					std::cout << ReadBuf << std::endl;
				else
					throw "ReadFile: Ошибка ";
			}
			else if (Code > 9) printf("Неверная команда.\n\n");
		} while (Code != 7 && Code != 3 && Code != 6);
	}
	catch (const char* ErrorPipeText)
	{
		printf("%s", ErrorPipeText);
		std::cout << GetLastError() << std::endl;
	}
	system("pause");
	return 0;
}

std::string GetErrorMsgText(int code)
{
	std::string msgText;
	switch (code)
	{
	default: msgText = "***ERROR***";
		break;
	};
	return msgText;
}
std::string SetPipeError(std::string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}