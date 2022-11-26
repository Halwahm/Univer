#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

struct PList{
	int x; //Информационное поле
	struct PList *Next; //Ссылка на следующий элемент списка
};

void CreateList(struct PList *Head, int Num)
{
//Процедура создает список, содержащий Len элементов, 
//начинающийся с элемента Head
	struct PList *H;
	if(Num > 1){
		//currentSS -> nextSS = (struct sSS *) new (struct sSS);
		//H = new (Head);
		H = (struct PList *) new (struct PList);

		//При работе с однонаправленными списками принципиально 
		//важно не потерять ссылку на первый элемент. Поэтому 
		//дальнейшие операции будем проводить не с Head, а со 
		//вспомогательной переменной H
		for(int n = 2; n <= Num; n++){
			  //H = new (H.Next);
			  //H = new (H.Next);
			H = (struct PList *) new (struct PList);
		}
		//H.Next = NULL;
		Head->Next = NULL;
	}
	else
		Head->Next = NULL;
}
 
void FreeList(struct PList *Head)
{
//Процедура освобождающая память, выделенную под список с 
//первым элементом Head
	struct PList *H;
	//Поскольку список все равно уничтожается, 
	//можем спокойно изменять Head
	while(Head != NULL){
		H = Head;
		Head = Head->Next;
		//Dispose(H);
	}
}
 
void FillList(struct PList *Head)
{
//Процедура заполняет информационную часть элементов списка 
//числами 1, 2, 3, …
	int n = 1;
	  while(Head != NULL){
		Head -> x = n;
		n = n + 1;
		Head = Head->Next;
	  }
}
 
void PrintList(struct PList *Head)
{
//Процедура печатает информационную часть элементов списка
	while(Head != NULL){
		//writeln(Head^.x);
		printf(" = %d\n", Head -> x);
		Head = Head->Next;
	}
}

void main()
{
	//FONT: Lucida Console
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); //установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_ALL, "Rus");
	struct PList List;
	CreateList(List, 5); //Создаем список из 5-ти элементов
	FillList(List); //В информационные части пишем числа 1, 2, 3, 4, 5
	PrintList(List); //Печатаем информационные части элементов списка
	ClearList(List); //Освобождаем память
	//printf("Для %d число Фибоначчи = %d\n", pp, Fib2(1, 1, pp));
	system("PAUSE");
}
