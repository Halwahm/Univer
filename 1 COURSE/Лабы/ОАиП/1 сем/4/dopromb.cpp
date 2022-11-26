#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "russian");
	double r, p, q;
	cout << "Введите радиус r = "; cin >> r;
	cout << endl << "Введите первую диагональ: "; cin >> p;
	cout << endl << "Введите вторую диагональ: "; cin >> q;
	if 
		(r < (p / 2 * q / 2) / ((sqrt(p / 2 * p / 2 + q / 2 * q / 2)));
	{
		cout << endl << "Можно";
	}
	else { cout << endl << "Нельзя"; }
	
	return 0;
}