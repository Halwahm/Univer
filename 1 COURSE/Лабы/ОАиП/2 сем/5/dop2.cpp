/*#include <iostream>
#include<fstream>

#define str_len 256
#define size 100

using namespace std;

//Записная книжка.Ф.И.О, дата рождения, адрес, телефон.
//Поиск по фамилии.Дату рождения реализовать с помощью битового поля.

void enter_new();
void out();
void del();
void search();

struct notebook
{
	char name[str_len];
	char surname[str_len];
	char middleName[str_len];
	unsigned day : 4;
	unsigned month : 4;
	unsigned year : 4;
	char addres[str_len];
	int phone;
	char place_of_work[str_len];
	char position[str_len];
};
struct notebook people_in_notebook[size];
int current_size = 0; int choice;
notebook all;
notebook b;
int l, z, x;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите:" << endl;
	cout << "1-для ввода записи" << endl;
	cout << "2-для вывода записи" << endl;
	cout << "3-для удаления" << endl;
	cout << "4-для поиска информации" << endl;
	cout << "5-для выхода" << endl;
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1: enter_new(); break;
		case 2: out(); break;
		case 3: del(); break;
		case 4: search(); break;


		}
	} while (choice != 5);
}
void enter_new()
{
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "Фамилия" << endl;
		cin >> people_in_notebook[current_size].surname;
		cout << "Имя" << endl;
		cin >> people_in_notebook[current_size].name;
		cout << "Отчество" << endl;
		cin >> people_in_notebook[current_size].middleName;
		cout << "Дата рождения: " << endl;
		cout << "День:";
		cin >> l; b.day = l;
		cout << endl;
		cout << "Месяц:";
		cin >> z; b.month = z;
		cout << endl;
		cout << "Год:";
		cin >> x; b.year = x;
		cout << endl;
		cout << "Адрес:" << endl;
		cin >> people_in_notebook[current_size].addres;
		cout << "Номер телефона:" << endl;
		cin >> people_in_notebook[current_size].phone;
		cout << "Место работы:" << endl;
		cin >> people_in_notebook[current_size].place_of_work;
		cout << "Должность:" << endl;
		cin >> people_in_notebook[current_size].position;
		current_size++;

	}
	else
		cout << "Введено максимальное кол-во строк";
	cout << "Что дальше?" << endl;
	cin >> choice;
}
void out()
{
	int sw, n;
	cout << "1-вывод 1 строки" << endl;
	cout << "2-вывод всех строк" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "Номер выводимой строки: " << endl; cin >> n; cout << endl;
		cout << "Фамилия" << endl;
		cout << people_in_notebook[n - 1].surname;
		cout << endl;
		cout << "Имя" << endl;
		cout << people_in_notebook[n - 1].name;
		cout << endl;
		cout << "Отчество" << endl;
		cout << people_in_notebook[n - 1].middleName;
		cout << endl;
		cout << "Дата рождения: " << endl;
		cout << "День:";
		cout << l;
		cout << endl;
		cout << "Месяц:";
		cout << z;
		cout << endl;
		cout << "Год:";
		cout << x;
		cout << endl;
		cout << "Адрес:" << endl;
		cout << people_in_notebook[n - 1].addres;
		cout << endl;
		cout << "Номер телефона:" << endl;
		cout << people_in_notebook[n - 1].phone;
		cout << endl;
		cout << "Место работы:" << endl;
		cout << people_in_notebook[n - 1].place_of_work;
		cout << endl;
		cout << "Должность:" << endl;
		cout << people_in_notebook[n - 1].position;
		cout << endl;


	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "Фамилия" << endl;
			cout << people_in_notebook[i].surname;
			cout << endl;
			cout << "Имя" << endl;
			cout << people_in_notebook[i].name;
			cout << endl;
			cout << "Отчество" << endl;
			cout << people_in_notebook[i].middleName;
			cout << endl;
			cout << "Дата рождения: " << endl;
			cout << "День:";
			cout << l;
			cout << endl;
			cout << "Месяц:";
			cout << z;
			cout << endl;
			cout << "Год:";
			cout << x;
			cout << endl;
			cout << "Адрес:" << endl;
			cout << people_in_notebook[i].addres;
			cout << endl;
			cout << "Номер телефона:" << endl;
			cout << people_in_notebook[i].phone;
			cout << endl;
			cout << "Место работы:" << endl;
			cout << people_in_notebook[i].place_of_work;
			cout << endl;
			cout << "Должность:" << endl;
			cout << people_in_notebook[i].position;
			cout << endl;

		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}
void del()
{
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;
	cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			people_in_notebook[de1] = people_in_notebook[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			people_in_notebook[i] = all;
	cout << "Что дальше?" << endl;
	cin >> choice;
}
void search()
{
	char surname[16];
	cout << "Фамилия:" << "\n";
	cin >> surname;
	for (int q = 0; q < current_size; q++)
	{
		if (strcmp(surname, people_in_notebook[q].surname) == 0)
		{
			cout << "Фамилия" << endl;
			cout << people_in_notebook[q].surname;
			cout << endl;
			cout << "Имя" << endl;
			cout << people_in_notebook[q].name;
			cout << endl;
			cout << "Отчество" << endl;
			cout << people_in_notebook[q].middleName;
			cout << endl;
			cout << "Дата рождения: " << endl;
			cout << "День:";
			cout << l;
			cout << endl;
			cout << "Месяц:";
			cout << z;
			cout << endl;
			cout << "Год:";
			cout << x;
			cout << endl;
			cout << "Адрес:" << endl;
			cout << people_in_notebook[q].addres;
			cout << endl;
			cout << "Номер телефона:" << endl;
			cout << people_in_notebook[q].phone;
			cout << endl;
			cout << "Место работы:" << endl;
			cout << people_in_notebook[q].place_of_work;
			cout << endl;
			cout << "Должность:" << endl;
			cout << people_in_notebook[q].position;
			cout << endl;
		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}*/