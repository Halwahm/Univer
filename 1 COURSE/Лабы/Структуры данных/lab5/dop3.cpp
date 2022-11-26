

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//������� ������, ���������� �������� ������ ����.
//����� ����� ������������� ���������, ������� 5, ��� ������ ���������, ��� ����� ��������� ���. 

struct list
{
	int number;
	list* next;
};

void insert(list*&, int);
void printList(list*);
void menu(void);
void sum5(list*);

int main()
{
	setlocale(LC_ALL, "RU");
	list* first = NULL;
	short choice;
	short value;
	menu();
	cout << " ��� ������? ";
	cin >> choice;
	while (choice != 4)
	{
		switch (choice)
		{
		case 1: cout << "������� ����� ";
			cin >> value;
			insert(first, value);	break;
		case 2:
			printList(first);	break;
		case 3: sum5(first);	break;
		default: cout << "������������ �����" << endl;
			menu(); break;
		}
		cout << "��� ������? ";
		cin >> choice;
	}
	cout << "�����" << endl;
	return 0;
}

void menu(void)
{
	cout << "�������� �����:" << endl;
	cout << " 1 - ���� �����" << endl;
	cout << " 2 - ����� ������" << endl;
	cout << " 3 - ���������� ����� �����, ������� 5" << endl;
	cout << " 4 - �����" << endl;
}

void insert(list*& p, int value)
{
	list* newP = new list;
	if (newP != NULL)
	{
		newP->number = value;
		newP->next = p;
		p = newP;
	}
	else
		cout << "�������� ���������� �� ���������" << endl;
}

void printList(list* p)
{
	if (p == NULL)
		cout << "������ ����" << endl;
	else
	{
		cout << "������:" << endl;
		while (p != NULL)
		{
			cout << "-->" << p->number;
			p = p->next;
		}
		cout << "-->NULL" << endl;
	}
}

void sum5(list* p)
{
	int sm = 0;
	if (p == NULL)
		cout << "������ ����" << endl;
	else
	{
		while (p != NULL)
		{
			if (p->number % 5 == 0)

				sm = sm + (p->number);
			p = p->next;


		}
		cout << "����� = " << sm << endl;
	}

}

