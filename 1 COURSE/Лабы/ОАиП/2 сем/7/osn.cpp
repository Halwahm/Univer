/*	Разработать функцию, которая удаляет первый
повторяющийся элемент стека.*/
/*
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct STACK {
	int data;
	STACK* head;
	STACK* next;
};

void AddEl(int elem, STACK* stack);
int TakeFromStack(STACK* stack);
void PrintStack(STACK* stack);
void ToFile(STACK* stack);
void FromFile(STACK* stack);
int DeleteSame(STACK* stack);
void clear(STACK* stack);

void DeleteSameHelp(STACK* stack, int point);

int main()
{
	setlocale(LC_ALL, "rus");
	int choice, newEl, position;

	STACK* stack = new STACK;
	stack->head = NULL;


	while (true)
	{
		cout << "1 - добавить элемент в стек\n";
		cout << "2 - извлечь элемент из стека\n";
		cout << "3 - вывод стека на экран\n";
		cout << "4 - удалить из стека первый повторяющийся элемент\n";
		cout << "5 - запись в файл\n";
		cout << "6 - вывод из файла\n";
		cout << "7 - очистка стека\n";
		cout << "0 - выход\n";
		cin >> choice;

		switch (choice)
		{
		case 1: {
			cout << "\n";
			cout << "Значение > "; cin >> newEl;
			AddEl(newEl, stack);
			cout << "\n";
			break;
		}

		case 2: {
			cout << TakeFromStack(stack) << endl;
			break;
		}

		case 3: {
			PrintStack(stack);
			break;
		}

		case 4: {
			DeleteSameHelp(stack, DeleteSame(stack));
			break;
		}

		case 5: {
			ToFile(stack);
			break;
		}

		case 6: {
			FromFile(stack);
			break;
		}

		case 7: {
			clear(stack);
			cout << "\n\nСтек очищен!\n\n";
			break;
		}

		case 0: {
			exit(0);
			break;
		}
		}
	}
}

void AddEl(int elem, STACK* stack)
{
	STACK* NewEl = new STACK;
	NewEl->data = elem;
	NewEl->next = stack->head;
	stack->head = NewEl;
}

int TakeFromStack(STACK* stack)
{
	if (stack->head == NULL)
	{
		cout << "Стек пуст";
		return -1;
	}
	else {
		STACK* intermEl = new STACK;
		int elData = stack->head->data;
		stack->head = stack->head->next;
		delete intermEl;
		return elData;
	}
}

void PrintStack(STACK* stack)
{
	STACK* sthead = stack->head;
	int elData;
	if (sthead == NULL)
		cout << "Стек пуст";
	while (sthead != NULL)
	{
		elData = sthead->data;
		cout << elData << " ";
		sthead = sthead->next;
	}
	cout << "\n";
}

void ToFile(STACK* stack)
{
	ofstream getf;
	getf.open("File13.txt");
	if (getf.is_open())
	{
		STACK* StackHead = stack->head;
		while (StackHead != NULL)
		{
			getf << StackHead->data << " ";
			StackHead = StackHead->next;
		}; cout << "\n";
	}
	getf.close();
	cout << "Информация записана в файл!\n\n";
}

void FromFile(STACK* stack)
{
	string line;
	ifstream outf("File13.txt");
	if (outf.is_open())
	{
		while (getline(outf, line))
		{
			outf >> line;
			cout << line << " ";
		}
	}
	outf.close();
	cout << "\nИнформация выведена из файла!\n\n";
}

int DeleteSame(STACK* stack)
{
	STACK* sthead = stack->head;
	int elData, arr[20], i = 0, point = -1;
	if (sthead == NULL)
		cout << "Стек пуст";
	while (sthead != NULL)
	{
		elData = sthead->data;
		arr[i] = elData;
		sthead = sthead->next;
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		int interm = arr[j], count = 0;
		for (int p = 0; j + p - 1 < i; p++)
		{
			if (arr[p] == interm)
				count++;
			if (count > 1)
			{
				point = p;
				j = i + 1;
				break;
			}
		}
	}
	return point;
}

void DeleteSameHelp(STACK* stack, int point)
{
	STACK* sthead1 = stack->head;
	for (int k = 0; k < point - 1; k++)
		sthead1 = sthead1->next;

	sthead1->next = sthead1->next->next;
}

void clear(STACK* stack)
{
	if (stack->head == NULL)
		cout << "Стек пуст";
	while (stack->head != NULL)
	{
		STACK* f = stack->head;
		stack->head = stack->head->next;
		delete f;
	}
	cout << "\n";
}*/
