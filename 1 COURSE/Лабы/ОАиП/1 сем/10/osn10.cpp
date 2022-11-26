#include <iostream>
using namespace std;
void td();
int main() {
	setlocale(LC_CTYPE, "Russian");

	int arr[10] = { 0 };
	int n = 0, indmin = 0, indmax = 0;
	cout << "Введите массив из 10 элементов: " << endl;
	while (n < 10)
	{
		cin >> arr[n];
		n++;
	}
	for (int i = 0; i < 10; i++)
	{
		if (arr[i] == 0)
		{
			indmin = i;
			break;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (arr[i] == 0)
		{
			indmax = i;
		}
	}
	cout << "Первый нулевой элемент массива на " << indmin + 1 << " позиции." << endl;
	cout << "Последний нулевой элемент массива на " << indmax + 1 << " позиции." << endl;
	
	td();
	return 0;
}

void td() {
	cout << "----------------------------------------------------------------" << endl;
	int k, max = 0, tok = 0, arrnum[100] = {0};
	cout << "Введите количество элементов массива: ";
	cin >> k;
	int* arr = new int[k];
	cout << "Введите массив: " << endl;
	while (tok<k)
	{
		cin >> arr[tok];
		tok++;
	}
	/*for (int o = 0; o < k; o++)
	{
		cin >> arr[tok];
		tok++;
	}*/
	tok = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int l = 0; l < k; l++) 
		{
			if (i == arr[l])
				tok++; 
		}
		arrnum[i] = tok;
		tok = 0;
		cout << i << ":" << arrnum[i] << endl;
	}
	tok = 0;
	for (int i = 0; i < 100; i++)
	{
		if (arrnum[i] > max) {
			max = arrnum[i];
			tok = i;
		}
	}
	cout << "Повторяющиеся элемент: " << tok;
}