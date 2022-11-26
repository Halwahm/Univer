#include <iostream>

using namespace std;

int main() {
	setlocale(LC_CTYPE, "russian");

	int a, b, c;
	for (int i = 100; i < 1000; i++) {
		a = i / 100;
		b = (i % 100)/10;
		c = i % 10;
			if (a != b && b != c && a != c)
		cout << i << endl;
	}
	return 0;
}