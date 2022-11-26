/*Разработать функцию удаления элементов стека, кратных 3, если такие есть.*/

#include <iostream>

using namespace std;

struct Stek
{
	int number;
	Stek* next;
} stek, stek_new;

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
	int a;
	int size_new = 0;
	Stek* ptr_stek = &stek;
	Stek* ptr_stek_new = &stek_new;
	for (int i = 0; i < size; i++)
	{
		cout << "Enter number: ";
		cin >> a;
		push(ptr_stek, a);
		if (pop(ptr_stek) % 3 != 0)
		{
			push(ptr_stek_new, a);
			size_new++;
		}
	}
	for (int i = 0; i < size_new; i++)
	{
		cout << pop(ptr_stek_new) << endl;
	}
}