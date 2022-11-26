/*Разработать функцию подсчета количества повторяющихся элементов стека.*/
/*
#include <iostream>

using namespace std;

struct Stek
{
	int number;
	Stek* next;
} stek, stek_new;

struct mas_of_elements
{
	int number;
	int amount = 0;
};

int pop(Stek*& st) // Извлечение элемента
{
	int tmp = st->number;
	Stek* pv = st;
	st = st->next;       // вершиной становится предшествующий элемент
	delete pv;           // освобождается память 
	return tmp;
}

void push(Stek*& st, int d) // Добавление элемента
{
	Stek* pv = new Stek;
	pv->number = d;   // значение помещается в стек     
	pv->next = st;
	st = pv;
}


void main()
{
	int size = 5;
	mas_of_elements* ptr_mas_of_elements = new mas_of_elements[size];
	int a;
	Stek* ptr_stek = &stek;
	Stek* ptr_stek_new = &stek_new;
	for (int i = 0; i < size; i++)
	{
		mas_of_elements* ptr_i = ptr_mas_of_elements + i;
		cout << "Enter number: ";
		cin >> a;
		push(ptr_stek, a);
		ptr_i->number = a;
	}
	int amount_of_repeating = 0;
	for (int i = 0; i < size; i++)
	{
		mas_of_elements* ptr_i = ptr_mas_of_elements + i;
		for (int j = 0; j < i; j++)
		{
			mas_of_elements* ptr_j = ptr_mas_of_elements + j;
			if (ptr_i->number == ptr_j->number)
			{
				amount_of_repeating++;
				break;
			}
		}
	}
	cout << "Count: " << amount_of_repeating << endl;
}*/