/*#include <iostream>
#include<fstream>

#define str_len 256
#define size 100

using namespace std;

void enter_new();
void out();
void del();
void search();

//�����.������������ ������, ����, ����������, ������� �������� ��������(5, 7, 11, 20, 25, 30).
//����� �� ����.������� �������� �������� ����������� � ������� ������������.

struct Sklad
{
	char name_of_product[str_len];
	float cell;
	int many;
	int per;
};

enum Percent
{
	five = 5, seven = 7, eleven = 11, twenty = 20, twentyFive = 25, thirty = 30
};
Sklad productOnSclad[size];
Sklad all;
int choice; int current_size = 0;
int sell;
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
		cout << endl << "������������ ������" << endl;
		cin >> productOnSclad[current_size].name_of_product;
		cout << "����" << endl;
		cin >> productOnSclad[current_size].cell;
		cout << "����������" << endl;
		cin >> productOnSclad[current_size].many;
		cout << "���������� ��������" << endl;
		cin >> productOnSclad[current_size].per;
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
		cout << "������ ����� "; cin >> n;
		cout << endl << "������������ ������:" << endl;
		cout << productOnSclad[n - 1].name_of_product << endl;
		cout << "����:" << endl;
		cout << productOnSclad[n - 1].cell << endl;
		cout << "����������:" << endl;
		cout << productOnSclad[n - 1].many << endl;
		if (productOnSclad[n - 1].per == 5)
		{
			cout << "���������� ��������=" << five << "%" << endl;
		}
		else if (productOnSclad[n - 1].per == 7)
		{
			cout << "���������� ��������=" << seven << "%" << endl;
		}
		else if (productOnSclad[n - 1].per == 11)
		{
			cout << "���������� ��������=" << eleven << "%" << endl;
		}
		else if (productOnSclad[n - 1].per == 20)
		{
			cout << "���������� ��������=" << twenty << "%" << endl;
		}
		else if (productOnSclad[n - 1].per == 25)
		{
			cout << "���������� ��������=" << twentyFive << "%" << endl;
		}
		else if (productOnSclad[n - 1].per == 30)
		{
			cout << "���������� ��������=" << thirty << "%" << endl;
		}

	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << endl << "������������ ������:" << endl;
			cout << productOnSclad[i].name_of_product << endl;
			cout << "����:" << endl;
			cout << productOnSclad[i].cell << endl;
			cout << "����������:" << endl;
			cout << productOnSclad[i].many << endl;
			if (productOnSclad[i].per == 5)
			{
				cout << "���������� ��������=" << five << "%" << endl;
			}
			else if (productOnSclad[i].per == 7)
			{
				cout << "���������� ��������=" << seven << "%" << endl;
			}
			else if (productOnSclad[i].per == 11)
			{
				cout << "���������� ��������=" << eleven << "%" << endl;
			}
			else if (productOnSclad[i].per == 20)
			{
				cout << "���������� ��������=" << twenty << "%" << endl;
			}
			else if (productOnSclad[i].per == 25)
			{
				cout << "���������� ��������=" << twentyFive << "%" << endl;
			}
			else if (productOnSclad[i].per == 30)
			{
				cout << "���������� ��������=" << thirty << "%" << endl;
			}

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
			productOnSclad[de1] = productOnSclad[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			productOnSclad[i] = all;
	cout << "��� ������?" << endl;
	cin >> choice;
}
void search()
{
	cout << "���� ������:" << "\n";
	cin >> sell;
	for (int z = 0; z < current_size; z++)
	{
		if (sell == productOnSclad[z].cell)
		{
			cout << endl << "������������ ������:" << endl;
			cout << productOnSclad[z].name_of_product << endl;
			cout << "����:" << endl;
			cout << productOnSclad[z].cell << endl;
			cout << "����������:" << endl;
			cout << productOnSclad[z].many << endl;
			if (productOnSclad[z].per == 5)
			{
				cout << "���������� ��������=" << five << "%" << endl;
			}
			else if (productOnSclad[z].per == 7)
			{
				cout << "���������� ��������=" << seven << "%" << endl;
			}
			else if (productOnSclad[z].per == 11)
			{
				cout << "���������� ��������=" << eleven << "%" << endl;
			}
			else if (productOnSclad[z].per == 20)
			{
				cout << "���������� ��������=" << twenty << "%" << endl;
			}
			else if (productOnSclad[z].per == 25)
			{
				cout << "���������� ��������=" << twentyFive << "%" << endl;
			}
			else if (productOnSclad[z].per == 30)
			{
				cout << "���������� ��������=" << thirty << "%" << endl;
			}

		}

	}
	cout << "��� ������?" << endl;
	cin >> choice;
}*/