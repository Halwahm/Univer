#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	double s = 5.2, x, j = 10.4 * pow(10,4), v;

	cout << "Введите x ";
	 cin >> x;

	 if (2 * s > x * j) {
		 v = pow(cos(j * s), 2);
		 cout << "v = " << v;
	 }
	 else if (2 * s < x * j) {
		 v = 2 * tan(j * x);
		 cout << "v = " << v;
	 }
	 if (2 * s == x * j) {
		 v = 5 - exp(x / 2);
		 cout << "v = " << v;
	 }
	return 0;
}