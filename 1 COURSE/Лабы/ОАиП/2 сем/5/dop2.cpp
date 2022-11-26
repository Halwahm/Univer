/*#include <iostream>
#include<fstream>

#define str_len 256
#define size 100

using namespace std;

//�������� ������.�.�.�, ���� ��������, �����, �������.
//����� �� �������.���� �������� ����������� � ������� �������� ����.

void enter_new();
void out();
void del();
void search();

struct notebook
{
	char name[str_len];
	char surname[str_len];
	char middleName[str_len];
	unsigned day : 4;
	unsigned month : 4;
	unsigned year : 4;
	char addres[str_len];
	int phone;
	char place_of_work[str_len];
	char position[str_len];
};
struct notebook people_in_notebook[size];
int current_size = 0; int choice;
notebook all;
notebook b;
int l, z, x;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "�������:" << endl;
	cout << "1-��� ����� ������" << endl;
	cout << "2-��� ������ ������" << endl;
	cout << "3-��� ��������" << endl;
	cout << "4-��� ������ ����������" << endl;
	cout << "5-��� ������" << endl;
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1: enter_new(); break;
		case 2: out(); break;
		case 3: del(); break;
		case 4: search(); break;


		}
	} while (choice != 5);
}
void enter_new()
{
	cout << "���� ����������" << endl;
	if (current_size < size)
	{
		cout << "������ ����� ";
		cout << current_size + 1;
		cout << endl << "�������" << endl;
		cin >> people_in_notebook[current_size].surname;
		cout << "���" << endl;
		cin >> people_in_notebook[current_size].name;
		cout << "��������" << endl;
		cin >> people_in_notebook[current_size].middleName;
		cout << "���� ��������: " << endl;
		cout << "����:";
		cin >> l; b.day = l;
		cout << endl;
		cout << "�����:";
		cin >> z; b.month = z;
		cout << endl;
		cout << "���:";
		cin >> x; b.year = x;
		cout << endl;
		cout << "�����:" << endl;
		cin >> people_in_notebook[current_size].addres;
		cout << "����� ��������:" << endl;
		cin >> people_in_notebook[current_size].phone;
		cout << "����� ������:" << endl;
		cin >> people_in_notebook[current_size].place_of_work;
		cout << "���������:" << endl;
		cin >> people_in_notebook[current_size].position;
		current_size++;

	}
	else
		cout << "������� ������������ ���-�� �����";
	cout << "��� ������?" << endl;
	cin >> choice;
}
void out()
{
	int sw, n;
	cout << "1-����� 1 ������" << endl;
	cout << "2-����� ���� �����" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "����� ��������� ������: " << endl; cin >> n; cout << endl;
		cout << "�������" << endl;
		cout << people_in_notebook[n - 1].surname;
		cout << endl;
		cout << "���" << endl;
		cout << people_in_notebook[n - 1].name;
		cout << endl;
		cout << "��������" << endl;
		cout << people_in_notebook[n - 1].middleName;
		cout << endl;
		cout << "���� ��������: " << endl;
		cout << "����:";
		cout << l;
		cout << endl;
		cout << "�����:";
		cout << z;
		cout << endl;
		cout << "���:";
		cout << x;
		cout << endl;
		cout << "�����:" << endl;
		cout << people_in_notebook[n - 1].addres;
		cout << endl;
		cout << "����� ��������:" << endl;
		cout << people_in_notebook[n - 1].phone;
		cout << endl;
		cout << "����� ������:" << endl;
		cout << people_in_notebook[n - 1].place_of_work;
		cout << endl;
		cout << "���������:" << endl;
		cout << people_in_notebook[n - 1].position;
		cout << endl;


	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "�������" << endl;
			cout << people_in_notebook[i].surname;
			cout << endl;
			cout << "���" << endl;
			cout << people_in_notebook[i].name;
			cout << endl;
			cout << "��������" << endl;
			cout << people_in_notebook[i].middleName;
			cout << endl;
			cout << "���� ��������: " << endl;
			cout << "����:";
			cout << l;
			cout << endl;
			cout << "�����:";
			cout << z;
			cout << endl;
			cout << "���:";
			cout << x;
			cout << endl;
			cout << "�����:" << endl;
			cout << people_in_notebook[i].addres;
			cout << endl;
			cout << "����� ��������:" << endl;
			cout << people_in_notebook[i].phone;
			cout << endl;
			cout << "����� ������:" << endl;
			cout << people_in_notebook[i].place_of_work;
			cout << endl;
			cout << "���������:" << endl;
			cout << people_in_notebook[i].position;
			cout << endl;

		}
	}
	cout << "��� ������?" << endl;
	cin >> choice;
}
void del()
{
	int d;
	cout << "\n����� ������, ������� ���� ������� (��� �������� ���� ����� ������ 99)" << endl;
	cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			people_in_notebook[de1] = people_in_notebook[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			people_in_notebook[i] = all;
	cout << "��� ������?" << endl;
	cin >> choice;
}
void search()
{
	char surname[16];
	cout << "�������:" << "\n";
	cin >> surname;
	for (int q = 0; q < current_size; q++)
	{
		if (strcmp(surname, people_in_notebook[q].surname) == 0)
		{
			cout << "�������" << endl;
			cout << people_in_notebook[q].surname;
			cout << endl;
			cout << "���" << endl;
			cout << people_in_notebook[q].name;
			cout << endl;
			cout << "��������" << endl;
			cout << people_in_notebook[q].middleName;
			cout << endl;
			cout << "���� ��������: " << endl;
			cout << "����:";
			cout << l;
			cout << endl;
			cout << "�����:";
			cout << z;
			cout << endl;
			cout << "���:";
			cout << x;
			cout << endl;
			cout << "�����:" << endl;
			cout << people_in_notebook[q].addres;
			cout << endl;
			cout << "����� ��������:" << endl;
			cout << people_in_notebook[q].phone;
			cout << endl;
			cout << "����� ������:" << endl;
			cout << people_in_notebook[q].place_of_work;
			cout << endl;
			cout << "���������:" << endl;
			cout << people_in_notebook[q].position;
			cout << endl;
		}
	}
	cout << "��� ������?" << endl;
	cin >> choice;
}*/