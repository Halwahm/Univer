#include <iostream>
using namespace std;

int main() {

	setlocale(LC_CTYPE, "Russian");
	
	cout << "Метод трапеции: ";
	double a1 = 8, n, s, x, h, s1, s2, i, a = 0, z, e, b, x1, b1 = 15;
	n = 200;
	s = 0;
	x = a;
	for (int i = 1; i > 0; i++) {
		h = (b1 - a1) / n;
		s = s + h * ((5 - pow(x, 2)) + (5 - pow(x + h, 2))) / 2;
		x = x + h;
		if (x > (b1 - h)) break;
	}
	cout << s << endl;

	cout << "Метод параболы: ";
	h = (b1 - a1) / (2 * n);
	x = a1 + 2 * h;
	s1 = 0;
	s2 = 0;
	i = 1;
	for (int o = 1; o > 0; o++) {
		s2 = s2 + (5 - pow(x, 2));
		x = x + h;
		s1 = s1 + (5 - pow(x, 2));
		x = x + h;
		i = i + 1;
		if (i < n) break;
	}
	z = (h / 3) * ((5 - pow(a1, 2)) + 4 * (5 - pow(a1 + h, 2)) + 4 * s1 + 2 * s2 + (5 - pow(b1, 2)));
	cout << z << endl;

	cout << "Метод дихотомии: " << endl;
	cout << "Введите a и b" << endl;
	cin >> a >> b;
	e = 0.0001;
	do {
		x = (a + b) / 2;
		if ((2 - pow(x, 2) + x) * (2 - pow(a, 2) + a) < 0)
			b = x;
		else a = x;
	} while (abs(a - b) > 2 * 2.7182);
	cout << x;
}