﻿#include <iostream>
#include <clocale>
#include <ctime>
#include "ErrorMessage.h"
#include "Windows.h"
#define NAME L"\\\\.\\mailslot\\Box"
using namespace std;


int main()
{
    setlocale(LC_ALL, "rus");
    HANDLE sH;
    DWORD rb, time = 1800000, nMaxMessageSize = 1000;
    clock_t start, end;
    char rbuf[300];
    bool flag = true;

    try
    {
        if ((sH = CreateMailslot(NAME, nMaxMessageSize, time, NULL)) == INVALID_HANDLE_VALUE)
            throw SetPipeError("CreateMailslot: ", GetLastError());

        while (true)
        {
            if (!ReadFile(sH, rbuf, sizeof(rbuf), &rb, NULL))
                throw SetPipeError("ReadFile: ", GetLastError());

            else
            {
                if (flag)
                {
                    start = clock();
                    flag = false;
                }
            }

            if (strcmp(rbuf, "STOP") == 0)
            {
                end = clock();
                cout << "\n[INFO] Time elapsed: " << ((double)(end - start) / CLK_TCK) << " seconds" << endl;
                flag = true;
            }
            cout << rbuf << endl;
        }

        if (!CloseHandle(sH))
            throw SetPipeError("CloseHandle: ", GetLastError());

    }
    catch (string ErrorPipeText)
    {
        cout << endl << ErrorPipeText;
    }
}