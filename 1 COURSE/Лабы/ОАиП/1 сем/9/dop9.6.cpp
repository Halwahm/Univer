#include <iostream>
using namespace std;

int main() {

	setlocale(LC_CTYPE, "Russian");
	cout << "Метод трапеции: ";
	double a2 = 1, n, s, x, a = 0, h, s1, s2, i, z, b, e, x1, b2 = 5;
	n = 200;
	s = 0;
	x = a;
	for (int i = 1; i > 0; i++) {
		h = (b2 - a2) / n;
		s = s + h * ((1 + pow(x, 3)) + ((1 + pow(x + h, 3)))) / 2;
		x = x + h;
		if (x > (b2 - h)) break;
	}
	cout << s << endl;

	cout << "Метод параболы: ";
	h = (b2 - a2) / (2 * n);
	x = a2 + 2 * h;
	s1 = 0;
	s2 = 0;
	i = 1;
	for (int o = 1; o > 0; o++) {
		s2 = s2 + ((1 + pow(x, 3)));
		x = x + h;
		s1 = s1 + ((1 + pow(x, 3)));
		x = x + h;
		i = i + 1;
		if (i < n) break;
	}
	z = (h / 3) * (((1 + pow(a2, 3)) + 4 * ((1 + pow(a2 + h, 3)) + 4 * s1 + 2 * s2 + ((1 + pow(b2, 3))))));
	cout << z << endl;

	cout << "Метод дихотомии: " << endl;
	cout << "Введите a и b" << endl;
	cin >> a >> b;
	e = 0.0001;
	do {
		x = (a + b) / 2;
		if (((5 * x - 1 + pow(x, 3)) * ((5 * a - 1 + pow(a, 3)) < 0)))
			b = x;
		else a = x;
	} while (abs(a - b) > 2 * 2.7182);
	cout << x;
}
