/*#include <iostream>
#include<fstream>

#define str_len 256
#define size 100

using namespace std;

//Преподаватели.Фамилия преподавателя, название экзамена, дата экзамена.
//Выбор по дате экзамена.Дату экзамена реализовать с помощью битового поля.

void enter_new();
void out();
void del();
void search();

struct teachers
{
	char surname_of_teacher[str_len];
	char exam[str_len];
	unsigned day : 4;
	unsigned month : 4;
	unsigned year : 4;

};
teachers allTeachers[size];
teachers all;
teachers b;
int choice; int current_size = 0;
int l, z, q;
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
		cout << endl << "Фамилия преподователя" << endl;
		cin >> allTeachers[current_size].surname_of_teacher;
		cout << "Экзамен" << endl;
		cin >> allTeachers[current_size].exam;
		cout << "Дата" << endl;
		cout << "День";
		cin >> l; b.day = l;
		cout << endl;
		cout << "Месяц";
		cin >> z; b.month = l;
		cout << endl;
		cout << "Год";
		cin >> q; b.year = l;
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
		cout << "Фамилия преподователя:";
		cout << allTeachers[n - 1].surname_of_teacher;
		cout << endl;
		cout << "Экзамен:";
		cout << allTeachers[n - 1].exam;
		cout << endl;
		cout << "Дата" << endl;
		cout << "День:";
		cout << l;
		cout << endl;
		cout << "Месяц:";
		cout << z;
		cout << endl;
		cout << "Год:";
		cout << q;
		cout << endl;


	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{

			cout << "Фамилия преподователя:";
			cout << allTeachers[i].surname_of_teacher;
			cout << endl;
			cout << "Экзамен:";
			cout << allTeachers[i].exam;
			cout << endl;
			cout << "Дата" << endl;
			cout << "День:";
			cout << l;
			cout << endl;
			cout << "Месяц:";
			cout << z;
			cout << endl;
			cout << "Год:";
			cout << q;
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
			allTeachers[de1] = allTeachers[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			allTeachers[i] = all;
	cout << "Что дальше?" << endl;
	cin >> choice;
}
void search()
{
	int day, month, year;
	cout << "Введите дату" << endl;
	cout << "День:";
	cin >> day;
	cout << endl;
	cout << "Месяц:";
	cin >> month;
	cout << endl;
	cout << "Год:";
	cin >> year;
	cout << endl;
	for (int f = 0; f < current_size; f++)
	{
		if (day == l && month == z && year == q)
		{
			cout << "Фамилия преподователя:";
			cout << allTeachers[f].surname_of_teacher;
			cout << endl;
			cout << "Экзамен";
			cout << allTeachers[f].exam;
			cout << endl;
			cout << "Дата" << endl;
			cout << "День:";
			cout << l;
			cout << endl;
			cout << "Месяц:";
			cout << z;
			cout << endl;
			cout << "Год:";
			cout << q;
			cout << endl;
		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}*/