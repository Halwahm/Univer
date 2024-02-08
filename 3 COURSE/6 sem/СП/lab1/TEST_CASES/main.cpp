﻿#include "tests.h"

using namespace std;

int main()
{
    ht::HtHandle* ht = ht::create(1000, 3, 10, 256, L"./files/HTspace.ht");
    if (!ht)
        throw "-- create: error";

    // Тест 1: Повторная вставка элемента
    if (tests::test1(ht))
        cout << "-- test1: success" << endl;
    else
        cout << "-- test1: error" << endl;

    // Тест 2: Попытка удаления несуществующего элемента
    if (tests::test2(ht))
        cout << "-- test2: success" << endl;
    else
        cout << "-- test2: error" << endl;

    // Тест 3: Попытка удаления несуществующего элемента
    if (tests::test3(ht))
        cout << "-- test3: success" << endl;
    else
        cout << "-- test3: error" << endl;

    // Тест 4: Повторная вставка элемента
    if (tests::test4(ht))
        cout << "-- test4: success" << endl;
    else
        cout << "-- test4: error" << endl;

    if (ht != nullptr)
        if (ht::close(ht))
            cout << "-- close: success" << endl;
        else
            throw "-- close: error";

    return 0;
}