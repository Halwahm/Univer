//main
#include <iostream>
#include <iomanip> 
#include <tchar.h>
#include <stdio.h>
#include "Salesman.h"
#define N 5
int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");
    int d[N][N] = { //0   1     2    3     4        
                   { INF,  20,  31,  INF,  10},    //  0
                   { 10,   INF, 25,  58,   74},    //  1
                   { 12,    30,  INF, 86,   59},    //  2 
                   { 27,   48,  40,  INF,  30},    //  3
                   { 83,   76,  52,  23,   INF} };   //  4 
    int r[N];                     // результат 
    int s = salesman(
        N,          // [in]  количество городов 
        (int*)d,          // [in]  массив [n*n] расстояний 
        r           // [out] массив [n] маршрут 0 x x x x  

    );
    std::cout << std::endl << "-- Задача коммивояжера -- ";
    std::cout << std::endl << "-- количество  городов: " << N;
    std::cout << std::endl << "-- матрица расстояний : ";
    for (int i = 0; i < N; i++) {
        std::cout << std::endl;
        for (int j = 0; j < N; j++)
            if (d[i][j] != INF) std::cout << std::setw(3) << d[i][j] << " ";
            else std::cout << std::setw(3) << "INF" << " ";
    }
    std::cout << std::endl << "-- оптимальный маршрут: ";
    for (int i = 0; i < N; i++) std::cout << r[i] + 1 << "-->"; std::cout << 1;
    std::cout << std::endl << "-- длина маршрута     : " << s;
    std::cout << std::endl;
    return 0;
}