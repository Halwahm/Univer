/*

#include <iostream>
#include <fstream>
#define str_len 256 
#define size 100 

using namespace std;

void enter_new();
void out();
void del();
void search();

struct Pupil
{
	char name[str_len];
	char surname[str_len];
	char middleName[str_len];
	unsigned  number : 4;
	unsigned letter : 8;
	float average_scoree;
};

enum Subjects
{
	Math, Biology, History, Chemistry, Physics, Englysh, PE, Geography
} subject;

int marks;
int average_score;
struct Pupil pupilss_of_school[size];
int current_size = 0;
int choice;
Pupil b;
Pupil all;
int l;
char f;
float markss[8];
float average;

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
		case 1:  enter_new();	break;
		case 2:  out();  break;
		case 3:  del();  break;
		case 4:  search();	break;
		}
	} while (choice != 5);
}

void enter_new() {
	cout << "Вывод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "Фамилия" << endl;
		cin >> pupilss_of_school[current_size].surname;
		cout << "Имя" << endl;
		cin >> pupilss_of_school[current_size].name;
		cout << "Отчество" << endl;
		cin >> pupilss_of_school[current_size].middleName;
		cout << "Класс: " << endl;
		cin >> l; b.number = l;
		cin >> f; b.letter = f;
		cout << "Предметы:" << endl;
		Subjects::Math;
		cout << "Математка:";
		cin >> markss[0];
		cout << "\n";
		Subjects::Biology;
		cout << "Биология:";
		cin >> markss[1];
		cout << "\n";
		Subjects::History;
		cout << "История:";
		cin >> markss[2];
		cout << "\n";
		Subjects::Chemistry;
		cout << "Химия:";
		cin >> markss[3];
		cout << "\n";
		Subjects::Physics;
		cout << "Физика:";
		cin >> markss[4];
		cout << "\n";
		Subjects::Englysh;
		cout << "Английский:";
		cin >> markss[5];
		cout << "\n";
		Subjects::PE;
		cout << "Физкультура:";
		cin >> markss[6];
		cout << "\n";
		Subjects::Geography;
		cout << "География:";
		cin >> markss[7];
		cout << "\n";
		cout << "Средний балл:" << endl;
		average = ((markss[0] + markss[1] + markss[2] + markss[3] + markss[4] + markss[5] + markss[6] + markss[7]) / 8);
		cout << average << "\n";
		current_size++;
	}
	else
		cout << "Введено максимальное кол-во строк";

	cout << "Что дальше?" << endl;
	cin >> choice;
}

void out() {
	int sw, n;
	cout << "1-вывод 1 строки" << endl;
	cout << "2-вывод всех строк" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "Номер выводимой строки: " << endl;   cin >> n;  cout << endl;
		cout << "Фамилия:";
		cout << pupilss_of_school[n - 1].surname << endl;
		cout << "Имя:";
		cout << pupilss_of_school[n - 1].name << endl;
		cout << "Отчество:";
		cout << pupilss_of_school[n - 1].middleName << endl;
		cout << "Класс: " << endl;
		cout << l;
		cout << f;
		cout << "\n";
		cout << "Предметы и оценки:" << endl;
		Subjects::Math;
		cout << "Математка:";
		cout << markss[0];
		cout << "\n";
		Subjects::Biology;
		cout << "Биология:";
		cout << markss[1];
		cout << "\n";
		Subjects::History;
		cout << "История:";
		cout << markss[2];
		cout << "\n";
		Subjects::Chemistry;
		cout << "Химия:";
		cout << markss[3];
		cout << "\n";
		Subjects::Physics;
		cout << "Физика:";
		cout << markss[4];
		cout << "\n";
		Subjects::Englysh;
		cout << "Английский:";
		cout << markss[5];
		cout << "\n";
		Subjects::PE;
		cout << "Физкультура:";
		cout << markss[6];
		cout << "\n";
		Subjects::Geography;
		cout << "Ã=ГЕография:";
		cout << markss[7];
		cout << "\n";
		cout << "Средний балл:" << endl;
		cout << average << "\n";
	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "Фамилия:";
			cout << pupilss_of_school[i].surname << endl;
			cout << "Имя:";
			cout << pupilss_of_school[i].name << endl;
			cout << "Отчество:";
			cout << pupilss_of_school[i].middleName << endl;
			cout << "Класс: " << endl;
			cout << l;
			cout << f;
			cout << "\n";
			cout << "Предметы и оценки:" << endl;
			Subjects::Math;
			cout << "Математка:";
			cout << markss[0];
			cout << "\n";
			Subjects::Biology;
			cout << "Биология:";
			cout << markss[1];
			cout << "\n";
			Subjects::History;
			cout << "История:";
			cout << markss[2];
			cout << "\n";
			Subjects::Chemistry;
			cout << "Химия:";
			cout << markss[3];
			cout << "\n";
			Subjects::Physics;
			cout << "Физика:";
			cout << markss[4];
			cout << "\n";
			Subjects::Englysh;
			cout << "Английский:";
			cout << markss[5];
			cout << "\n";
			Subjects::PE;
			cout << "Физкультура:";
			cout << markss[6];
			cout << "\n";
			Subjects::Geography;
			cout << "Ã=ГЕография:";
			cout << markss[7];
			cout << "\n";
			cout << "Средний балл:" << endl;
			cout << average << "\n";
			cout << "_________________________________________________________________________________" << "\n";
		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}

void del() {
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;
	cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			pupilss_of_school[de1] = pupilss_of_school[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			pupilss_of_school[i] = all;
	cout << "Что дальше?" << endl;
	cin >> choice;
}

void search()
{
	char surname[16];
	cout << "Фамилия учащегося:" << "\n";
	cin >> surname;
	for (int z = 0; z < current_size; z++)
	{
		if (strcmp(surname, pupilss_of_school[z].surname) == 0)
		{
			cout << "Фамилия:";
			cout << pupilss_of_school[z].surname << endl;
			cout << "Имя:";
			cout << pupilss_of_school[z].name << endl;
			cout << "Отчество:";
			cout << pupilss_of_school[z].middleName << endl;
			cout << "Класс: " << endl;
			cout << l;
			cout << f;
			cout << "\n";
			cout << "Предметы и оценки:" << endl;
			Subjects::Math;
			cout << "Математка:";
			cout << markss[0];
			cout << "\n";
			Subjects::Biology;
			cout << "Биология:";
			cout << markss[1];
			cout << "\n";
			Subjects::History;
			cout << "История:";
			cout << markss[2];
			cout << "\n";
			Subjects::Chemistry;
			cout << "Химия:";
			cout << markss[3];
			cout << "\n";
			Subjects::Physics;
			cout << "Физика:";
			cout << markss[4];
			cout << "\n";
			Subjects::Englysh;
			cout << "Английский:";
			cout << markss[5];
			cout << "\n";
			Subjects::PE;
			cout << "Физкультура:";
			cout << markss[6];
			cout << "\n";
			Subjects::Geography;
			cout << "Ã=ГЕография:";
			cout << markss[7];
			cout << "\n";
			cout << "Средний балл:" << endl;
			cout << average << "\n";
		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}
*/