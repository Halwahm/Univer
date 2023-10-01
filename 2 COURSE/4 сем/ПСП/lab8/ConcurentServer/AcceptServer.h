#pragma once
#include "Global.h"


static void WaitClients() 
{
	bool ListEmpty = false;
	while(!ListEmpty) 
	{
		// ��������� ������� ��������
		EnterCriticalSection(&scListContact);
		ListEmpty = Contacts.empty();
		LeaveCriticalSection(&scListContact);\
		// ��� (�������� ����������� ���������)
		SleepEx(1, TRUE);
	}
}

bool AcceptCycle(int squirt, SOCKET* s, bool isCanConnect)
{	
	bool rc = false;
	// ������� ����� Contact
	Contact c(Contact::ACCEPT,(char*)"AcceptServer");
	// �������� HANDLE �������������� ������
	c.hAcceptServer=hAcceptServer;


	if ((c.s = accept(*s,(sockaddr*)&c.prms, &c.lprms)) == INVALID_SOCKET)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK) 
			throw  SetErrorMsgText("Accept:",WSAGetLastError());
	}
	else //���� �����������
	{
		if (isCanConnect) {
			rc = true;
			InterlockedIncrement(&Accept);// ����������� ���-�� ����� �����������
			InterlockedIncrement(&Work);  // ����������� ���-�� ������� �����������
			EnterCriticalSection(&scListContact);
			Contacts.push_front(c);
			LeaveCriticalSection(&scListContact);
			SetEvent(Event); // ��������� ������� � ���������� ���������
		}
		else {
			char errorMsg[] = "Server in wait state, Can't connect.";
			send(c.s, errorMsg, strlen(errorMsg) + 1, NULL);
		}

	}
	return rc;  
};

void CommandsCycle(TalkersCmd& cmd, SOCKET* s)      // ���� ��������� ������
{
	int squirt = 0;
	while (cmd!=Exit)     // ���� ��������� ������ ������� � �����������
	{	
		bool CanConnect = true;
		switch (cmd)   
		{
		case Start:  //����������� ����������� ��������
			cmd=Getcommand; 
			CanConnect = true;
			squirt=AS_SQUIRT; 
			break; 
		case Stop:  //���������� ����������� �������� 
			cmd=Getcommand;   
			CanConnect = false;
			squirt = 0;
			break;
		case Wait:  //���������� �������, � ����� ��������� ����������� ����� ��������
			WaitClients();
			CanConnect = false;
			cmd=Getcommand;
			squirt=AS_SQUIRT;
			break;	
		case Shutdown:  //���������� �������, � ����� ��������� ������
			WaitClients();
			CanConnect = false;
			cmd=Exit;
			break;			
		}; 

		if(cmd != Exit && squirt>Work)
		{
			if (AcceptCycle(squirt, s, CanConnect))   //����  ������/����������� (accept) 
			{
				cmd = Getcommand;      
			}    
			SleepEx(0, TRUE);
		} 	

	}
};

// ��������� ������� ��������� �������� �� ����������� ��������
DWORD WINAPI AcceptServer (LPVOID pPrm)
{
	cout<<"AcceptServer started\n"<<endl;
	DWORD rc = 0; //��� ��������  
	SOCKET  ServerSocket;
	WSADATA wsaData;  

	try
	{
		// �������������� Winsocket 
		if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:",WSAGetLastError());

		// ������� ����� ������� ��� ������ ����������� ��������
		if ((ServerSocket = socket(AF_INET, SOCK_STREAM, NULL))== INVALID_SOCKET) 
			throw  SetErrorMsgText("Socket:",WSAGetLastError());

		// ��������� ������ �������
		SOCKADDR_IN Server_IN;  
		Server_IN.sin_family  = AF_INET;
		Server_IN.sin_port = htons(port);
		Server_IN.sin_addr.s_addr =ADDR_ANY;
		// ��������� ��������� � ������
		if (bind(ServerSocket,(LPSOCKADDR)&Server_IN, sizeof(Server_IN))== SOCKET_ERROR)
			throw  SetErrorMsgText("Bind:",WSAGetLastError());

		// ��������� ����� � ����� �������������
		if (listen(ServerSocket,SOMAXCONN)== SOCKET_ERROR)  
			throw  SetErrorMsgText("Listen:",WSAGetLastError());

		// ��������� ����� � ������������� �����
		u_long nonblk;  
		if (ioctlsocket( ServerSocket, FIONBIO, &(nonblk = 1)) == SOCKET_ERROR)
			throw SetErrorMsgText("Ioctlsocket:",WSAGetLastError());

		TalkersCmd* command = (TalkersCmd*)pPrm;
		// ������� ������������ ��������� �� �������
		CommandsCycle(*((TalkersCmd*)command),&ServerSocket);

		// ��������� �����
		if (closesocket(ServerSocket)== SOCKET_ERROR)
			throw  SetErrorMsgText("�losesocket:",WSAGetLastError());
		// ������� �������
		if (WSACleanup()== SOCKET_ERROR)         
			throw  SetErrorMsgText("Cleanup:",WSAGetLastError());
	}
	catch (string errorMsgText)
	{ 
		std::cout<<errorMsgText<<endl;
	}
	cout<<"AcceptServer stoped;\n"<<endl;
	// ������� �� ������
	ExitThread(rc);  
}

