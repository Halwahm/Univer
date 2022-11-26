

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Создать список, содержащий элементы целого типа.
//Найти сумму положительных элементов, кратных 5, или выдать сообщение, что таких элементов нет. 

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
	cout << " Что дальше? ";
	cin >> choice;
	while (choice != 4)
	{
		switch (choice)
		{
		case 1: cout << "Введите число ";
			cin >> value;
			insert(first, value);	break;
		case 2:
			printList(first);	break;
		case 3: sum5(first);	break;
		default: cout << "Неправильный выбор" << endl;
			menu(); break;
		}
		cout << "Что дальше? ";
		cin >> choice;
	}
	cout << "Конец" << endl;
	return 0;
}

void menu(void)
{
	cout << "Сделайте выбор:" << endl;
	cout << " 1 - Ввод числа" << endl;
	cout << " 2 - Вывод списка" << endl;
	cout << " 3 - Вычисление суммы чисел, кратных 5" << endl;
	cout << " 4 - Конец" << endl;
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
		cout << "Операция добавления не выполнена" << endl;
}

void printList(list* p)
{
	if (p == NULL)
		cout << "Список пуст" << endl;
	else
	{
		cout << "Список:" << endl;
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
		cout << "Список пуст" << endl;
	else
	{
		while (p != NULL)
		{
			if (p->number % 5 == 0)

				sm = sm + (p->number);
			p = p->next;


		}
		cout << "Сумма = " << sm << endl;
	}

}

