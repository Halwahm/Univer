/*

//��������� ��� - �������, ���������� ����� � 
//���������� �� ��������� �� ��������� ������.
//������� ������� �� �����.����������� ����� 
//��������� ����� � ��� - �������.

#include <iostream>
#include <string>
using namespace std;

int getHashCode(char a) {
	return int(a);
}

int main() {
	setlocale(LC_CTYPE, "rus");
	string s;
	const int SIZE = 25;
	int key = 0;
	char symbol;
	int alphabet1[SIZE] = { 0 };
	int alphabet2[SIZE] = { 0 };
	cout << "������� ������, ��� �������� ���������� ��������� ������ �� ���� � ������: ";

	getline(cin, s);

	int index = 0;
	for (int i = 0; i < s.length(); ++i) {
		index = getHashCode(s[i]);
		if (index >= 65 && index <= 90) {
			alphabet1[index - 65]++;
		}
		else if (index >= 97 && index <= 122) {
			alphabet2[index - 97]++;
		}
		else continue;
	}

	for (;;) {
		cout << "��������, ��� ������ �������: " << endl;
		cout << "1 - ������� ���-������� ��������: " << endl;
		cout << "2 - ����� �� �������: " << endl;
		cin >> key;

		switch (key)
		{
		case 1:
			for (int i = 0; i < SIZE; ++i) {
				if (alphabet1[i] == 0)
					continue;
				else
					cout << "|" << char(i + 65) << " - " << alphabet1[i];


			}
			cout << "|" << endl;

			for (int i = 0; i < SIZE; ++i) {
				if (alphabet2[i] == 0)
					continue;
				else
					cout << "|" << char(i + 97) << " - " << alphabet2[i];


			}
			cout << "|" << endl;
			break;
		case 2:
			cout << "������� ������, ���������� ��������� �������� � ������ ������ ����������: " << endl;
			cin >> symbol;


			if (getHashCode(symbol) >= 65 && getHashCode(symbol) <= 90)
				cout << "���������� ��������� �������'" << symbol << "' � ������ ����� " << alphabet1[getHashCode(symbol) - 65] << endl;
			else if (getHashCode(symbol) >= 97 && getHashCode(symbol) <= 122)
				cout << "���������� ��������� �������'" << symbol << "' � ������ ����� " << alphabet2[getHashCode(symbol) - 97] << endl;
			break;
		}
	}
}
*/