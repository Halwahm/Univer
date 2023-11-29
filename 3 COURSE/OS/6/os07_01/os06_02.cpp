#include <iostream>
#include <Windows.h>

using namespace std;
DWORD pId = NULL;
CRITICAL_SECTION cs;

DWORD WINAPI ChildThreadFirst()
{
	DWORD tId = GetCurrentThreadId();


	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}
		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}
		cout << "PID = " << pId << ", Child Thread First: " << "tId- " << tId << ": " << i << endl;
		Sleep(100);

		if (i == 60)
		{
			EnterCriticalSection(&cs);
			LeaveCriticalSection(&cs);
		}
	}
	return 0;
}

DWORD WINAPI ChildThreadSecond()
{
	DWORD tId = GetCurrentThreadId();

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}
		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}

		cout << "PID = " << pId << ", Child Thread Second: " << "tId- " << tId << ": " << i << endl;
		Sleep(100);

		if (i == 60)
		{
			EnterCriticalSection(&cs);
			LeaveCriticalSection(&cs);
		}
	}

	return 0;
}

int main()
{
	pId = GetCurrentProcessId();
	DWORD tId = GetCurrentThreadId();
	DWORD childIdFirst = NULL;
	DWORD childIdSecond = NULL;

	HANDLE hChildFirst = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadFirst, NULL, 0, &childIdFirst);
	HANDLE hChildSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadSecond, NULL, 0, &childIdSecond);

	InitializeCriticalSection(&cs);

	for (int i = 1; i <= 90; i++)
	{

		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}
		if (i == 60)
		{
			LeaveCriticalSection(&cs);;
		}
		cout << "PID = " << pId << ", Main Thread: " << "tId- " << tId << ": " << i << endl;
		Sleep(100);
		if (i == 60)
		{
			EnterCriticalSection(&cs);
			LeaveCriticalSection(&cs);
		}
	}
	WaitForSingleObject(hChildFirst, INFINITE);
	WaitForSingleObject(hChildSecond, INFINITE);

	DeleteCriticalSection(&cs);

	CloseHandle(hChildFirst);
	CloseHandle(hChildSecond);

	system("pause");
	return 0;
}


