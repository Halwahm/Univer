//#include <iostream>
//#include <cmath>
//#include <string>
//#include <fstream>
//
//using namespace std;
//struct stack
//{
//	int ind;
//	stack* next;
//};
//void length(stack** el, int n)
//{
//	stack* i = new stack;
//	i->ind = n;
//	i->next = *el;
//	*el = i;
//}
//void out(stack* el)
//{
//	stack* i = el;
//	if (el == NULL)
//	{
//		cout << "Список пуст";
//		return;
//	}
//	while (i != NULL)
//	{
//		cout << i->ind << endl;
//		i = i->next;
//	}
//}
//int main()
//{
//	int min = 256, j = 0;
//	setlocale(LC_CTYPE, "Russian");
//	stack* el = NULL;
//	ifstream file1("1.txt");
//	char str[255];
//	int n;
//	while (!file1.eof())
//	{
//		file1.getline(str, 255);
//		n = strlen(str);
//		length(&el, n);
//		if (n < min)
//		{
//			min = n;
//			j++;
//		}
//	}
//	file1.close();
//	out(el);
//	cout << endl;
//	cout << "Длина самой маленькой строки:" << min << endl;
//	cout << "Её номер:" << j << endl;
//	return 0;
//}