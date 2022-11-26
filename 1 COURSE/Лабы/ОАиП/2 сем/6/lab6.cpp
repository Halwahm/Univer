#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Создать список, содержащий элементы целого типа. 
Найти сумму положительных элементов, кратных 5, или выдать сообщение, что таких элементов нет. */

struct list
{
	int number;
	list* next;
};

void insert(list*&, int);
int del(list*&, int);
int IsEmpty(list*);
void printList(list*);
void menu(void);
void sum5(list*);
void toFile(list*& p);
void fromFile(list*& p);
void find(list*);

int main()
{
    setlocale(LC_ALL, "RU");
	list* first = NULL;
	short choice;
	short value;
	menu(); 
	cout << " Что дальше? ";
	cin >> choice;
	while (choice != 8)
	{
		switch (choice)
		{
		case 1: cout << "Введите число ";
			cin >> value;
			insert(first, value);	break;
		case 2:
			printList(first);	break;
		case 3: if (!IsEmpty(first))
		{
			cout << "Введите удаляемое число ";
			cin >> value;
			if (del(first, value))
			{
				cout << "Удалено число " << value << endl;
				printList(first);
			}
			else
				cout << "Число не найдено" << endl;
		}
			  else
			cout << "Список пуст" << endl;	break;
		case 4: sum5(first);	break;
		case 5: toFile(first);	break;
		case 6: fromFile(first);	break;
		case 7: find(first);   break;
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
	cout << " 2 - Вывод числа" << endl;
	cout << " 3 - Удаление числа" << endl;
	cout << " 4 - Вычисление суммы чисел, кратных 5" << endl;
	cout << " 5 - Запись в файл" << endl;
	cout << " 6 - Вывод из файла" << endl;
	cout << " 7 - Поиск элемента" << endl;
	cout << " 8 - Конец" << endl;
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

int del(list*& p, int value)
{
	list* previous, * current, * temp;
	if (value == p->number)
	{
		temp = p;
		p = p->next; //отсоединение узла
		delete temp; 
		return value;
	}
	else
	{
		previous = p;
		current = p->next;
		while (current != NULL && current->number != value)
		{
			previous = current;
			current = current->next; // перейти к следующему 
		}
		if (current != NULL)
		{
			temp = current;
			previous->next = current->next;
			free(temp);
			return value;
		}
	}
	return 0;
}

int IsEmpty(list* p)
{
	return p == NULL;
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

void toFile(list*& p)
{
	list* temp = p;
	ofstream file1("mList.txt");
	if (file1.fail())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	while (temp)
	{
		int nn = temp->number;
		file1 << nn << "\n";
		temp = temp->next;
	}
	file1.close();
	cout << "Список записан в файл mList.txt\n";
}

void fromFile(list*& p)
{

	char buf[10];

	ifstream file1("mList.txt");
	if (file1.fail())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	while (!file1.eof())
	{
		file1.getline(buf, 10);
		if (strlen(buf))
			insert(p, atoi(buf));
		cout << "-->" << buf;
	}
	cout << "-->NULL" << endl;
	file1.close();
}

void find(list* p)
{
	bool isFnd = false;
	cout << "Введите элемент:" << endl;
	int element;
	cin >> element;
	list* fnd = p;
	while (fnd)
	{
		if (fnd->number == element)
		{
			isFnd = true;
			printf("Элемент найден\n");
			break;
		}
		fnd = fnd->next;
	}
	if (!isFnd)
		printf("Элемент не найден\n");
}