//#include <iostream>
//#include "stack.h"
//
//using namespace std;
//
//void push(char x, Stack* myStk)   //���������� �������� � � ���� 
//{
//	Stack* e = new Stack;    //��������� ������ ��� ������ ��������
//	e->data = x;             //������ �������� x � ���� v 
//	e->next = myStk->head;   //������� ������� �� ��������� ������� 
//	myStk->head = e;         //����� ������� �� ������� ������
//}
//int pop(Stack* myStk)   //���������� (��������) �������� �� �����
//{
//	if (myStk->head == NULL)
//	{
//		cout << "���� ����!" << endl;
//		return -1;               //���� ���� ���� - ������� -1 
//	}
//	else
//	{
//		Stack* e = myStk->head;   //� - ���������� ��� �������� ������ ��������
//		char a = myStk->head->data;   //������ ����� �� ���� data � ���������� a 
//		myStk->head = myStk->head->next; //������� �������
//		delete e;                        //�������� ��������� ����������
//		return a;                        //������� �������� ���������� ��������
//	}
//}
//void show(Stack* myStk)    //����� �����
//{
//	Stack* e = myStk->head;    //����������� ��������� �� ������� �����
//	char a;
//	if (e == NULL)
//		cout << "���� ����!" << endl;
//	while (e != NULL)
//	{
//		a = e->data;          //������ �������� � ���������� a 
//		cout << a << " ";
//		e = e->next;
//	}
//	cout << endl;
//}