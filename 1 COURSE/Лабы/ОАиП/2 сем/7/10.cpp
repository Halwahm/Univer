/*����������� �������, ������� ����������, ���� �� � ����� ���� �� ���� �������, ������� � �������� ���������.*/
/*
#include <iostream>

using namespace std;

struct Stek
{
	int number;
	Stek* next;
} stek, stek_new;


int pop(Stek*& st) // ���������� ��������
{
	int tmp = st->number;
	Stek* pv = st;
	st = st->next;       // �������� ���������� �������������� �������
	delete pv;           // ������������� ������ 
	return tmp;
}

void push(Stek*& st, int d) // ���������� ��������
{
	Stek* pv = new Stek;
	pv->number = d;   // �������� ���������� � ����     
	pv->next = st;
	st = pv;
}


void main()
{
	setlocale(LC_CTYPE, "RU");
	int lower, higher;
	cout << "������� ������ �������: "; cin >> lower;
	cout << "������� ������� �������: "; cin >> higher;
	if (lower > higher)
	{
		cout << "�������� �������";
		exit(12);
	}
	int size = 5;
	int a;
	Stek* ptr_stek = &stek;
	for (int i = 0; i < size; i++)
	{
		cout << "������� �����: ";
		cin >> a;
		push(ptr_stek, a);
	}
	for (int i = 0; i < size; i++)
	{
		if (lower <= pop(ptr_stek) <= higher)
		{
			cout << "����� ������� ����������\n";
			exit(13);
		}
		else
		{
			cout << "������ �������� �� ����������\n";
		}
	}
}*/