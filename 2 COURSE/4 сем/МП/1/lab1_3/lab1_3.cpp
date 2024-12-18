﻿#include <iostream>
#include <ctime>

using namespace std;

/*
Числа Фибоначчи (строка Фибоначчи) — числовая последовательность, 
первые два числа которой являются 0 и 1, а каждое последующее за ними число 
является суммой двух предыдущих.
*/

int fib(int n) {
    if (n > 0) {
        // выводим числа Фибоначчи от 1 до n-1
        fib(n - 1);
        // выводим n-ое число Фибоначчи
        cout << (n <= 2 ? 1 : fib(-(n - 1)) + fib(-(n - 2))) << endl;
    }
    else {
        n *= -1;
    }
    return n <= 2 ? 1 : fib(-(n - 1)) + fib(-(n - 2));
}

int main()
{
    setlocale(LC_ALL, "rus");
    clock_t  t1 = 0, t2 = 0;
    for (int j = 1; j <= 10; j++) {
        t1 = clock();
        for (int k = 1; k <= 1; k++) {
            fib(10);
        }
        t2 = clock();

        cout << endl << "продолжительность (у.е):   " << (t2 - t1);
        cout << endl << "                  (сек):   "
            << ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
        cout << endl;
    }
    return 0;
}

/*
Функция fib работает так, что, если в неё передаётся положительное число n, 
то она выводит первые n чисел Фибоначчи и возвращает n-ое число Фибоначчи,
а если передаётся отрицательное число n, то возвращает -n-ое число Фибоначчи 
(без вывода)
*/