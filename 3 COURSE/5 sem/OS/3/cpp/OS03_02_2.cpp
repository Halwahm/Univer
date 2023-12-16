#include <iostream>
#include<Windows.h>
#include <process.h>

using namespace std;

int main()
{
    for (int i = 0; i < 125; i++) {
        cout << i << "  OS03_02_02 " << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }

}