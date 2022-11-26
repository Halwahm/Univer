#include <iostream>

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Russian");
	float i, y, t, b = 2, j = 6, a = 1.5 * pow(10, 8);
	for (int n = 1; n <= 4; n++) {
		cout << "Введите i = "; cin >> i;
		y = a / (b + exp(b)) / (1 + (j * i));
		t = cos(y + 1) / sqrt(abs(-2 * j));
		cout << "y = " << y << endl;
		cout << "t = " << t << endl;
	}

	return 0;
}