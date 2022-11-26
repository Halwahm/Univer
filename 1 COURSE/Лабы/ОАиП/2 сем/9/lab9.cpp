#include <iostream>
#include <fstream>

using namespace std;

/*deleteEveryМ(int m) – функция удаления каждого М - ого элемента списка.*/
//const unsigned int NAME_SIZE = 30;
//const unsigned int CITY_SIZE = 20;
//
//struct Address
//{
//	char name[NAME_SIZE];
//	char city[CITY_SIZE];
//	Address* next;
//	Address* prev;
//};
////-----------------------------------------------------------
//void insert(Address* e, Address** phead, Address** plast) //Добавление в конец списка
//{
//	Address* p = *plast;
//	if (*plast == NULL)
//	{
//		e->next = NULL;
//		e->prev = NULL;
//		*plast = e;
//		*phead = e;
//		return;
//	}
//	else
//	{
//		p->next = e;
//		e->next = NULL;
//		e->prev = p;
//		*plast = e;
//	}
//}
////-----------------------------------------------------------
//Address* setElement() // Создание элемента и ввод его значений с клавиатуры
//{
//	Address* temp = new Address();
//	if (!temp)
//	{
//		cerr << "Ошибка выделения памяти памяти";
//		return NULL;
//	}
//	cout << "Введите имя: ";
//	cin >> temp->name;
//	cout << "Введите город: ";
//	cin >> temp->city;
//	temp->next = NULL;
//	temp->prev = NULL;
//	return temp;
//}
////-----------------------------------------------------------
//void outputList(Address** phead, Address** plast) //Вывод списка на экран
//{
//	Address* t = *phead;
//	while (t)
//	{
//		cout << t->name << ' ' << t->city << endl;
//		t = t->next;
//	}
//	cout << "" << endl;
//}
////-----------------------------------------------------------
//void find(char name[NAME_SIZE], Address** phead) // Поиск имени в списке
//{
//	Address* t = *phead;
//	while (t)
//	{
//		if (!strcmp(name, t->name)) break;
//		t = t->next;
//	}
//	if (!t)
//		cerr << "Имя не найдено" << endl;
//	else
//		cout << t->name << ' ' << t->city << endl;
//}
////-----------------------------------------------------------
//void delet(char name[NAME_SIZE], Address** phead, Address** plast)// Удаление элемента по имени
//{
//	struct Address* t = *phead;
//	while (t)
//	{
//		if (!strcmp(name, t->name)) break;
//		t = t->next;
//	}
//	if (!t)
//		cerr << "Имя не найдено" << endl;
//	else
//	{
//		if (*phead == t)
//		{
//			*phead = t->next;
//			if (*phead)
//				(*phead)->prev = NULL;
//			else
//				*plast = NULL;
//		}
//		else
//		{
//			t->prev->next = t->next;
//			if (t != *plast)
//				t->next->prev = t->prev;
//			else
//				*plast = t->prev;
//		}
//		delete t;
//		cout << "Элемент удален" << endl;
//	}
//}
////-----------------------------------------------------------
//void writeToFile(Address** phead) //Запись в файл
//{
//	struct Address* t = *phead;
//	ofstream file1("Lip.txt");
//	if (file1.fail())
//	{
//		cerr << "Файл не открывается" << endl;
//		exit(1);
//	}
//	cout << "Сохранение в файл" << endl;
//	while (t)
//	{
//		file1 << t->name << " " << t->city << endl;
//		t = t->next;
//	}
//	file1.close();
//}
////---------------------------------------------------------------
//void fromFile(Address** phead)
//{
//
//	char buf[256];
//	ifstream file2("Lip.txt");
//	if (file2.fail())
//	{
//		cout << "\n Ошибка открытия файла";
//		exit(1);
//	}
//	while (!file2.eof())
//	{
//		file2.getline(buf, 256);
//		if (strlen(buf))
//			cout << " " << buf;
//		cout << endl;
//	}
//
//	file2.close();
//}
//
//void delm(Address** phead, Address** plast, int m)
//{
//	Address* t = *phead;
//
//	while (t)
//	{
//		if ((m++) % 2 == 0)
//		{
//			if (*phead == t)
//			{
//				*phead = t->next;
//				if (*phead)
//					(*phead)->prev = NULL;
//				else
//					*plast = NULL;
//			}
//			else
//			{
//				t->prev->next = t->next;
//				if (t != *plast)
//					t->next->prev = t->prev;
//				else
//					*plast = t->prev;
//			}
//			delete t;
//			return;
//		}
//		t = t->next;
//	}
//}
//int main()
//{
//	Address* head = NULL;
//	Address* last = NULL;
//	setlocale(LC_CTYPE, "Rus");
//	int choice;
//	char s[80]; int c;
//	cout << endl;
//	cout << "1. Ввод адреса" << endl;
//	cout << "2. Удаление имени" << endl;
//	cout << "3. Вывод на экран" << endl;
//	cout << "4. Поиск" << endl;
//	cout << "5. В файл" << endl;
//	cout << "6. Из файла" << endl;
//	cout << "7. Удалени каждого m элемента" << endl;
//	cout << "8. Выход" << endl;
//	cout << endl;
//	for (;;)
//	{
//		cout << "Ваш выбор: ";
//		cin >> choice;
//		switch (choice)
//		{
//		case 1: insert(setElement(), &head, &last);
//			break;
//		case 2: { char dname[NAME_SIZE];
//			cout << "Введите имя: ";
//			cin >> dname;
//			delet(dname, &head, &last);
//		}
//			  break;
//		case 3: outputList(&head, &last);
//			break;
//		case 4: { char fname[NAME_SIZE];
//			cout << "Введите имя: ";
//			cin >> fname;
//			find(fname, &head);
//		}
//			  break;
//		case 5: {
//			writeToFile(&head);
//		}
//			  break;
//		case 6: {
//			fromFile(&head);
//		}
//			  break;
//		case 7: {
//			int m = 1;
//			delm(&head, &last, m);
//		}
//			  break;
//		case 8: exit(0);
//		default: exit(1);
//		}
//	}
//	return 0;
//}


//=======================================================

/*1 доп
Дополнить проект, разработав функцию
deleteList (удаление списка) и функцию
countList (подсчет числа элементов списка).
В содержимом списка отразить информацию
в соответствии со своим вариантом из лабораторной
работы № 4. Создать интерфейс в виде меню.
Клиенты банка. Ф.И.О., тип счета (срочный,
льготный и т. д.), номер счета, сумма
на счете, дата последне-го изменения.
Выбор по номеру счета.
*/

//#include <iostream>
//#include "List.h"
//using namespace std;
//void insert(address* e, address** phead, address** plast)
//{
//	address* p = *plast;
//	if (*plast == NULL)
//	{
//		e->next = NULL;
//		e->prev = NULL;
//		*plast = e;
//		*phead = e;
//		return;
//	}
//	else
//	{
//		p->next = e;
//		e->next = NULL;
//		e->prev = p;
//		*plast = e;
//	}
//}
////-----------------------------------------------------------
//address* setelement()
//{
//	address* temp = new address();
//	if (!temp)
//	{
//		cerr << "ошибка выделения памяти памяти";
//		return NULL;
//	}
//	cout << "введите фамилию: ";
//	cin >> temp->surname;
//	cout << "введите имя: ";
//	cin >> temp->name;
//	cout << "введите отчество: ";
//	cin >> temp->parentname;
//	cout << "введите тип счета: ";
//	cin >> temp->type;
//	cout << "введите номер счета: ";
//	cin >> temp->number;
//	cout << "введите сумму на счете: ";
//	cin >> temp->sum;
//	cout << "введите дату последнего изменения: ";
//	cin >> temp->date;
//	temp->next = NULL;
//	temp->prev = NULL;
//	return temp;
//}
//void outputlist(address** phead, address** plast)
//{
//	address* t = *phead;
//	if (t == NULL)
//	{
//		cout << "список пуст!" << endl;
//	}
//	while (t)
//	{
//		cout << "фамилия:" << t->surname << endl;
//		cout << "имя:" << t->name << endl;
//		cout << "отчество:" << t->parentname << endl;
//		cout << "тип счета:" << t->type << endl;
//		cout << "номер счета:" << t->number << endl;
//		cout << "сумма на счете:" << t->sum << endl;
//		cout << "дата последнего измененеия:" << t->date << endl;
//		t = t->next;
//	}
//	cout << "" << endl;
//}
//void find(char number[NAME_SIZE], address** phead)
//{
//	address* t = *phead;
//	while (t)
//	{
//		if (!strcmp(number, t->number)) break;
//		t = t->next;
//	}
//	if (!t)
//		cerr << "имя не найдено" << endl;
//	else
//		cout << "фамилия:" << t->surname << endl;
//	cout << "имя:" << t->name << endl;
//	cout << "отчество:" << t->parentname << endl;
//	cout << "тип счета:" << t->type << endl;
//	cout << "номер счета:" << t->number << endl;
//	cout << "сумма на счете:" << t->sum << endl;
//	cout << "дата последнего измененеия:" << t->date << endl;
//}
//void countlist(address** phead, address** plast)
//{
//	address* t = *phead;
//	int i = 0;
//	while (t != NULL)
//	{
//		i++;
//		t = t->next;
//	}
//	cout << "количество элементов=" << i << endl;
//}
//void delall(address** phead, address** plast)
//{
//	address* t = *phead;
//	while (t != NULL)
//	{
//
//		if (*phead == t)
//		{
//			*phead = t->next;
//			if (*phead)
//				(*phead)->prev = NULL;
//			else
//				*plast = NULL;
//		}
//		else
//		{
//			t->prev->next = t->next;
//			if (t != *plast)
//				t->next->prev = t->prev;
//			else
//				*plast = t->prev;
//		}
//		t = t->next;
//		delete t;
//	}
//	cout << "список очищен!" << endl;
//}
//int main()
//{
//	address* head = NULL;
//	address* last = NULL;
//	setlocale(LC_CTYPE, "rus");
//	int choice;
//	char s[80]; int c;
//	cout << endl;
//	cout << "1. ввод элемента" << endl;
//	cout << "2. вывод на экран" << endl;
//	cout << "3. поиск" << endl;
//	cout << "4. количсетво элементов" << endl;
//	cout << "5. очищение списка" << endl;
//	cout << "6. выход" << endl;
//	cout << endl;
//	for (;;)
//	{
//		cout << "ваш выбор: ";
//		cin >> choice;
//		switch (choice)
//		{
//		case 1: insert(setelement(), &head, &last);
//			break;
//		case 2: outputlist(&head, &last);
//			break;
//		case 3: { char fnumber[NAME_SIZE];
//			cout << "введите номер: ";
//			cin >> fnumber;
//			find(fnumber, &head);
//		}
//			  break;
//		case 4: {
//
//			countlist(&head, &last);
//		}
//			  break;
//		case 5: {
//			delall(&head, &last);
//		}
//			  break;
//		case 6: exit(0);
//		default: exit(1);
//		}
//	}
//	return 0;
//}

//=======================================================


/*2
//Каждый элемент списка студентов содержит фамилию,
//имя, отчество, год рождения, курс, номер группы, 
//оценки по пяти предметам. Упорядочить студентов 
//по курсу, причем студенты одного курса должны 
//располагаться в алфавит-ном порядке. Найти средний
//балл каждой группы по каждому предмету. Определить 
//самого старшего студента и само-го младшего студентов. 
//Для каждой группы найти лучшего с точки зрения
//успеваемости студента.*/

//#include <iomanip>
//#include "List1.h"
//#include <iostream>
//using namespace std;
//void insert(Address* e, Address** phead, Address** plast)
//{
//	Address* p = *plast;
//	if (*plast == NULL)
//	{
//		e->next = NULL;
//		e->prev = NULL;
//		*plast = e;
//		*phead = e;
//		return;
//	}
//	else
//	{
//		p->next = e;
//		e->next = NULL;
//		e->prev = p;
//		*plast = e;
//	}
//}
////-----------------------------------------------------------
//Address* setElement()
//{
//	Address* temp = new Address();
//	if (!temp)
//	{
//		cerr << "Ошибка выделения памяти памяти";
//		return NULL;
//	}
//	cout << "Введите фамилию: ";
//	cin >> temp->surname;
//	cout << "Введите имя: ";
//	cin >> temp->name;
//	cout << "Введите отчество: ";
//	cin >> temp->parentname;
//	cout << "Введите дату рождения: " << endl;;
//	cout << "Введите день:";
//	cin >> temp->day;
//	cout << endl;
//	cout << "Введите месяц:";
//	cin >> temp->month;
//	cout << endl;
//	cout << "Введите год:";
//	cin >> temp->year;
//	cout << endl;
//	cout << "Введите номер курса: ";
//	cin >> temp->course;
//	cout << "Введите номер группы: ";
//	cin >> temp->group;
//	cout << "Введите оценки по предметам: " << endl;
//	cout << "Математика:";
//	cin >> temp->math;
//	cout << endl;
//	cout << "ОАиП:";
//	cin >> temp->OAIP;
//	cout << endl;
//	cout << "Английский язык:";
//	cin >> temp->English;
//	cout << endl;
//	cout << "ЯП:";
//	cin >> temp->Yap;
//	cout << endl;
//	cout << "КЯР:";
//	cin >> temp->Kyar;
//	cout << endl;
//	temp->next = NULL;
//	temp->prev = NULL;
//	return temp;
//}
//void outputList(Address** phead, Address** plast)
//{
//	Address* t = *phead;
//	if (t == NULL)
//	{
//		cout << "Список пуст!" << endl;
//	}
//	while (t)
//	{
//
//		cout << "--------------------------------------------------" << endl;
//		cout << "Фамилия:" << t->surname << endl;
//		cout << "Имя:" << t->name << endl;
//		cout << "Отчество:" << t->parentname << endl;
//		cout << "Дата рождения:" << t->day << "." << t->month << "." << t->year << endl;
//		cout << "Курс:" << t->course << endl;
//		cout << "Группа:" << t->group << endl;
//		cout << "Оценки:" << endl;
//		cout << "Математика:" << t->math << endl;
//		cout << "ОАиП:" << t->OAIP << endl;
//		cout << "Английский язык:" << t->English << endl;
//		cout << "ЯП:" << t->Yap << endl;
//		cout << "КЯР:" << t->Kyar << endl;
//		t = t->next;
//
//	}
//}
//void outputFirstCourse(Address** phead, Address** plast)
//{
//	int i = 0;
//	Address* t = *phead;
//	if (t == NULL)
//	{
//		cout << "Список пуст!" << endl;
//	}
//	cout << "---------------------Студенты 1 курса-------------------" << endl;
//	if (strcmp(t->surname, (t->next)->surname) > 0)
//	{
//		t = t->next;
//		t->next = t->prev;
//		t->prev = t;
//	}
//	while (i != 2)
//	{
//
//
//		if (t->course == 1)
//		{
//			cout << "--------------------------------------------------" << endl;
//			cout << "Фамилия:" << t->surname << endl;
//			cout << "Имя:" << t->name << endl;
//			cout << "Отчество:" << t->parentname << endl;
//			cout << "Дата рождения:" << t->day << "." << t->month << "." << t->year << endl;
//			cout << "Курс:" << t->course << endl;
//			cout << "Группа:" << t->group << endl;
//			cout << "Оценки:" << endl;
//			cout << "Математика:" << t->math << endl;
//			cout << "ОАиП:" << t->OAIP << endl;
//			cout << "Английский язык:" << t->English << endl;
//			cout << "ЯП:" << t->Yap << endl;
//			cout << "КЯР:" << t->Kyar << endl;
//			t = t->next;
//		}
//		else
//		{
//			t = t->next;
//		}
//
//		i++;
//	}
//}
//void outputSecondCourse(Address** phead, Address** plast)
//{
//	Address* t = *phead;
//	if (t == NULL)
//	{
//		cout << "Список пуст!" << endl;
//	}
//	cout << "--------------------Студенты 2 курса----------------" << endl;
//	while (t)
//	{
//		if (t->course == 2)
//		{
//			cout << "--------------------------------------------------" << endl;
//			cout << "Фамилия:" << t->surname << endl;
//			cout << "Имя:" << t->name << endl;
//			cout << "Отчество:" << t->parentname << endl;
//			cout << "Дата рождения:" << t->day << "." << t->month << "." << t->year << endl;
//			cout << "Курс:" << t->course << endl;
//			cout << "Группа:" << t->group << endl;
//			cout << "Оценки:" << endl;
//			cout << "Математика:" << t->math << endl;
//			cout << "ОАиП:" << t->OAIP << endl;
//			cout << "Английский язык:" << t->English << endl;
//			cout << "ЯП:" << t->Yap << endl;
//			cout << "КЯР:" << t->Kyar << endl;
//			t = t->next;
//		}
//		else
//			t = t->next;
//
//	}
//}
//void outputThirdCourse(Address** phead, Address** plast)
//{
//	Address* t = *phead;
//	if (t == NULL)
//	{
//		cout << "Список пуст!" << endl;
//	}
//	cout << "--------------------Студенты 3 курса----------------" << endl;
//	while (t)
//	{
//		if (t->course == 3)
//		{
//			cout << "--------------------------------------------------" << endl;
//			cout << "Фамилия:" << t->surname << endl;
//			cout << "Имя:" << t->name << endl;
//			cout << "Отчество:" << t->parentname << endl;
//			cout << "Дата рождения:" << t->day << "." << t->month << "." << t->year << endl;
//			cout << "Курс:" << t->course << endl;
//			cout << "Группа:" << t->group << endl;
//			cout << "Оценки:" << endl;
//			cout << "Математика:" << t->math << endl;
//			cout << "ОАиП:" << t->OAIP << endl;
//			cout << "Английский язык:" << t->English << endl;
//			cout << "ЯП:" << t->Yap << endl;
//			cout << "КЯР:" << t->Kyar << endl;
//			t = t->next;
//		}
//		else
//			t = t->next;
//
//	}
//}
//void outputFourthCourse(Address** phead, Address** plast)
//{
//	Address* t = *phead;
//	if (t == NULL)
//	{
//		cout << "Список пуст!" << endl;
//	}
//	cout << "--------------------Студенты 4 курса----------------" << endl;
//	while (t)
//	{
//		if (t->course == 4)
//		{
//			cout << "--------------------------------------------------" << endl;
//			cout << "Фамилия:" << t->surname << endl;
//			cout << "Имя:" << t->name << endl;
//			cout << "Отчество:" << t->parentname << endl;
//			cout << "Дата рождения:" << t->day << "." << t->month << "." << t->year << endl;
//			cout << "Курс:" << t->course << endl;
//			cout << "Группа:" << t->group << endl;
//			cout << "Оценки:" << endl;
//			cout << "Математика:" << t->math << endl;
//			cout << "ОАиП:" << t->OAIP << endl;
//			cout << "Английский язык:" << t->English << endl;
//			cout << "ЯП:" << t->Yap << endl;
//			cout << "КЯР:" << t->Kyar << endl;
//			t = t->next;
//		}
//		else
//			t = t->next;
//
//	}
//}
//void studentOld(Address** phead, Address** plast)
//{
//	int old = 0;
//	Address* tmp = *phead;
//	old = tmp->year;
//	while (tmp)
//	{
//
//		if (tmp->year < old)
//		{
//			old = tmp->year;
//		}
//		tmp = tmp->next;
//
//	}
//	Address* t = *phead;
//	while (t)
//	{
//		if (t->year == old)
//		{
//			cout << "Старший студент=" << t->surname << endl;
//		}
//		t = t->next;
//	}
//
//}
//void studentYoung(Address** phead, Address** plast)
//{
//	int young = 0;
//	Address* tmp = *phead;
//	young = tmp->year;
//	while (tmp)
//	{
//
//		if (tmp->year > young)
//		{
//			young = tmp->year;
//		}
//		tmp = tmp->next;
//
//	}
//	Address* t = *phead;
//	while (t)
//	{
//		if (t->year == young)
//		{
//			cout << "Младший студент=" << t->surname << endl;
//		}
//		t = t->next;
//	}
//}
//void average(Address** phead, Address** plast)
//{
//	float average1 = 0, average2 = 0, average3 = 0;
//	Address* t = *phead;
//	while (t)
//	{
//		average1 = (t->English + t->math + t->Kyar + t->Yap + t->OAIP) / 5;
//		cout << "Студент:" << t->surname << " " << "средний балл=" << average1 << endl;
//		t = t->next;
//		average2 = (t->English + t->math + t->Kyar + t->Yap + t->OAIP) / 5;
//		cout << "Студент:" << t->surname << " " << "средний балл=" << average2 << endl;
//		t = t->next;
//
//	}
//	Address* emp = *phead;
//	while (emp)
//	{
//		if (average1 >= average2 && average1 >= average3)
//		{
//			cout << "Best students:" << emp->surname << endl;
//		}
//		emp = emp->next;
//		if (average2 >= average1 && average2 >= average3)
//		{
//			cout << "Best students:" << emp->surname << endl;
//		}
//		emp = emp->next;
//
//
//	}
//}
//int main()
//{
//	Address* head = NULL;
//	Address* last = NULL;
//	setlocale(LC_CTYPE, "Rus");
//	int choice;
//	char s[80]; int c;
//	cout << endl;
//	cout << "1. Ввод элемента" << endl;
//	cout << "2. Старший студент" << endl;
//	cout << "3. Младший студент" << endl;
//	cout << "4. Лучший ученик" << endl;
//	cout << "5. вывод списка" << endl;
//	cout << "6. 1 курс" << endl;
//	cout << "7. 2 курс" << endl;
//	cout << "8. 3 курс" << endl;
//	cout << "9. 4 курс" << endl;
//	cout << "10. Выход" << endl;
//	cout << endl;
//	for (;;)
//	{
//		cout << "Ваш выбор: ";
//		cin >> choice;
//		switch (choice)
//		{
//		case 1: insert(setElement(), &head, &last);
//			break;
//		case 2: studentOld(&head, &last);
//			break;
//		case 3: studentYoung(&head, &last);
//			break;
//		case 4: average(&head, &last);
//			break;
//		case 5: outputList(&head, &last);
//			break;
//		case 6: outputFirstCourse(&head, &last);
//			break;
//		case 7:
//			outputSecondCourse(&head, &last);
//			break;
//		case 8:
//			outputThirdCourse(&head, &last);
//			break;
//		case 9:
//			outputFourthCourse(&head, &last);
//			break;
//		case 10: exit(0);
//		default: exit(1);
//		}
//	}
//	return 0;
//}

//===========================================================


/*3 доп 
N человек  располагаются  по кругу.  
Начав отсчет от первого, удаляют каждого k-го, 
смыкая круг после удаления. Определить порядок у
даления людей из круга. Использовать линейный список.*/

#include <iostream>
#include <conio.h>
using namespace std;

struct Node
{
	int x;
	Node* Next;
	Node* Prev;
};

struct List
{
	Node* Head = NULL, * Tail = NULL;
	int size = 0;
	void Add(int x);
	bool del(int k);
	void Show(int size);
	int Count();
};



int List::Count()
{
	return size;
}

void List::Add(int x)
{
	size++;
	Node* temp = new Node;
	temp->Next = Head;
	temp->x = x;

	if (Head != NULL)
	{
		Tail->Next = temp;
		Tail = temp;
	}
	else Head = Tail = temp;
}

bool List::del(int k)
{
	if (Head == NULL) {
		cout << "Список пуст" << endl;
		return false;
	}
	else
		Node* temp = new Node;
	Node* temp = Tail;
	while (Head != Tail)
	{
		for (int i = 1; i < k; i++)
		{
			temp = temp->Next;
			Node* buf = temp->Next;
			cout << buf->x << " ";
			if (buf == Head)
			{
				Head = buf->Next;
			}
			if (buf == Tail)
			{
				Tail = temp;
			}
			temp->Next = buf->Next;
			delete buf;
		}
	}
	return true;
}

void List::Show(int temp)
{
	Node* tempHead = Head;

	temp = size;
	while (temp != 0)
	{
		cout << tempHead->x << " ";
		tempHead = tempHead->Next;
		temp--;
	}
}
void main()
{
	setlocale(LC_ALL, "Russian");
	int n, k;
	List lst;
	cout << "Введите кол-во элементов в списке" << endl;
	cin >> n;
	for (int i = 1; i < n + 1; i++)
	{
		lst.Add(i);
	}
	cout << "Список:" << endl;
	lst.Show(lst.Count());
	cout << endl;
	cout << "Введите k:" << endl;
	cin >> k;
	cout << endl;
	cout << "Порядок удаления:";
	lst.del(k);
}