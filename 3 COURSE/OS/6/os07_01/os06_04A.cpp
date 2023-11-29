#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{

	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"smwSem");
	if (hs == NULL)
	{
		cout << "os06_04A: Open error Semaphore\n";
	}
	else
	{
		cout << "OS06_04A: Open Semaphore\n";
	}

	LONG prevcount = 0;
	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hs, INFINITE);
		}
		if (i == 60)
		{
			ReleaseSemaphore(hs, 1, &prevcount);
			cout << "os06_04A: prevcount = " << prevcount << endl;
		}
		Sleep(100);
		cout << "os06_03A: " << i << " PID: " << GetCurrentProcessId() << endl;
	}

	CloseHandle(hs);
	system("pause");

	return 0;
}













//dwDesiredAccess: Режим доступа к семафору.В вашем случае, SEMAPHORE_ALL_ACCESS предоставляет полный доступ к семафору.

//bInheritHandle : Если этот параметр установлен в TRUE, то новый дескриптор может быть унаследован дочерними процессами.
//В вашем случае, FALSE означает, что дескриптор не должен наследоваться.

//lpName : Имя семафора.Должно быть уникальным в пределах системы.В вашем примере это "smwSem".


//помимо SEMAPHORE_ALL_ACCESS могут быть
//SEMAPHORE_MODIFY_STATE: Позволяет изменять состояние семафора.Это включает в себя увеличение и уменьшение счетчика 
// семафора.
//
//READ_CONTROL : Позволяет читать информацию о семафоре, такую как владелец и права доступа.
//
//SYNCHRONIZE : Позволяет использовать семафор в функциях синхронизации, таких как WaitForSingleObject или 
//WaitForMultipleObjects.