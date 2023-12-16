#include <iostream>
#include<Windows.h>
#include <process.h>

using namespace std;

int main()
{
    LPCWSTR chp1 = L"D:\\УНИВЕР\\OS\\3\\OS03_02_1.exe"; // UTF-16
    LPCWSTR chp2 = L"D:\\УНИВЕР\\OS\\3\\OS03_02_2.exe";

    STARTUPINFO w1; // структура, исп для настройки атрибутов нового процесса
    STARTUPINFO w2;

    PROCESS_INFORMATION pi1;     // информация о созданном процессе и его первичном потоке
    PROCESS_INFORMATION pi2;

    //заполняет блок памяти нулями.
    //1-указатель на блок памяти, 2-размер блока памяти
    ZeroMemory(&w1, sizeof(STARTUPINFO)); w1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&w2, sizeof(STARTUPINFO)); w2.cb = sizeof(STARTUPINFO);

    // путь, cmd, 2 указателя на структуру для настройки атрибутов безопасности процесса и потока, нет наследования,
    // имеем собственное окно консоли, не исп текущий каталог для нового процесса, 
    // пустой указатель на структуру STARTUPINFO, структура в кот сохр инфа о созд процессе 
    if (CreateProcess(chp1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &w1, &pi1))
        cout << "-- Process OS03_02_1 created" << endl;
    else {
        cout << "-- Process OS03_02_1 not created" << endl;
    }

    if (CreateProcess(chp2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &w2, &pi2))
        cout << "-- Process OS03_02_2 created" << endl;
    else {
        cout << "-- Process OS03_02_2 not created" << endl;
    }

    for (int i = 0; i < 100; i++) {
        cout << i << "  OS03_02 " << " PID:" << _getpid() << endl;
        Sleep(1000);
    }

    WaitForSingleObject(
        pi1.hProcess, 
        INFINITE      
    );
    WaitForSingleObject(pi2.hProcess, INFINITE); 
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
}