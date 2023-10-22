#include <iostream>
#include<Windows.h>
#include <process.h>

using namespace std;

int main()
{
    for (int i = 0; i < 50; i++) {
        cout << i << "  OS03_02_01 " << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }
}