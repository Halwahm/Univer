
/*
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const short N = 10;
#define size 2

struct client
{
	char* name = new char[20];
	char* address = new char[20];
	char* phone = new char[20];
	char* check = new char[20];
	char* person = new char[20];
};

struct rent
{
	char* floor = new char[20];
	char* area = new char[20];
	char* conditioner = new char[4];
	char* price = new char[20];
};

struct treaty
{
	string name_place;
	string name_client;
	string renral_period; //период аренды
};

struct client a[size];
FILE* fin; FILE* second; FILE* third;
int csize = 0;
short choice;
char fnme[15];

void reg(char fnme[]);
void output(FILE* f, char fname[]);
void del(char fname[]);
void removefrom(FILE* f2, char fname[]);
void izmenenie(FILE* f3, char fnme[]);

void Menu()
{
	cout << endl << "Введите желаемую операцию: " << endl;
	cout << "0 - новый файл" << endl;
	cout << "1 - ввод информации об аренде торговых точек" << endl;
	cout << "2 - вывод из файла информации о торговых точках" << endl;
	cout << "3 - вывод информации об аренде торговых точек" << endl;
	cout << "4 - удаление информации об аренде торговых точек" << endl; //dop1
	cout << "5 - ввод информации о клиентах" << endl;
	cout << "6 - вывод инормации о клиенте" << endl;
	cout << "7 - вывод информации о клиенте из файла" << endl;
	cout << "8 - оформить договор по аренде" << endl;
	cout << "9 - выход из программы" << endl;
	cout << "10 - dop1" << endl;
}

void Menu1() {
	cout << endl << "Выберите действие:" << endl
		<< "(1) Ввод данных о клиентах" << endl
		<< "(2) Вывод клиентов" << endl
		<< "(3) Удаление записи из файла" << endl
		<< "(4) Удаление файла " << endl
		<< "(5) Изменение записи" << endl
		<< "(0) Выход в главное меню" << endl
		<< "Ваш выбор: ";
	cout << endl;
}

void file()
{
	cout << "Введите название файла для записи" << endl;
	cin >> fnme;

	Menu1();

	cin >> choice;
	while (choice != 0) {
		switch (choice) {
		case 1:
			system("cls");

			reg(fnme);
			cout << "Данные введены!" << endl;
			Menu1();
			cin >> choice;
			break;

		case 2:
			system("cls");
			output(fin, fnme);
			Menu1();
			cin >> choice;
			break;

		case 3:
			system("cls");
			removefrom(second, fnme);
			Menu1();
			cin >> choice;
			break;

		case 4:
			del(fnme);
			cout << "Файл удалён!" << endl;
			Menu1();
			cin >> choice;
			break;
		case 5:
			system("cls");
			izmenenie(third, fnme);
			Menu1();
			cin >> choice;
			break;

		default:
			Menu();
			break;
		}
	}
}

void reg(char fname[]) {
	int index = 0;
	ofstream fout(fname);
	for (csize; csize < size; csize++) {
		cout << "\nДанные " << csize + 1 << " клиента:" << endl;
		cout << "Имя\n";
		cin >> a[csize].name;
		cout << "\n\n";
		cout << "\nАдрес\n";
		cin >> a[csize].address;
		cout << "\nТелефон\n";
		cin >> a[csize].phone;
		cout << "\nРеквизиты\n";
		cin >> a[csize].person;
		fout << a[csize].name << ' ' << a[csize].address << ' ' << a[csize].phone << ' ' << a[csize].person << '.' << '\n';
	}
	if (csize == size)
		cout << endl << "Введено максимальное количество строк" << endl;
	fout.close();
}

void output(FILE* f, char fname[]) {
	cout << endl << "(1) Вывод данных из файла" << endl << "(2) Вывод по индексу" << endl;
	int choice0;
	cin >> choice0;
	if (choice0 == 1) {
		char s[100] = "";
		int o = 0;
		fopen_s(&f, fname, "r");
		while (o < csize) {
			cout << "Запись №" << o + 1 << endl;
			fgets(s, 100, f);
			cout << s;
			o++;
		}
		fclose(f);
	}
	else if (choice0 == 2) {
		bool y = false;
		cout << endl << "Введите индекс" << endl;
		int seind;
		cin >> seind;
		if (seind != 1 && seind != 2)
			cout << endl << "Некорректный ввод" << endl;
		for (int p = 0; p < csize; p++) {
			if ((seind - 1) == p) {
				cout << endl << "Запись №" << p + 1 << endl;
				y = true;
				cout << a[p].name << ' ' << a[p].address << ' ' << a[p].phone << ' ' << a[p].person << '.' << '\n';
			}
		}
		if (y == false) {
			cout << endl << "Запись не найдeна" << endl;
		}

	}
}

void removefrom(FILE* f2, char fname[]) {
	int icheck = 0;
	ofstream fout1("temporary file.txt");
	bool y = false;
	cout << endl << "Введите индекс для удаления записи" << endl;
	cin >> icheck;
	for (int p = 0; p < csize; p++) {
		if ((icheck - 1) != p) {
			fout1 << a[p].name << ' ' << a[p].address << ' ' << a[p].phone << ' ' << a[p].person << '.' << '\n';
		}
		else {
			for (int d = p; d < size; d++) {
				a[d] = a[p + 1];
				y = true;
			}
		}
	}
	if (y == true) {
		cout << endl << "Запись удалена" << endl;
		csize--;
	}
	else {
		cout << endl << "Запись не найдена" << endl;
	}
	remove(fname);
	fout1.close();
	rename("temporary file.txt", fname);
}

void del(char fname[]) {
	remove(fname);
	cout << endl << "Файл удалён";
	return;
}

void izmenenie(FILE* F3, char fnme[]) {
	int num;
	ofstream fout3("sasasaaa.txt");
	cout << "Введите номер записи для изменения\n";
	cin >> num;
	if (num > csize || num < 1) {
		cout << "Неверный номер записи\n";
		system("cls");
		return;
	}
	else {
		cout << "\nДанные " << num << "-ого клиента:" << endl;
		cout << "\nИмя\n";
		cin >> a[num - 1].name;
		cout << "\nАдрес\n";
		cin >> a[num - 1].address;
		cout << "\nТелефон\n";
		cin >> a[num - 1].phone;
		cout << "\nРеквизиты\n";
		cin >> a[num - 1].person;
	}
	for (short i = 0; i < csize; i++) {
		fout3 << a[i].name << ' ' << a[i].address << ' ' << a[i].phone << ' ' << a[i].person << '.' << '\n';
	}
	remove(fnme);
	fout3.close();
	rename("sasasaaa.txt", fnme);
	cout << endl << "Запись изменена \n";
}

void place_entry(rent point[])
{
	short num;
	cout << "Количество торговых точек: ";
	cin >> num;
	ofstream file1("information1.txt");

	for (short i = 0; i < num; i++)
	{
		cout << "\tТочка №" << i + 1 << endl;
		file1 << "\tТочка №" << i + 1 << endl;
		cout << "Введите этаж точки:\n";
		file1 << "\nЭтаж точки: ";
		cin >> point[i].floor;
		file1 << point[i].floor;
		cout << "Введите площадь:\n";
		file1 << "\nПлощадь: ";
		cin >> point[i].area;
		file1 << point[i].area;
		cout << "Введите наличие кондиционера:\n";
		file1 << "\nКондиционер: ";
		cin >> point[i].conditioner;
		file1 << point[i].conditioner;
		cout << "Введите стоимость аренды:\n";
		file1 << "\nСтоимость аренлы: ";
		cin >> point[i].price;
		file1 << point[i].price;
	}
	cout << "Информация записана в information1.txt" << endl;
}

void output_place(rent point[])
{
	short place_num;
	cout << "Введите номер точки, информацию о которой требуется вывести" << endl;
	cin >> place_num;
	short i = place_num - 1;
	cout << "\tТочка №" << place_num << '\n';
	cout << "Этаж точки: " << point[i].floor << '\n';
	cout << "Площадь: " << point[i].area << '\n';
	cout << "Наличие кондиционера: " << point[i].conditioner << '\n';
	cout << "Cтоимость: " << point[i].price << "\n\n\n";
}

void output_place_file(rent point[])
{
	string strInf;
	ifstream file1("information1.txt");
	while (file1)
	{
		getline(file1, strInf);
		cout << strInf << '\n';
	}
	cout << endl;
}

void delete_place(rent point[])
{
	ofstream file("information1.txt", ios_base::trunc);
}

void client_entry(client client[])
{
	short num;
	cout << "Введите количество клиентов: ";
	cin >> num;
	ofstream file2("information2.txt");
	for (short i = 0; i < num; i++)
	{
		cout << "\tКлинт №" << i + 1 << endl;
		file2 << "\tКлиент №" << i + 1 << endl;
		cout << "Введите имя клиента:\n";
		file2 << "\nИмя клиента: ";
		cin >> client[i].name;
		file2 << client[i].name;
		cout << "Введите адрес клиента:\n";
		file2 << "\nАдрес клиента: ";
		cin >> client[i].address;
		file2 << client[i].address;
		cout << "Введите телефон клинта:\n";
		file2 << "\nТелефон клиента: ";
		cin >> client[i].phone;
		file2 << client[i].phone;
		cout << "Введите реквизиты:\n";
		file2 << "\nРеквизиты: ";
		cin >> client[i].person;
		file2 << client[i].person;
		cout << "Введите контактное лицо:\n";
		file2 << "\nКонтактное лицо: ";
		cin >> client[i].check;
		file2 << client[i].check;
		cout << endl;
	}
}

void client_output_file(client client[])
{
	string strInf;
	ifstream file2("information2.txt");
	while (file2)
	{
		getline(file2, strInf);
		cout << strInf << '\n';
	}
	cout << endl;
}

void client_output(client client[])
{
	cout << "Введите номер клиента, информацию о котором хотите вывести: ";
	short num;
	cin >> num;
	short i = num - 1;
	cout << "Точка № " << num << endl;
	cout << "Название точки: " << client[i].name << endl;
	cout << "Адрес клиента: " << client[i].address << endl;
	cout << "Телефон клиента: " << client[i].phone << endl;
	cout << "Реквизиты: " << client[i].person << endl;
	cout << "Контактное лицо: " << client[i].check << endl;
}

void treaty_place(treaty treaty_n[])
{
	cout << "Введите точку: ";
	short i;
	cin >> i;
	ofstream file5("information5.txt");

	cout << "\tТочка №" << i << '\n';
	file5 << "\tТочка №" << i << '\n';
	cout << "Введите название точки:\n";
	file5 << "\nНазвание точки: ";
	cin >> treaty_n[i].name_place;
	file5 << treaty_n[i].name_place;
	cout << "Введите имя клиента:\n";
	file5 << "\nИмя клиента: ";
	cin >> treaty_n[i].name_client;
	file5 << treaty_n[i].name_client;
	cout << "Введите период аренды:\n";
	file5 << "\nПериод аренды: ";
	cin >> treaty_n[i].renral_period;
	file5 << treaty_n[i].renral_period << "\n\n";

	cout << endl;
}

void dop1(rent point[]) 
{
	int smallest_id;

	for (int i = 0; i < N; i++) {
		smallest_id = i;
		for (int j = i + 1; j < N; j++) {
			if (point[j].price < point[smallest_id].price)
				smallest_id = j;
		}
		swap(point[smallest_id], point[i]);

		cout << "Цена по убыванию";
		cout << ' ' << point[i].price << ' ' << endl;
	}
}


int main()
{
	setlocale(LC_CTYPE, "Russian");
	rent point[N];
	client client[N];
	treaty treaty_n[N];

	short choose;
	cout << endl;

	Menu();
	do {
		cin >> choose;
		switch (choose)
		{
		case 0: file(); Menu(); break;
		case 1: place_entry(point); Menu(); break;
		case 2: output_place_file(point); Menu(); break;
		case 3: output_place(point); Menu(); break;
		case 4: delete_place(point); Menu(); break;
		case 5: client_entry(client); Menu(); break;
		case 6: client_output(client); Menu(); break;
		case 7: client_output_file(client); Menu(); break;
		case 8: treaty_place(treaty_n); Menu(); break;
		case 9: cout << endl << "До свидания!" << endl; break;
		case 10: dop1(point); Menu(); break;

		}
	} while (choose != 9);
}
*/
