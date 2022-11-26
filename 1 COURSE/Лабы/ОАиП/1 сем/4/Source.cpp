#include <iostream>

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Russian");
	float a, b, c, d;

	printf("¬ведите a "); cin >> a;
	printf("¬ведите b "); cin >> b;
	printf("¬ведите c "); cin >> c;

	if (a > b && a > c) {
		d = a;
		cout << "d = " << d;
	}
	if (b > a && b > c) {
		d = b;
		cout << "d = " << d;
	}
	if (c > a && c > b) {
		d = c;
		cout << "d = " << d;
	}
	return 0;
}