#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"smwMutex");
	if (hm == NULL)
	{
		cout << "os06_03A: Open err Mutex\n";
	}
	else
	{
		cout << "OS06_03A: Open  Mutex\n";
	}

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hm, INFINITE);
		}
		if (i == 60)
		{
			ReleaseMutex(hm);
		}
		Sleep(100);
		cout << "os06_03A: " << i << " PID: " << GetCurrentProcessId() << endl;

	}

	system("pause");
}









//
//HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"smwMutex");
//dwDesiredAccess: Указывает желаемые права доступа к мьютексу.В данном случае SYNCHRONIZE означает право на 
// синхронизацию(или ожидание) мьютекса.
//
//bInheritHandle : Если это значение TRUE, дескриптор мьютекса может быть унаследован потомками процесса.Если FALSE, 
// дескриптор не наследуется.
//
//lpName : Указатель на строку с уникальным именем мьютекса.