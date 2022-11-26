#include <iostream>
using namespace std;
void v14c1();
void v14c2();
void v2c1();
void v3c1();
void v5c2();

int main()
{
    setlocale(LC_CTYPE, "Russian");
    v14c1();
    v14c2();
	v2c1();
	v3c1();
	v5c2();
    return 0;
}

void v14c1() 
{
	const int i = 30, j = 40;
	int n, x[i], y[j], g, schetchik = 0;
	cout << "Введите размер массива (до 30): ";
	cin >> n;
	cout << "Введите размер массива (до 40): ";
	cin >> g;
	cout << "====================" << endl;

	//Заполняем массив X
	for (int f = 0; f < n; f++)
		x[f] = rand() % 7;
	
	int* px = x;
	for (int f = 0; f < n; f++)
	{
		cout << "Указатель на первый массив: " << * (px + f) << endl;
	}
	cout << "====================" << endl;

	//Заполняем массив Y
	for (int f = 0; f < g; f++)
		y[f] = rand() % 7;

	int* py = y;
	for (int f = 0; f < g; f++)
		cout << "Указатель на второй массив: " << * (py + f) << endl;
	
	cout << "====================" << endl;
	for (int z = 0; z < n; z++) //Массив X 
	{
		for (int v = 0; v < g; v++) //Массив Y
		{
			if (*(px + z) == *(py + v))
			{
				schetchik = schetchik + 1;
				cout << z + 1 << "-й " << "элемент массива X равен " << v + 1 << "-ому " << "элементу массива Y" << endl;
			}
		}
	}
	cout << endl << "Количество пар одинаковых элементов = " << schetchik << endl;
}

void v14c2() 
{
	cout << "-------------------------------------------------------------------" << endl;
	const int n = 60;
	int K[n], i, t, size, newK[n], index = 0;
	cout << "Введите размер массива (не более 60): ";
	cin >> size;

	for (i = 0; i < size; i++)
		*(K + i) = rand() % 99;

	cout << endl << "Введите t: ";
	cin >> t;

	for (i = 0; i < size; i++)
	{
		if (*(K + i) < t)
		{
			*(newK + index) = *(K + i);
			index++;
		}
		cout << " " << *(K + i);
	}

	for (i = 0; i < size; i++)
	{
		if (*(K + i) > t)
		{
			*(newK + index) = *(K + i);
			index++;
		}
		cout << " " << *(K + i);
	}
	cout << endl;
}

void v2c1()
{
	cout << "-------------------------------------------------------------------" << endl;
	const int n = 50;
	int A[n], B[n], S[n], k;
	cout << "Введите кол-во элементов (не более 50): "; cin >> k;

	cout << "Массив A:" << endl;
	for (int f = 0; f < k; f++)
		A[f] = rand() % 7;
	
	int* pA = A;
	for (int f = 0; f < k; f++)
		cout << *(pA + f) << endl;
	
	cout << "====================" << endl;
	cout << "Массив B:" << endl;
	for (int f = 0; f < k; f++)
		B[f] = rand() % 7;
	
	int* pB = B;
	for (int f = 0; f < k; f++)
	{
		cout << *(pB + f) << endl;
	}
	cout << "====================" << endl;
	cout << "Массив S: " << endl;
	int* pS = S;
	for (int f = 0; f < k; f++)
	{
		*(pS + f) = *(pA + f) + *(pB + f);
		cout << *(pS + f) << " = " << *(pA + f) << " + " << *(pB + f) << endl;
	}
}

void v3c1()
{
	cout << "-------------------------------------------------------------------" << endl;
	const int n = 60;
	int A[n], B[n], t, size, cA = 0, cB = 0;
	cout << "Введите размер массивов (не более 60): ";
	cin >> size;

	for (int i = 0; i < size; i++)
		*(A + i) = rand() % 99;

	for (int i = 0; i < size; i++)
		*(B + i) = rand() % 99;

	cout <<"Введите t : ";
	cin >> t;

	for (int i = 0; i < size; i++)
		if (*(A + i) < t) 
			cA++;

	for (int i = 0; i < size; i++)
		if (*(B + i) < t) 
			cB++;

	if (cA > cB) {
		cout << "Массив A[] (" << cA << " эл. меньше t = " << t << "):" << endl;
		for (int i = 0; i < size; i++)
			cout << "A[" << i << "] = " << *(A + i) << endl;
		cout << "Массив B[]: (" << cB << " эл. меньше t = " << t << "):" << endl;
		for (int i = 0; i < size; i++)
			cout << "B[" << i << "] = " << *(B + i) << endl;
	}

	else if (cA < cB) {
		cout << "Массив B[]: (" << cB << " эл. t = " << t << "):" << endl;
		for (int i = 0; i < size; i++)
			cout << "B[" << i << "] = " << *(B + i) << endl;
		cout << "Массив A[] (" << cA << " эл.меньше t = " << t << "):" << endl;
		for (int i = 0; i < size; i++)
			cout << "A[" << i << "] = " << *(A + i) << endl;
	}

	else if (cA == cB) cout << "Массивы имеют одинаковое количество элементов, меньших t.";

	else cout << "Ошибка." << endl;
}

void v5c2()
{
	cout << "-------------------------------------------------------------------" << endl;
	const int i = 30, j = 40;
	int n, a[i], b[j], g, schetchik = 0;
	cout << "Введите размер массива (до 30): ";
	cin >> n;
	cout << "Введите размер массива (до 40): ";
	cin >> g;
	cout << "====================" << endl;


	//Заполняем массив a
	for (int f = 0; f < n; f++)
		a[f] = rand() % 20;
		
	int* px = a;
	for (int f = 0; f < n; f++)
	{
		cout << "Указатель на первый массив: " << *(px + f) << endl;
	}
	cout << "====================" << endl;

	//Заполняем массив b
	for (int f = 0; f < g; f++)
		b[f] = rand() % 20;
	
	int* py = b;
	for (int f = 0; f < g; f++)
	{
		cout << "Указатель на второй массив: " << *(py + f) << endl;
	}
	cout << "====================" << endl;
	for (int z = 0; z < n; z++) //Массив a 
	{
		for (int v = 0; v < g; v++) //Массив b
		{
			if (*(px + z) == *(py + v))
			{
				schetchik = schetchik + 1;
				cout << z + 1 << "-й " << "элемент массива a равен " << v + 1 << "-ому " << "элементу массива b" << endl;
			}
		}
	}
	cout << endl << "Количество пар элементов = " << schetchik << endl;
}