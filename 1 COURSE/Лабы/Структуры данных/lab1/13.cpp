#include <iostream>
using namespace std;
struct DoubleList //�������� ���� ������
{
	int data; //�������������� ����
	DoubleList* next; //��������� �� ��������� �������
	DoubleList* prev; //��������� �� ���������� �������
};
DoubleList* head; 
void AddList(int value, int position)
{
	DoubleList* node = new DoubleList; //�������� ������ ��������
	node->data = value; //���������� �������� ��������
	if (head == NULL) //���� ������ ����
	{
		node->next = node; //��������� ��������� next
		node->prev = node; //��������� ��������� prev
		head = node; //������������ ������ ������
	}
	else
	{
		DoubleList* p = head;
		for (int i = position; i > 1; i--) p = p->next;
		p->prev->next = node;
		node->prev = p->prev;
		node->next = p;
		p->prev = node;
	}
	cout << "\n������� ��������...\n\n";
}

int DeleteList(int position)
{
	if (head == NULL) { cout << "\n������ ����\n\n"; return 0; }
	if (head == head->next)
	{
		delete head;
		head = NULL;
	}
	else
	{
		DoubleList* a = head;
		for (int i = position; i > 1; i--) a = a->next;
		if (a == head) head = a->next;
		a->prev->next = a->next;
		a->next->prev = a->prev;
		delete a;
	}
	cout << "\n������� ������...\n\n";
}

void PrintList()
{
	if (head == NULL) cout << "\n������ ����\n\n";
	else
	{
		DoubleList* a = head;
		cout << "\n�������� ������: ";
		do
		{
			cout << a->data << " ";
			a = a->next;
		} while (a != head); cout << "\n\n";
	}
}

void main()
{
	setlocale(LC_ALL, "Rus");
	int value, position, x;
	do
	{
		cout << "1. �������� �������" << endl;
		cout << "2. ������� �������" << endl;
		cout << "3. ������� ������" << endl;
		cout << "0. �����" << endl;
		cout << "\n����� �������� > "; cin >> x;
		switch (x)
		{
		case 1:
			cout << "�������� > "; cin >> value;
			cout << "������� > "; cin >> position;
			AddList(value, position); break;
		case 2:
			cout << "������� > "; cin >> position;
			DeleteList(position); break;
		case 3: PrintList(); break;
		}
	} while (x != 0);
}