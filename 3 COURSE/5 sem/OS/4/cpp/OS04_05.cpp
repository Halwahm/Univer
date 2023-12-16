#include <Windows.h>
#include <iostream>

DWORD pid = NULL;
using namespace std;


DWORD WINAPI ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		cout << i << " " << "\nOS04_05_T1: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;

}

DWORD WINAPI ChildSecondThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		cout << i << " " << "\nOS04_05_T2: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
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

		cout << i << " " << "\nParent Thread: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
		if (i == 40) {
			cout << "\n Terminate OS04_05_T2 \n";
			TerminateThread(hChildSecond, -1);
		}
	}

	WaitForSingleObject(hChild, INFINITE);
	CloseHandle(hChild);

}















// TerminateThread(hChildSecond, -1);
// поток с дескриптором hChildSecond должен быть немедленно завершен, и код завершения для этого потока будет -1.
