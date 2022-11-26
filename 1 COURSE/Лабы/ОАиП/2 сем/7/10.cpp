/*Разработать функцию, которая определяет, есть ли в стеке хотя бы один элемент, лежащий в заданном диапазоне.*/
/*
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
	setlocale(LC_CTYPE, "RU");
	int lower, higher;
	cout << "Введите нижнюю границу: "; cin >> lower;
	cout << "Введите верхнюю границу: "; cin >> higher;
	if (lower > higher)
	{
		cout << "Неверная граница";
		exit(12);
	}
	int size = 5;
	int a;
	Stek* ptr_stek = &stek;
	for (int i = 0; i < size; i++)
	{
		cout << "Введите число: ";
		cin >> a;
		push(ptr_stek, a);
	}
	for (int i = 0; i < size; i++)
	{
		if (lower <= pop(ptr_stek) <= higher)
		{
			cout << "Такой элемент существует\n";
			exit(13);
		}
		else
		{
			cout << "Такого элемента не существует\n";
		}
	}
}*/