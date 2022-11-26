#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

//e^x + x - 4,
//x^2 – 4

	float koren(float a, float b, float (*f)(float))
	{
			float x, e = 0.001;
			do
			{
				x = (a + b) / 2;
				if (f(x) * f(a) <= 0)
					b = x;
				else a = x;
			} while (abs(a - b) > 2 * e);
			cout << x << endl;
			return x;
	}

	float f1(float x)
{
	float z = exp(x) + x - 4;
	return z;
}

float f2(float x)
{
	float z = pow(x, 2) - 4;
	return z;
}

/*Написать функцию compr, которая «сжимает» строку, удаляя из нее все пробелы. 
С ее помощью сжать различные строки.*/

void compr()
{
	cout << endl << "----------------------" << endl;
	const int n = 10;
	int point = 0;
	char mas1[n];
	char mas2[n]; 
	cout << "Введите 9 символов с пробелами" << endl;
	gets_s(mas1);
	for (int i = 0; i < n; i++)
	{
		if (mas1[i] != ' ')
		{
			mas2[point] = mas1[i];
			cout << mas2[point];
			point++;
		}
	}
}


/*Написать функцию fmax с переменным числом параметров, которая находит
минимальное из чисел типа int или из чисел типа double, тип параметров
определяется с помощью первого параметра функции.*/

int fmax(int a, ...)
{
	cout << endl << "----------------------" << endl;
	int *p = &a;
	short min = 100;
	for (short i = 0; i < a; i++)
	{
		if (*(++p) < min)
			min = *p;
	}
	cout << min;
	return min;
}


/*Написать функцию fmin с переменным числом параметров, в которой определяется минимальное из чисел типа int*/

int fmin(int n, ...)
{
	cout << endl << "----------------------" << endl;
	int* p = &n;
	int min = *p;

	while (*p)
	{
		if (*(p) < min)
			min = *(p);
		p++;
	}
	return min;
}
void v_1_2()
{
	cout 
		<< fmin(1, 3, 8, 5, 7, 4, 0) << endl
		<< fmin(4, 346, 234, 53, 36, 5, 0) << endl;
}

/*Написать функцию, которая в предложении подсчитывает количество символов в
слове максимальной длины (слова разделяются пробелами). Опробовать работу
функции на нескольких предложениях. */

void StrSym()
{
	cout << endl << "----------------------" << endl;
	char* Size = new char[256];
	cout << "Введите предложение, заканчивающееся точкой:\n";
	cin.getline(Size, 256, '.');
	short i = 0, Probel = 0, LastP = 0, Length = strlen(Size), Max = 0;
	while (i != Length)
	{
		if (*(Size + i) == ' ')
		{
			Probel = i;
			short Word = Probel - LastP - 1;
			if (Word > Max)
			{
				Max = Word;
			}
			LastP = Probel;
		}
		i++;
	}
	cout << "Максимальное количество букв в слове: " << Max;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");

	compr();

	cout << endl << "----------------------" << endl;

	float aa, bb;
	cout << "Enter a: " << endl;
	cin >> aa;
	cout << "Enter b: " << endl;
	cin >> bb;
	float* a = &aa;
	float* b = &bb;
	koren(*a, *b, f1);
	koren(*a, *b, f2);

	fmax(8, 5, 12, 89, -42, 45, -13, 98);

	v_1_2();

	StrSym();

	return 0;
}