#include <iostream>
#include <iomanip>

using namespace std;

int main() { 

	setlocale(LC_CTYPE, "Russian");
	char c, probel; probel = ' '; // пробел - зарезервированный символ
	cout << "Введите символ "; cin >> c;

	int a[8] = { 1, 3, 5, 6, 3, 3, 3, 3 };
	for (int i = 0; i <= 7; i++) {
		cout << setw(7-a[i]) << setfill(probel) << probel;
		cout << setw(a[i]*2) << setfill(c) << c << endl;
	}

	return 0;
}
