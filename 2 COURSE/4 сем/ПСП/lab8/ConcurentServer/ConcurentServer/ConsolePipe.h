#pragma once
#define _CRT_SECURE_NO_WARNINGS 1;
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1;
#include "Global.h"
#include "StringConvert.h"

DWORD WINAPI ConsolePipe(LPVOID pPrm)
{
	std::cout << "ConsolePipe started;\n" << std::endl;
	HANDLE hPipe;
	DWORD rc = 0;
	try
	{
		BOOL fSuccess;

		//��������� ��������� ������������
		SECURITY_ATTRIBUTES SecurityAttributes;
		SECURITY_DESCRIPTOR SecurityDescriptor;

		fSuccess = InitializeSecurityDescriptor(
			&SecurityDescriptor,
			SECURITY_DESCRIPTOR_REVISION);

		if (!fSuccess) {
			throw new string("InitializeSecurityDescriptor():");
		}

		fSuccess = SetSecurityDescriptorDacl(
			&SecurityDescriptor,
			TRUE,
			NULL,
			FALSE);

		if (!fSuccess) {
			throw new string("SetSecurityDescriptorDacl():");
		}

		SecurityAttributes.nLength = sizeof(SecurityAttributes);
		SecurityAttributes.lpSecurityDescriptor = &SecurityDescriptor;
		SecurityAttributes.bInheritHandle = FALSE;

		//�������� ������������ ������
		char rnpname[50];
		strcpy(rnpname, "\\\\.\\pipe\\");  //301fit
		strcat(rnpname, npname);
		if ((hPipe = CreateNamedPipe(get_wstring(rnpname).c_str(),
			PIPE_ACCESS_DUPLEX,           //���������� ����� 
			PIPE_TYPE_MESSAGE | PIPE_WAIT,  // ���������|����������
			1, NULL, NULL,                 // �������� 1 ���������
			INFINITE, &SecurityAttributes)) == INVALID_HANDLE_VALUE)
			throw SetErrorMsgText("Create:", GetLastError());

		while (*((TalkersCmd*)pPrm) != Exit) //���� ������
		{
			if (!ConnectNamedPipe(hPipe, NULL))           // ������� �������   
				throw SetErrorMsgText("Connect:", GetLastError());
			char ReadBuf[50], WriteBuf[50];
			DWORD nBytesRead = 0, nBytesWrite = 0;
			TalkersCmd SetCommand;
			bool Check;
			HMODULE st;
			HANDLE(*ts)(char*, LPVOID);
			char dllName[256];
			while (*((TalkersCmd*)pPrm) != Exit)
			{
				if (*((TalkersCmd*)pPrm) == Getcommand) {

					if (!ReadFile(hPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
						break;
					if (nBytesRead > 0)
					{
						Check = true;
						int n = atoi(ReadBuf);
						switch (n)
						{
						case 0:
							sprintf(WriteBuf, "%s", "Start");
							SetCommand = TalkersCmd::Start;
							break;
						case 1:
							sprintf(WriteBuf, "%s", "Stop");
							SetCommand = TalkersCmd::Stop;
							break;
						case 2:
							sprintf(WriteBuf, "%s", "Exit");
							SetCommand = TalkersCmd::Exit;
							break;
						case 3:
							sprintf(WriteBuf, "\nAccept: %i\nFail: %i\nFinished: %i\nWork: %i\n", Accept, Fail, Finished, Work);
							Check = false;
							break;
						case 4:
							sprintf(WriteBuf, "%s", "Wait");
							SetCommand = TalkersCmd::Wait;
							break;
						case 5:
							sprintf(WriteBuf, "%s", "Shutdown");
							SetCommand = TalkersCmd::Shutdown;
							break;
						case 7:
							if (!ReadFile(hPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
								break;
							st = LoadLibrary(get_wstring(ReadBuf).c_str()); //��������� dll
							vList.push_back(st);
							ts = (HANDLE(*)(char*, LPVOID))GetProcAddress(st1, "SSS"); //����������� �������
							vArray.push_back(ts);
							sprintf(WriteBuf, "%s", "DLL Load");
							Check = false;
							break;
						case 8:
							if (!ReadFile(hPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
								break;
							for (int i = 0; i < vList.size(); i++)
							{
								GetModuleFileName(vList[i], (LPWSTR)get_wstring(dllName).c_str(), 256);
								if (strstr(dllName, ReadBuf) != NULL)
								{
									FreeLibrary(vList[i]);
									sprintf(WriteBuf, "%s", "DLL Free");
									break;
								}
								else
								{
									sprintf(WriteBuf, "%s", "DLL Error");
								}
							}
							Check = false;
							break;
						default:
							sprintf(WriteBuf, "%s", "NoCmd");
							Check = false;
							break;
						}
						if (Check == true)
						{
							*((TalkersCmd*)pPrm) = SetCommand;
							printf("ConsolePipe: ������� %s\n", WriteBuf);
						}

						if (!WriteFile(hPipe, WriteBuf, sizeof(WriteBuf), &nBytesRead, NULL))
							throw new string("CP WRITE ERROR");
					}
				}
				else Sleep(1000);
			}
			if (!DisconnectNamedPipe(hPipe))           // ��������� �������   
				throw SetErrorMsgText("disconnect:", GetLastError());
		}
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
		std::cout << "ConsolePipe stoped;\n" << std::endl;
	}
	catch (string ErrorPipeText)
	{
		std::cout << ErrorPipeText << std::endl;
	}
	ExitThread(rc);
}