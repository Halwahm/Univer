// Salesman.h
#define INF   0x7fffffff    // бесконечность
#include "Combi3.h"
int salesman(     // функция возвращает длину оптимального маршрута
	int n,        // кол-во городов
	const int* d,  // массив [n*n] расстояний
	int* r     // массив [n] маршрут
);