//#include<iostream>
//#include<tchar.h>
//#include"number.h"
//#include<fstream>
//#include <string>
//using namespace std;
//
//void create(Queue** begin, Queue** end, int p)
//{
//	Queue* t = new Queue;
//	t->next = NULL;
//	if (*begin == NULL)
//		*begin = *end = t;
//	else
//	{
//		t->info = p;
//		(*end)->next = t;
//		*end = t;
//	}
//}
//void view(Queue* begin)
//{
//	setlocale(LC_CTYPE, "RUSSIAN");
//	Queue* t = begin;
//	if (t == NULL)
//	{
//		cout << "Элементов нет\n";
//		return;
//	}
//	else
//		while (t != NULL)
//		{
//			cout << t->info << endl;
//			t = t->next;
//		}
//}
//Queue* maxElem(Queue* begin)
//{
//	Queue* t = begin;
//	int max;
//	if (t == NULL)
//	{
//		cout << "Элементов нет\n"; return 0;
//	}
//	else
//	{
//		max = t->info;
//		while (t != NULL)
//		{
//			if (t->info >= max)
//			{
//				max = t->info;
//			}
//			t = t->next;
//		}
//	}
//	cout << "Максимальный элемент=" << max << endl;
//}
//void size(Queue* begin)
//{
//	setlocale(LC_CTYPE, "RUSSIAN");
//	Queue* t = begin;
//	int sz = 0;
//	if (t == NULL)
//	{
//		cout << "Элементов нет\n";
//		return;
//	}
//	else
//		while (t != NULL)
//		{
//			t->info;
//			t = t->next;
//			sz++;
//		}
//	cout << "Размер очереди=" << sz << endl;
//}
//void del3(Queue** begin)
//{
//	Queue* t;
//	int i = 0;
//	while (*begin != NULL && i != 3)
//	{
//		t = *begin;
//		*begin = (*begin)->next;
//		delete t;
//		i++;
//	}
//
//}
//void delAll(Queue** begin)
//{
//	Queue* t;
//	while (*begin != NULL)
//	{
//		t = *begin;
//		*begin = (*begin)->next;
//		delete t;
//	}
//}