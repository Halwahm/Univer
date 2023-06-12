#include "Auxil.h"                            // вспомогательные функции 
#include <iostream>
#include <ctime>
#include <locale>
#define  CYCLE  1000000                       // количество циклов  
using namespace std;

int main()
{
	double  av1 = 0, av2 = 0;
	clock_t  t1 = 0, t2 = 0;
	setlocale(LC_ALL, "rus");
	auxil::start();                          // старт генерации 
	// фиксация времени 
	for (int j = 1; j <= 10; j++) {
		t1 = clock();
		for (int i = 0; i < j * CYCLE; i++)
		{
			av1 += (double)auxil::iget(-100, 100); // сумма случайных чисел 
			av2 += auxil::dget(-100, 100);         // сумма случайных чисел 
		}
		t2 = clock();                            // фиксация времени 
		cout << endl << "количество циклов:         " << CYCLE * j;
		cout << endl << "среднее значение (int):    " << av1 / (CYCLE * j);
		cout << endl << "среднее значение (double): " << av2 / (j * CYCLE);
		cout << endl << "продолжительность (у.е):   " << (t2 - t1);
		cout << endl << "                  (сек):   "
			<< ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
		cout << endl;
		av1 = 0;
		av2 = 0;
	}
	return 0;
}