#include <Windows.h>
#include <iostream>

using namespace std;

#define FILE_PATH L"D:/УНИВЕР/OS/9/OS09_01.txt"


BOOL printFileTxt(LPWSTR FileName);
BOOL delRowFileTxt(LPWSTR FileName, DWORD row);

int main()
{
    setlocale(LC_CTYPE, "Rus");
    LPWSTR path = (LPWSTR)FILE_PATH;

    delRowFileTxt(path, 1);
    delRowFileTxt(path, 3);
    delRowFileTxt(path, 8);
    delRowFileTxt(path, 10);

    printFileTxt(path);
}


BOOL printFileTxt(LPWSTR path)
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    char buf[1024];
    DWORD countBytes = 0;

    ZeroMemory(buf, sizeof(buf));
    BOOL b = ReadFile(file, &buf, sizeof(buf) - 1, &countBytes, NULL);
    if (!b) throw "read file failed";

    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);

    wchar_t* wideStr = new wchar_t[wideStrLen];
    int result = MultiByteToWideChar(CP_UTF8, 0, buf, -1, wideStr, wideStrLen);

    int ansiLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);

    char* ansiStr = new char[ansiLen];
    result = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, ansiStr, ansiLen, NULL, NULL);

    cout << "\n-- Read file " << countBytes << " byte succesfull:\n" << ansiStr << '\n';
}

BOOL delRowFileTxt(LPWSTR FileName, DWORD row) {
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();

    int rowCount = 1;

    int position = 0;
    int positionAfter = 0;

    bool rowFound = false;

    try {
        if (row <= 0) {
            throw "Invalid number of raw";
        }

        HANDLE of = CreateFile(
            FileName,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (of == INVALID_HANDLE_VALUE) {
            CloseHandle(of);
            throw "Open file failed";
        }

        if (GetFileSizeEx(of, fileSize)) {
            char* buf = new char[fileSize->QuadPart + 1];
            char* bufAfterDel = new char[fileSize->QuadPart + 1];
            ZeroMemory(buf, fileSize->QuadPart);
            ZeroMemory(bufAfterDel, fileSize->QuadPart);
            DWORD n = NULL;

            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL)) {
                buf[fileSize->QuadPart] = '\0';

                while (buf[position] != '\0') {
                    if (buf[position] == '\n') {
                        rowCount++;
                    }

                    if (rowCount == row) {
                        rowFound = true;
                        rowCount++;

                        position++;
                        while (buf[position] != '\n' && buf[position] != '\0') {
                            position++;
                        }

                        if (row == 1) {
                            position++;
                        }
                    }


                    if (position < fileSize->QuadPart) {
                        bufAfterDel[positionAfter++] = buf[position++];
                    }
                    else if (row == 1) {
                        bufAfterDel[0] = '\0';
                        break;
                    }

                    if (buf[position] == '\0') {
                        break;
                    }
                }

                bufAfterDel[positionAfter] = '\0';

                if (bufAfterDel[positionAfter] == '\0' && bufAfterDel[positionAfter - 1] == '\r') {
                    bufAfterDel[positionAfter - 1] = '\0';
                }
                else {
                    bufAfterDel[positionAfter] = '\0';
                }
            }

            if (rowFound) {
                if (SetFilePointer(of, 0, 0, FILE_BEGIN) == 0) {
                    if (WriteFile(of, bufAfterDel, strlen(bufAfterDel), &n, NULL)) {
                        std::cout << "Row deleted successfully #" << row << std::endl;
                    }
                    else {
                        CloseHandle(of);
                        throw "WriteFile failed";
                    }

                    if (!SetEndOfFile(of)) {
                        CloseHandle(of);
                        throw "SetEndOfFile failed";
                    }
                }
                else {
                    CloseHandle(of);
                    throw "SetFilePointer failed";
                }
            }
            else {
                CloseHandle(of);
                throw "Row isn't found";
            }
        }
        else {
            CloseHandle(of);
            throw "GetFileSizeEx failed";
        }

        CloseHandle(of);
    }
    catch (const char* err) {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }

    return true;
}