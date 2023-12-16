#include <Windows.h>
#include <iostream>

DWORD pid = NULL;
using namespace std;

DWORD WINAPI ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		cout << i << " " << "OS04_02_T1: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI ChildSecondThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		cout << i << " " << "OS04_02_T2: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;
}



int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD childId = NULL;
	DWORD childSecondId = NULL;

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &childId);
	HANDLE hChildSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildSecondThread, NULL, 0, &childSecondId);

	for (int i = 0; i < 100; i++)
	{
		cout << i << " " << "Parent Thread: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	WaitForSingleObject(hChild, INFINITE);
	CloseHandle(hChild);
}