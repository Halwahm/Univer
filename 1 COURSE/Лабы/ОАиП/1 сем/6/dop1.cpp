#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	setlocale(LC_CTYPE, "Russian");
	cout << "������� �������� ������������������ ����� Enter" << endl;
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
	cout << "���� �������� " << p << " ����";

	return 0;
}