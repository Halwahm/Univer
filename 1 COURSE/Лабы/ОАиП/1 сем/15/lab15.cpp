#include <iostream>
#include <ctime>

using namespace std;

void v14c1();
void v14c2();
void task1_9();
void task2_3();
void task1_6();

int main()
{
	setlocale(LC_CTYPE, "Russian");
	v14c1();
	v14c2();
	task1_9();
	task2_3();
	task1_6();
	return 0;
}

void v14c1()
{
	srand(time(0));
	int size, i = 0, C, token = 0, max = 0, maxind = 0;
	float* A;
	cout << "Введите размер массива: ";
	cin >> size;
	A = new float[size];
	cout << "Введите C: ";
	cin >> C;
	for (i = 0; i < size; i++)
	{
		A[i] = rand() % 10;
		cout << A[i] << endl;
		if (A[i] > C)
		{
			token++;
		}
		if (abs(A[i] > max))
		{
			maxind = i;
			max = abs(A[i]);
		}
	}
	max = 1;
	for (i = maxind + 1; i < size; i++) 
	{
		max *= A[i];
	}

	cout << endl << "Количество: " << token << endl;
	cout << "Произведение = " << max << endl;
	delete A;
}

void v14c2()
{
	cout << "----------------------------------------------" << endl;
	short n = 0;
	int arr[5][5] = { {1,0,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5} };
	int barr[5][5];

	for (short i = 0; i < 5; i++) 
		for (short j = 0; j < 5; j++) 
		{
			if (arr[i][j] == 0) {
				n++;
			}
		}

	for (short i = 0; i < 5; i++)
	{
		for (short j = 0; j < 5; j++)
		{
			barr[i][j] = arr[i][j] - arr[n][0];
			cout << barr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Нулевой элемент содержит " << n << " строка" << endl;
}

void task1_9()
{
	//В одномерном массиве, состоящем из n вещественных элементов, 
	//вычислить произведение положительных элементов массива и сумму элементов массива,
	//расположенных до минимального элемента.
	cout << "----------------------------------------------" << endl;
	int a[100] = {};
	short n, min = 0, min_i = 0, sum = 0, proiz = 1, i;
	cout << "Введите кол-во элементов: ";
	cin >> n;
	cout << "Введите числа" << endl;
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	min = a[0];
	for (i = 0; i < n; i++)
	{
		if (min > a[i])
		{
			min = a[i];
			min_i = i;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (a[i] > 0)
		proiz *= a[i];
	}
	for (i = 0; i < min_i; i++)
	{
		sum += a[i];
	}
	cout << "Произведение: " << proiz << endl;
	cout << "Сумма: " << sum << endl;
}

void task2_3() //Дана матрица размером 4x4. Найти сумму наименьших элементов ее нечетных строк и наибольших элементов ее четных строк
{
	cout << "----------------------------------------------" << endl;
	srand(time(0));
	int ** A, sz = 4;
	short i = 0, j = 0, min = 100, max = 0, sMin = 0, sMax = 0;
	A = new int* [sz];
	for (i = 0; i < 4; i++)
	{
		A[i] = new int[sz];
		for (j = 0; j < 4; j++)
		{
			A[i][j] = rand() % 99;
			cout << A[i][j] << "\t";
		}
		cout << "\n";
	}

	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			for (j = 0; j < 4; j++)
			{
				if (A[i][j] < min)
				{
					min = A[i][j];
				}
			}
			sMin += min;
			min = 100;
		}

		if (i == 1)
		{
			for (j = 0; j < 4; j++)
			{
				if (A[i][j] > max)
				{
					max = A[i][j];
				}
			}
			sMax += max;
			max = 0;
		}

		if (i == 2)
		{
			for (j = 0; j < 4; j++)
			{
				if (A[i][j] < min)
				{
					min = A[i][j];
				}
			}
			sMin += min;
			min = 100;
		}

		if (i == 3)
		{
			for (j = 0; j < 4; j++)
			{
				if (A[i][j] > max)
				{
					max = A[i][j];
				}
			}
			sMax += max;
			max = 100;
		}
	}
	cout << "Сумма минимальных элементов нечётных строк: " << sMin << endl;
	cout << "Сумма максимальных элементов чётных строк: " << sMax << endl;
	delete A;
}

void task1_6()
{
	cout << "----------------------------------------------" << endl;
	// В одномерном массиве, состоящем из n вещественных элементов, вычислить минимальный 
	// элемент массива и сумму модулей элементов массива, расположенных после первого отрицательного эле-мента.
	short i, min = 0, minind = 0, sum = 0;
	int n;
	cout << "Введите кол-во элементов: ";
	cin >> n;
	int* mas = new int[n];
	cout << "Введите " << n << " элементов" << endl;
	for (i = 0; i < n; i++)
		cin >> mas[i];

	min = mas[0];

	for (i = 0; i < n; i++)
	{
		if (min > mas[i])
		{
			min = mas[i];
			minind = i;

		}
	}
	cout << "min = " << min << endl;

	short first = 0;
	for (i = 0; i < n; i++)
	{
		if (mas[i] < 0) {
			first = i;
			break;
		}
	}
	for  (i = first + 1; i < n; i++)
	{
		sum += mas[i];
	}
	cout << "SUM = " << sum;
	delete mas;
}