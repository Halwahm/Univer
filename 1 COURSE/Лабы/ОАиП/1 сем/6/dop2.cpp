#include <iostream>

using namespace std;

int main() {

	setlocale(LC_CTYPE, "Russian");
	cout << "������� ���-�� ���" << endl;
	float n;
	cin >> n;
	cout << "������� ������ � %" << endl;
	float p;
	cin >> p;
	float s, sum = 0;
	for (int i = 0; i < n; i++) {
		cout << "������� ��������� �� " << i + 1 << " ���" << endl;
		cin >> s;
		sum = sum * (1 - (p / 100)) + s;
	}
	cout << sum;

	return 0;
}