﻿#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "Windows.h"
#define FILE_PATH L"D:/УНИВЕР/OS/9/OS09_03.txt"
#define DIR_PATH  L"D:/УНИВЕР/OS/9/"

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec);

int rowC = 0;
int main(){
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LPWSTR fileName = (LPWSTR)FILE_PATH;
    printWatchRowFileTxt(fileName, 30000);
}

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    LPWSTR path = (LPWSTR)DIR_PATH;
    char* cFileName = new char[wcslen(FileName) * sizeof(char) + 1];
    wcstombs(cFileName, FileName, strlen(cFileName));
    int i = 0;
    int lenName = 0;
    printf("File catalog:%s \n", path);
    try
    {
        HANDLE notif = FindFirstChangeNotification(path, false, FILE_NOTIFY_CHANGE_LAST_WRITE);
        DWORD err = GetLastError();
        clock_t t1 = clock();
        clock_t t2 = clock();
        DWORD dwWaitStatus;
        printf("\nWatch started:", t1);
        while (true)
        {
            dwWaitStatus = WaitForSingleObject(notif, mlsec);
            switch (dwWaitStatus)
            {
            case WAIT_OBJECT_0:
            {
                if (FindNextChangeNotification(notif) == FALSE)
                {
                    break;
                }
                else
                {
                    int position = 0;
                    int rowCount = 0;
                    HANDLE of = CreateFile(
                        FileName,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
                    if (of == INVALID_HANDLE_VALUE)
                    {
                        CloseHandle(of);
                        throw "Open file failed";
                    }
                    if (GetFileSizeEx(of, fileSize))
                    {
                        char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
                        ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));
                        DWORD n = NULL;
                        if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
                        {
                            while (buf[position++] != '\0')
                            {
                                if (buf[position] == '\n')
                                {
                                    rowCount++;
                                }
                            }
                        }
                    }
                    if (rowC != rowCount)
                    {
                        printf("\n Row quantity: %d", rowCount);
                        rowC = rowCount;
                    }
                    CloseHandle(of);
                }
            }
            }
            t2 = clock();
            if (t2 - t1 > mlsec)
            {
                break;
            }
            
        }
        CloseHandle(notif);
        printf("\n Watch ended timestamp %d:", t2);
    }
    catch (const char* err)
    {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }
    return true;
}
