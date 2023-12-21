﻿#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

#define FILE_PATH L"D:/УНИВЕР/OS/9/OS09_01.txt"

BOOL insRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row);
BOOL printFileTxt(LPWSTR FileName);

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LPWSTR fileName = (LPWSTR)FILE_PATH;

    printFileTxt(fileName);

    insRowFileTxt(fileName, (LPWSTR)L"STR(0)", 0);
    insRowFileTxt(fileName, (LPWSTR)L"STR(-1)", -1);
    insRowFileTxt(fileName, (LPWSTR)L"STR(15)", 15);
    insRowFileTxt(fileName, (LPWSTR)L"STR(7)", 7);

    printFileTxt(fileName);
}

BOOL insRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();

    int rowCount = 1;

    int position = 0;
    int positionAfter = 0;

    bool rowFound = false;

    try
    {
        HANDLE of = CreateFile(
            FileName,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (of == INVALID_HANDLE_VALUE)
            throw "Open file failed";

        LockFile(of, 0, 0, 0, 0);

        if (GetFileSizeEx(of, fileSize))
        {
            char* cstr = new char[wcslen(str) + 1];
            wcstombs(cstr, str, strlen(cstr));

            char* buf = new char[fileSize->QuadPart + 1];
            char* bufAfterIns = new char[fileSize->QuadPart + 3 + strlen(cstr)];

            ZeroMemory(buf, fileSize->QuadPart + 1);
            ZeroMemory(bufAfterIns, fileSize->QuadPart + 3 + strlen(cstr));

            DWORD n = NULL;

            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';

                while (buf[position] != '\0')
                {
                    if ((rowCount == row || row == 0) && !rowFound)
                    {
                        for (int i = 0; i < strlen(cstr); i++)
                        {
                            bufAfterIns[positionAfter++] = cstr[i];
                        }
                        bufAfterIns[positionAfter++] = '\r';
                        bufAfterIns[positionAfter++] = '\n';
                        rowFound = true;
                        rowCount++;
                    }

                    if (buf[position] == '\n')
                    {
                        rowCount++;
                    }

                    bufAfterIns[positionAfter++] = buf[position++];

                    if (buf[position] == '\0')
                    {
                        break;
                    }
                }

                if (row == 0 && buf[0] == '\0') {
                    for (int i = 0; i < strlen(cstr); i++)
                    {
                        bufAfterIns[positionAfter++] = cstr[i];
                    }
                    rowFound = true;
                    rowCount++;
                }

                if (row == MAXDWORD)
                {
                    bufAfterIns[positionAfter++] = '\r';
                    bufAfterIns[positionAfter++] = '\n';

                    for (int i = 0; i < strlen(cstr); i++)
                    {
                        bufAfterIns[positionAfter++] = cstr[i];
                    }

                    rowFound = true;
                    rowCount++;
                }

                bufAfterIns[positionAfter] = '\0';
            }

            if (rowFound)
            {
                int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, bufAfterIns, -1, NULL, 0);

                wchar_t* wideStr = new wchar_t[wideStrLen];
                int result = MultiByteToWideChar(CP_UTF8, 0, bufAfterIns, -1, wideStr, wideStrLen);

                int ansiLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);

                char* ansiStr = new char[ansiLen];
                result = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, ansiStr, ansiLen, NULL, NULL);

                printf("\n--- After insertion row #%d:\n%s\n", row == MAXDWORD ? -1 : row, ansiStr);
                if (SetFilePointer(of, 0, 0, FILE_BEGIN) == 0)
                {

                    if (WriteFile(of, bufAfterIns, strlen(bufAfterIns), &n, NULL))
                    {
                        printf("\nRow inserted successfully\n");
                    }
                    else
                    {
                        CloseHandle(of);
                        throw "WriteFile failed";
                    }

                    if (!SetEndOfFile(of))
                    {
                        CloseHandle(of);
                        throw "SetEndOfFile failed";
                    }
                }
                else
                {
                    CloseHandle(of);
                    throw "SetFilePointer failed";
                }
            }
            else
            {
                CloseHandle(of);
                throw "Row isn't found";
            }
        }
        else
        {
            CloseHandle(of);
            throw "GetFileSizeEx failed";
        }

        CloseHandle(of);
    }
    catch (const char* err)
    {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }

    return true;
}

BOOL printFileTxt(LPWSTR FileName)
{
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation = new BY_HANDLE_FILE_INFORMATION();
    DWORD fileType;
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    try
    {
        HANDLE of = CreateFile(
            FileName,
            GENERIC_READ,
            NULL,
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
            char* buf = new char[fileSize->QuadPart * sizeof(char)];
            ZeroMemory(buf, sizeof(buf));
            DWORD n = NULL;
            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';
                int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);

                wchar_t* wideStr = new wchar_t[wideStrLen];
                int result = MultiByteToWideChar(CP_UTF8, 0, buf, -1, wideStr, wideStrLen);

                int ansiLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);

                char* ansiStr = new char[ansiLen];
                result = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, ansiStr, ansiLen, NULL, NULL);
                printf("\n-- Read file:%d byte successful:\n%s\n", n, ansiStr);
            }
            else
            {
                CloseHandle(of);
                throw "ReadFile failed";
            }
        }
        else
        {
            CloseHandle(of);
            throw "GetFileSizeEx failed";
        }
        CloseHandle(of);
    }
    catch (const char* err)
    {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }
    return true;
}