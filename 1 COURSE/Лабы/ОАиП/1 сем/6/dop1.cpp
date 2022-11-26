#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	setlocale(LC_CTYPE, "Russian");
	cout << "Вводите числовую последовательность через Enter" << endl;
	int n, p = 0;
	do
	{
		cin >> n;
		cout << endl;
		if (n < 0)
		{
			p = p + 1;
		}
	} while (n != 0);
	cout << "Знак меняется " << p << " раза";

	return 0;
}