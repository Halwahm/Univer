#include <iostream>
#include <Windows.h>
#include <atomic>
#include <thread>
#include <ctime>

using namespace std;
int chng = 0;
DWORD WINAPI Thread();

int main() {

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, NULL);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, NULL);
	ResumeThread(hChild);
	ResumeThread(hChild2);
	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChild2);
	system("pause");
}

void start_critical_section(void)
{
	__asm {
	SpinLoop:
		lock bts chng, 0;
		jc SpinLoop
	}
}

void exit_critical_section(void)
{
	__asm lock btr chng, 0
}

DWORD WINAPI Thread()
{
	DWORD tid = GetCurrentThreadId();
	int firrtTime = clock();
	start_critical_section();
	for (int i = 1; i < 91; i++)
	{
		cout << "Thread: " << tid << "  " << i << endl;
	}
	exit_critical_section();
	return 0;
}
