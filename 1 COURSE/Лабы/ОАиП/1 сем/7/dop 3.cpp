#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "russian");
	double c1, c2;
	cout << "Введите кол-во литров в сосудах с1 и с2 соответственно ";
		cin >> c1 >> c2;
		for (int i = 0; i < 12; i++) {
			c1 = c1 / 2;
			c2 = c1 + c2;
			c2 = c2 / 2;
			c1 = c1 + c2;
			cout << c1 << " " << c2 << endl;
		}
	return 0;
}