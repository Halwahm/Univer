#include <Windows.h>
#include <iostream>

DWORD pid = NULL;
bool flag = false;
using namespace std;


DWORD WINAPI ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		cout << i << " " << "\nOS04_04_T1: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
		if (i == 25) {
			cout << "\nSuspend OS04_04_T1 \n";
			Sleep(10000);
			cout << "\nWakeup OS04_04_T1 \n";
		}
	}

	return 0;
}

DWORD WINAPI ChildSecondThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		cout << i << " " << "\nOS04_04_T2: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
		if (i == 80) {
			cout << "\nSuspend OS04_04_T2 \n";
			Sleep(15000);
			cout << "Wakeup OS04_02_T2 \n";
		}
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
		if (i == 30) {
			cout << "\nSuspend  Parent Thread\n";
			Sleep(10000);
			cout << "\nWakeup Parent Thread\n";
		}
	}

	WaitForSingleObject(hChild, INFINITE);
	CloseHandle(hChild);

}
