#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Levenshtein.h"

int main()
{
	setlocale(LC_ALL, "rus");
	clock_t t1 = 0, t2 = 0, t3, t4;
	char x[301], y[201];

	srand(time(0));

	for (int i = 0; i < 300; i++)
	{
		x[i] = ('a' + rand() % ('z' - 'a'));
		std::cout << x[i];
	}

	std::cout << std::endl;

	for (int i = 0; i < 200; i++)
	{
		y[i] = ('a' + rand() % ('z' - 'a'));
		std::cout << y[i];
	}

	double dividers[7] = { 1.0 / 25.0, 1.0 / 20.0, 1.0 / 15.0, 1.0 / 10.0, 1.0 / 5.0, 1.0 / 2.0, 1.0 };

	int  lx = sizeof(x) - 1, ly = sizeof(y) - 1;
	std::cout << std::endl;
	std::cout << std::endl << "-- расстояние Левенштейна -----" << std::endl;
	std::cout << std::endl << "--длина --- рекурсия -- дин.програм. ---"
		<< std::endl;
	for (int i = 0; i < 7; i++)
	{

		//t1 = clock(); levenshtein_r(lx * dividers[i], x, ly * dividers[i], y); t2 = clock();
		t3 = clock(); levenshtein(lx * dividers[i], x, ly * dividers[i], y); t4 = clock();
		std::cout << std::right << std::setw(2) << 1 << "/" << std::setw(2) << 1 / (double)dividers[i]
			<< "        " << std::left << std::setw(10) << (t2 - t1)
			<< "   " << std::setw(10) << (t4 - t3) << std::endl;
	}
	system("pause");
	return 0;
}