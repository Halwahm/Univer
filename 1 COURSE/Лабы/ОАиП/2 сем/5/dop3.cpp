/*#include <iostream>
#include<fstream>

#define str_len 256
#define size 100

using namespace std;

//�������������.������� �������������, �������� ��������, ���� ��������.
//����� �� ���� ��������.���� �������� ����������� � ������� �������� ����.

void enter_new();
void out();
void del();
void search();

struct teachers
{
	char surname_of_teacher[str_len];
	char exam[str_len];
	unsigned day : 4;
	unsigned month : 4;
	unsigned year : 4;

};
teachers allTeachers[size];
teachers all;
teachers b;
int choice; int current_size = 0;
int l, z, q;
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
		cout << endl << "������� �������������" << endl;
		cin >> allTeachers[current_size].surname_of_teacher;
		cout << "�������" << endl;
		cin >> allTeachers[current_size].exam;
		cout << "����" << endl;
		cout << "����";
		cin >> l; b.day = l;
		cout << endl;
		cout << "�����";
		cin >> z; b.month = l;
		cout << endl;
		cout << "���";
		cin >> q; b.year = l;
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
		cout << "������� �������������:";
		cout << allTeachers[n - 1].surname_of_teacher;
		cout << endl;
		cout << "�������:";
		cout << allTeachers[n - 1].exam;
		cout << endl;
		cout << "����" << endl;
		cout << "����:";
		cout << l;
		cout << endl;
		cout << "�����:";
		cout << z;
		cout << endl;
		cout << "���:";
		cout << q;
		cout << endl;


	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{

			cout << "������� �������������:";
			cout << allTeachers[i].surname_of_teacher;
			cout << endl;
			cout << "�������:";
			cout << allTeachers[i].exam;
			cout << endl;
			cout << "����" << endl;
			cout << "����:";
			cout << l;
			cout << endl;
			cout << "�����:";
			cout << z;
			cout << endl;
			cout << "���:";
			cout << q;
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
			allTeachers[de1] = allTeachers[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			allTeachers[i] = all;
	cout << "��� ������?" << endl;
	cin >> choice;
}
void search()
{
	int day, month, year;
	cout << "������� ����" << endl;
	cout << "����:";
	cin >> day;
	cout << endl;
	cout << "�����:";
	cin >> month;
	cout << endl;
	cout << "���:";
	cin >> year;
	cout << endl;
	for (int f = 0; f < current_size; f++)
	{
		if (day == l && month == z && year == q)
		{
			cout << "������� �������������:";
			cout << allTeachers[f].surname_of_teacher;
			cout << endl;
			cout << "�������";
			cout << allTeachers[f].exam;
			cout << endl;
			cout << "����" << endl;
			cout << "����:";
			cout << l;
			cout << endl;
			cout << "�����:";
			cout << z;
			cout << endl;
			cout << "���:";
			cout << q;
			cout << endl;
		}
	}
	cout << "��� ������?" << endl;
	cin >> choice;
}*/