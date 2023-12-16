#include <Windows.h>
#include <iostream>

DWORD pid = NULL;
bool flag = false;
using namespace std;

DWORD WINAPI ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		cout << i << " " << "\nOS04_03_T1: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI ChildSecondThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		cout << i << " " << "\nOS04_03_T2: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
		if (i == 124) {
			flag = true;
			cout << "\nWakeup Parent Thread \n";
			exit(0);
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
		if (i == 20) {
			SuspendThread(hChild);
			cout << "\nSuspend OS04_03_T1 \n";
		}
		else if (i == 60) {
			ResumeThread(hChild);
			cout << "\nResume OS04_03_T1 \n";
		}

		if (i == 40) {
			SuspendThread(hChildSecond);
			cout << "\nSuspend OS04_03_T2 \n";
		}
	}
	ResumeThread(hChildSecond);
	cout << "\nResume OS04_03_T2 \n";
	cout << "\nSuspend Parent Thread \n";
	Sleep(10000000);


	WaitForSingleObject(hChild, INFINITE);
	CloseHandle(hChild);

}
