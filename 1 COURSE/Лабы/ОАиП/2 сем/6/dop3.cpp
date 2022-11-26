//#include <iostream>
//#include <string>
//#include<fstream>
//using namespace std;
//
///*������� ������, ���������� �������� ������ ����. 
//����� ����� ������������� ���������, ������� 5, ��� ������ ���������, ��� ����� ��������� ���. */
//
//struct list
//{
//	int number;
//	list* next;
//};
//
//void insert(list*&, int);
//int del(list*&, int);
//int IsEmpty(list*);
//void printList(list*);
//void menu(void);
//void sum5(list*);
//void toFile(list*& p);
//void fromFile(list*& p);
//void find(list*);
//
//int main()
//{
//	setlocale(LC_CTYPE, "Russian");
//	list* first = NULL;
//	int choice;
//	int value;
//	menu();
//	cout << " ��� ������? ";
//	cin >> choice;
//	while (choice != 8)
//	{
//		switch (choice)
//		{
//		case 1: cout << "������� ����� ";
//			cin >> value;
//			insert(first, value);
//			break;
//		case 2:
//			printList(first);
//			break;
//		case 3: if (!IsEmpty(first))
//		{
//			cout << "������� ��������� ����� ";
//			cin >> value;
//			if (del(first, value))
//			{
//				cout << "������� ����� " << value << endl;
//				printList(first);
//			}
//			else
//				cout << "����� �� �������" << endl;
//		}
//			  else
//			cout << "������ ����" << endl;
//			break;
//		case 4: sum5(first);
//			break;
//		case 5: toFile(first);
//			break;
//		case 6: fromFile(first);
//			break;
//		case 7: find(first);
//			break;
//		default: cout << "������������ �����" << endl;
//			menu();
//			break;
//		}
//		cout << "��� ������? ";
//		cin >> choice;
//	}
//	cout << "�����" << endl;
//	return 0;
//}
//
//void menu(void)
//{
//	cout << "�������� �����:" << endl;
//	cout << " 1 - ���� �����" << endl;
//	cout << " 2 - ����� �����" << endl;
//	cout << " 3 - �������� �����" << endl;
//	cout << " 4 - ���������� ����� ������������� �����, ������� 5" << endl;
//	cout << " 5 - ������ � ����" << endl;
//	cout << " 6 - ����� �� �����" << endl;
//	cout << " 7 - ����� ��������" << endl;
//	cout << " 8 - �����" << endl;
//}
//
//void insert(list*& p, int value)
//{
//	list* newP = new list;
//	if (newP != NULL)
//	{
//		newP->number = value;
//		newP->next = p;
//		p = newP;
//	}
//	else
//		cout << "�������� ���������� �� ���������" << endl;
//}
//
//int del(list*& p, int value)
//{
//	list* previous, * current, * temp;
//	if (value == p->number)
//	{
//		temp = p;
//		p = p->next;
//		delete temp;
//		return value;
//	}
//	else
//	{
//		previous = p;
//		current = p->next;
//		while (current != NULL && current->number != value)
//		{
//			previous = current;
//			current = current->next;
//		}
//		if (current != NULL)
//		{
//			temp = current;
//			previous->next = current->next;
//			free(temp);
//			return value;
//		}
//	}
//	return 0;
//}
//
//int IsEmpty(list* p)
//{
//	return p == NULL;
//}
//
//
//
//void printList(list* p)
//{
//	if (p == NULL)
//		cout << "������ ����" << endl;
//	else
//	{
//		cout << "������:" << endl;
//		while (p != NULL)
//		{
//			cout << "-->" << p->number;
//			p = p->next;
//		}
//		cout << "-->NULL" << endl;
//	}
//}
//
//void sum5(list* p)
//{
//	int sm = 0;
//	if (p == NULL)
//		cout << "������ ����" << endl;
//	else
//	{
//		while (p != NULL)
//		{
//			if (p->number < 0 && p->number % 5 == 0)
//
//				sm = sm + (p->number);
//			p = p->next;
//
//
//		}
//		cout << "����� = " << sm << endl;
//	}
//
//}
//void toFile(list*& p)
//{
//	list* temp = p;
//	ofstream file1("mList.txt");
//	if (file1.fail())
//	{
//		cout << "\n ������ �������� �����";
//		exit(1);
//	}
//	while (temp)
//	{
//		int nn = temp->number;
//		file1 << nn << "\n";
//		temp = temp->next;
//	}
//	file1.close();
//	cout << "������ ������� � ���� mList.txt\n";
//}
//void fromFile(list*& p)
//{
//
//	char buf[10];
//
//	ifstream file1("mList.txt");
//	if (file1.fail())
//	{
//		cout << "\n ������ �������� �����";
//		exit(1);
//	}
//	while (!file1.eof())
//	{
//		file1.getline(buf, 10);
//		if (strlen(buf))
//			insert(p, atoi(buf));
//		cout << "-->" << buf;
//	}
//	cout << "-->NULL" << endl;
//	file1.close();
//}
//void find(list* p)
//{
//	bool isFnd = false;
//	int element;
//	cout << "������� �������" << endl;
//	cin >> element;
//	list* fnd = p;
//	while (fnd)
//	{
//		if (fnd->number == element)
//		{
//			isFnd = true;
//			printf("������� ������\n");
//			break;
//		}
//		fnd = fnd->next;
//	}
//	if (!isFnd)
//		printf("������� �� ������\n");
//}