/*1. Дана величина a строкового типа из четного
количества символов. Получить и напечатать величину b,
состоящую из символов первой половины величины a, 
записанных в обратном порядке, после которых идут 
символы второй половины величины a, также записанные
в обратном порядке (например, при а = “привет” b 
должно быть равно «ипртев»).*/

#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	char str[20];
	int dl;
	Stack* myStk = new Stack; //выделение памяти для стека
	myStk->head = NULL;       //инициализация первого элемента 
	while (strlen(str) % 2 != 0) {
		cout << "Строка с четным количеством символов" << endl;
		cin >> str;
	}
	dl = strlen(str);
	for (int i = (dl / 2); i < dl; i++) {
		push(str[i], myStk);
	}
	for (int i = 0; i < (dl / 2); i++) {
		push(str[i], myStk);
	}
	show(myStk);
}