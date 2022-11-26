#include <iostream>

using namespace std;

int main() {
	setlocale(LC_CTYPE, "russian");

	float a, b, max, min, indmax = 0, indmin = 0;
	int i, n;
	cout << "Введите n: ";
	 cin >> n;

	cout << "Введите числа: " << endl;
	cin >> a;
	max = a;
	min = a;
	 for (i = 1; i < n; i++) {
		 cin >> a;
		 if ( max < a) {
			 max = a;
			 indmax = i;
		}
		 if (min > a) {
			 min = a;
			 indmin = i;
		 }
	 }
	 cout << "Между min и max: " << abs(indmax - indmin) - 1;
	return 0;
}