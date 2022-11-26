#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Russian");
	float a = 1.5 * pow(10,8), b = 2, y, t, j = 6, i = 3;

	do {
		cout << "Для i = " << i <<  endl;
		y = a / (b + exp(b)) / (1 + (j * i));
		t = cos(y + 1) / sqrt(abs(-2 * j));
		cout << "y = " << y << endl;
		cout << "t = " << t << endl;
		i = i - 0.1;

	} while (i > 2);


	return 0;
}