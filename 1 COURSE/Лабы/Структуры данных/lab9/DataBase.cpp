/*

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;


struct Sellers
{
	int IdS;
	string Name;
	string Phone;
	string Adress;
};

struct Details
{
	int IdD;
	string Articul;
	double Price;
	string NameD;
	int Id;
};

struct Orders
{
	int IdO;
	string Date;
	int Count;
	int IdD;
};

struct HistoryAmount
{
	int IdH;
	string DateOfChange;
	double NewPrice;
	double OldPrice;
	int IdD;
};

ifstream fin;
ofstream fout;

int _stateMenu;
int YoN;
int selch, detch, ordch, hisch;
int numsel, numdet, numord, numhis;

char delS[50];
char delD[50];
char delH[50];
char delO[50];

char getS[50];
char getD[50];
char getO[50];
char getH[50];

const int amS = 3;
const int amD = 7;
const int amO = 7;
const int amH = 2;

int nodt;

int CountA[amO] = {};

void MenuDop() {
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  1  | Лаба 4 Доп 1                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  2  | Лаба 4 Доп 2                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  3  | Лаба 4 Доп 3                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  4  | Лаба 6 Доп 1                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  5  | Лаба 8 Доп 1                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  6  | Лаба 8 Доп 2                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  7  | Лаба 8 Доп 3                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "\n";
	cout << "Ваш выбор: ";
	cin >> nodt;
	system("cls");
}

void Menu() {
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  1  | Поставщики:                            |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  2  | Детали:                                |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  3  | Заказы:                                |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  4  | История цен:                           |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "                 |  5  | Допы:                                  |\n";
	cout << "                 |-----|----------------------------------------|\n";
	cout << "\n";
	cout << "Ваш выбор: ";
	cin >> _stateMenu;
	system("cls");
}

void MenuSel() 
{
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  1  | Записать информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  2  | Получить информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  3  | Удалить информацию                 |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  4  | Удалить файл                       |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  5  | Выполнить поиск по ID              |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  6  | Изменить данные                    |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  7  | Выполнить фильтрацию               |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "\n";
	cout << "Ваш выбор: ";
	cin >> selch;
}
void MenuDet()
{
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  1  | Записать информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  2  | Получить информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  3  | Удалить информацию                 |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  4  | Удалить файл                       |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  5  | Выполнить поиск по ID              |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  6  | Изменить данные                    |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "\n";
	cout << "Ваш выбор: ";
	cin >> detch;
}
void MenuOrd()
{
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  1  | Записать информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  2  | Получить информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  3  | Удалить информацию                 |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  4  | Удалить файл                       |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  5  | Выполнить поиск по ID              |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  6  | Изменить данные                    |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  7  | Интерполирующий поиск              |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  8  | Бинарный поиск                     |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  9  | Выполнить сортировку               |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "\n";
	cout << "Ваш выбор: ";
	cin >> ordch;
}
void MenuHis()
{
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  1  | Записать информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  2  | Получить информацию                |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  3  | Удалить информацию                 |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  4  | Удалить файл                       |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  5  | Выполнить поиск по ID              |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  6  | Изменить данные                    |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "                 |  7  | Выполнить сортировку               |\n";
	cout << "                 |-----|------------------------------------|\n";
	cout << "\n";
	cout << "Ваш выбор: ";
	cin >> hisch;
}

void InfSel(Sellers* point) {
	system("cls"); // очистка консоли
	cout << "Введите название файла: \n";
	cin >> delS;
	fout.open(delS, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!";
	}
	else
	{
		for (int i = 0; i < amS; i++)
		{
			cout << "Введите имя " << i + 1 << "-ого поставщика " << endl;
			cin >> point[i].Name;
			fout << point[i].Name << "\n";
			cout << endl << "Адресс: ";
			cin >> point[i].Adress;
			fout << point[i].Adress << "\n";
			cout << endl << "Номер: ";
			cin >> point[i].Phone;
			fout << point[i].Phone << "\n";
			point[i].IdS = 1000 + ((i + 1) * 10);
		}
	}
	fout.close();
	cout << "Данные введены!" << endl;
	system("pause"); 
	system("cls");
}

void InfDet(Details* detal) {
	system("cls"); // очистка консоли
	cout << "Введите название файла: \n";
	cin >> delD;
	fout.open(delD, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!";
	}
	else
	{
		for (int i = 0; i < amD; i++)
		{
			cout << "Введите наименование " << i + 1 << "-ого товара " << endl;
			cin >> detal[i].NameD;
			fout << detal[i].NameD << "\n";
			cout << endl << "Артикуль (A-0): ";
			cin >> detal[i].Articul;
			fout << detal[i].Articul << "\n";
			cout << endl << "Цену в (0.00)$: ";
			cin >> detal[i].Price;
			fout << detal[i].Price << "\n";
			detal[i].IdD = 2000 + ((i + 1) * 10);
		}
	}
	fout.close();
	cout << "Данные введены!" << endl;
	system("pause");
	system("cls");
}

void InfOrd(Orders* order) {
	system("cls"); // очистка консоли
	cout << "Введите название файла: \n";
	cin >> delO;
	fout.open(delO, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!";
	}
	else
	{
		for (int i = 0; i < amO; i++)
		{
			cout << "Введите дату " << i + 1 << "-ого заказа " << endl;
			cin >> order[i].Date;
			fout << order[i].Date << "\n";
			cout << endl << "Количество товара: ";
			cin >> order[i].Count;
			CountA[i] = order[i].Count;
			fout << order[i].Count << "\n";
			order[i].IdO = 3000 + ((i + 1) * 10);
		}
	}
	fout.close();
	cout << "Данные введены!" << endl;
	system("pause");
	system("cls");
}

void InfHis(HistoryAmount* amount) {
	system("cls"); // очистка консоли
	cout << "Введите название файла: \n";
	cin >> delH;
	fout.open(delH, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!";
	}
	else
	{
		for (int i = 0; i < amH; i++)
		{
			cout << "Введите дату " << i + 1 << "-ого изменения цены: " << endl;
			cin >> amount[i].DateOfChange;
			fout << amount[i].DateOfChange << "\n";
			cout << endl << "Старая цена: ";
			cin >> amount[i].OldPrice;
			fout << amount[i].OldPrice << "\n";
			cout << endl <<"Новая цена: ";
			cin >> amount[i].NewPrice;
			fout << amount[i].NewPrice << "\n";
			amount[i].IdH = 4000 + ((i + 1) * 10);
		}
	}
	fout.close();
	cout << "Данные введены!" << endl;
	system("pause");
	system("cls");
}

void GetSel(Sellers* point) {
	ifstream fin;
	cout << "Введите название файла: \n";
	cout << "Вы записывали в " << delS << "\n";
	cin >> getS;
	fin.open(getS);
	if (!fin.is_open())
	{
		cout << "Ошибка открытия!";
	}
	else
	{
		char ch;
		while (fin.get(ch))
		{
			cout << ch;
		}
	}
}

void GetDet(Details* detal) {
	ifstream fin;
	cout << "Введите название файла: \n";
	cout << "Вы записывали в " << delD << "\n";
	cin >> getD;
	fin.open(getD);
	if (!fin.is_open())
	{
		cout << "Ошибка открытия!";
	}
	else
	{
		char ch;
		while (fin.get(ch))
		{
			cout << ch;
		}
	}
}

void GetOrd(Orders* order) {
	ifstream fin;
	cout << "Введите название файла: \n";
	cout << "Вы записывали в " << delO << "\n";
	cin >> getO;
	fin.open(getO);
	if (!fin.is_open())
	{
		cout << "Ошибка открытия!";
	}
	else
	{
		char ch;
		while (fin.get(ch))
		{
			cout << ch;
		}
	}
}

void GetHis(HistoryAmount* amount) {
	ifstream fin;
	cout << "Введите название файла: \n";
	cout << "Вы записывали в " << delH << "\n";
	cin >> getH;
	fin.open(getH);
	if (!fin.is_open())
	{
		cout << "Ошибка открытия!";
	}
	else
	{
		char ch;
		while (fin.get(ch))
		{
			cout << ch;
		}
	}
}

void DelSel(Sellers* point) {
	ofstream fout(delS, ios_base::trunc);
	fout.close();
}

void DelDet(Details* detal) {
	ofstream fout(delD, ios_base::trunc);
	fout.close();
}

void DelOrd(Orders* order) {
	ofstream fout(delO, ios_base::trunc);
	fout.close();
}

void DelHis(HistoryAmount* amount) {
	ofstream fout(delH, ios_base::trunc);
	fout.close();
}

void DelFileS() {
	remove(delS);
		cout << "Файл успешно удалён!\n";
}
void DelFileD() {
	remove(delD);
		cout << "Файл успешно удалён!\n";
}
void DelFileO() {
	remove(delO);
		cout << "Файл успешно удалён!\n";
}
void DelFileH() {
	remove(delH);
		cout << "Файл успешно удалён!\n";
}

void SearchS(Sellers* point)
{
	int dot;
	cout << "Введите номер продавца: \n";
	cin >> dot;
	for (int i = 0; i < amS; i++)
	{
		if ((dot * 10) + 1000 == point[i].IdS)
		{
			cout << "Имя поставщика: " << point[i].Name << "\n";
			cout << "Адрес поставщика: " << point[i].Adress << "\n";
			cout << "Телефон поставщика: " << point[i].Phone << "\n";
		}
	}
}

void SearchD(Details* detal)
{
	int dot;
	cout << "Введите номер детали: \n";
	cin >> dot;
	for (int i = 0; i < amD; i++)
	{
		if ((dot * 10) + 2000 == detal[i].IdD)
		{
			cout << "Название детали: " << detal[i].NameD << "\n";
			cout << "Артикуль: " << detal[i].Articul << "\n";
			cout << "Цена: " << detal[i].Price << "\n";
		}
	}
}

void SearchO(Orders* order)
{
	int dot;
	cout << "Введите номер заказа: \n";
	cin >> dot;
	for (int i = 0; i < amO; i++)
	{
		if ((dot * 10) + 3000 == order[i].IdO)
		{
			cout << "Дата заказа: " << order[i].Date << "\n";
			cout << "Количество: " << order[i].Count << "\n";
		}
	}
}

void SearchH(HistoryAmount* amount)
{
	int dot;
	cout << "Введите номер иззменения цены: \n";
	cin >> dot;
	for (int i = 0; i < amH; i++)
	{
		if ((dot * 10) + 4000 == amount[i].IdH)
		{
			cout << "Дата изменения: " << amount[i].DateOfChange << "\n";
			cout << "Старая цена: " << amount[i].OldPrice << "\n";
			cout << "новая цена: " << amount[i].NewPrice << "\n";
		}
	}
}



void WWR() {
	string str;
	ofstream ffout("f1.txt");
	ofstream sfout("f2.txt");
	ffout << "Work with files C++" << "\n";
	ffout << "Work with files C++" << "\n";
	ffout << "Not work with files C++" << "\n";
	ffout.close();
	ifstream ffin("f1.txt");
	ifstream sfin("f2.txt");
	if (!ffin.is_open())
		cout << "Ошибка открытия файла!\n";
	else
	{
		while (getline(ffin, str))
		{
			if (str[0] == 'W' && str[1] == 'o' && str[2] == 'r' && str[3] == 'k')
			{
				sfout << str << "\n";
			}
		}
		cout << "Данные успешено скопированы!";
		ffin.close();
		sfin.close();
		ffout.close();
		sfout.close();
	}
}

void OSI() {
	int k, num = 0, counter = 0;
		string TTTR;
		ifstream file1("file2_1_1.txt");
		ofstream file2("file2_1_2.txt");
		while (getline(file1, TTTR))
		{
			if(TTTR[0] == 'a' || TTTR[0] == 'A')
			{
				file2 << TTTR << '\n';
			}
		}
}

void KIR() {
	int n, k, num = 0, counter = 0;
		cout << "Введите, с какой строки копировать:\n";
		cin >> n;
		cout << "Введите, до какой строки копировать:\n";
		cin >> k;
		string str1;
		ifstream file11("file6_1_1.txt");
		ofstream file21("file6_1_2.txt");
		k--;
		n--;
		while (getline(file11, str1))
		{
			if (num >= n && num <= k)
			{
				file21 << str1 << '\n';
				for (int j = 0; j < 8; j++)
				{
					if (str1[j] == 'q' || str1[j] == 'w' || str1[j] == 'r' || str1[j] == 't' || str1[j] == 'p' || str1[j] == 's' || str1[j] == 'd' || str1[j] == 'f' ||
						str1[j] == 'g' || str1[j] == 'h' || str1[j] == 'j' || str1[j] == 'k' || str1[j] == 'l' || str1[j] == 'z' || str1[j] == 'x' || str1[j] == 'c' ||
						str1[j] == 'v' || str1[j] == 'b' || str1[j] == 'n' || str1[j] == 'm')
						counter++;
				}
			}
			num++;
		}
		cout << counter << " согласных букв.\n";
}

void reFillS(Sellers* point) {
	int number;
	cout << "Введите номер: \n";
		cin >> number;
	cout << "Введите имя поставщика: " << endl;
	cin >> point[number - 1].Name;
	cout << endl << "Адресс: ";
	cin >> point[number - 1].Adress;
	cout << endl << "Номер: ";
	cin >> point[number - 1].Phone;
}

void reFillD(Details* detal) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите наименование товара: " << endl;
	cin >> detal[number - 1].NameD;
	cout << endl << "Артикуль (A-0): ";
	cin >> detal[number - 1].Articul;
	cout << endl << "Цену в (0.00)$: ";
	cin >> detal[number - 1].Price;
}

void reFillO(Orders* order) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите дату заказа: " << endl;
	cin >> order[number - 1].Date;
	cout << endl << "Количество товара: ";
	cin >> order[number - 1].Count;
}

void reFillH(HistoryAmount* amount) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите дату изменения цены: " << endl;
	cin >> amount[number - 1].DateOfChange;
	cout << endl << "Старая цена: ";
	cin >> amount[number - 1].OldPrice;
	cout << endl << "Новая цена: ";
	cin >> amount[number - 1].NewPrice;
}

void delsS(Sellers* point) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите имя поставщика: " << endl;
	point[number - 1].Name = " ";
	cout << endl << "Адресс: ";
	point[number - 1].Adress = " ";
	cout << endl << "Номер: ";
	point[number - 1].Phone = " ";
}

void delsD(Details* detal) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите наименование товара: " << endl;
	detal[number - 1].NameD = " ";
	cout << endl << "Артикуль (A-0): ";
	detal[number - 1].Articul = " ";
	cout << endl << "Цену в (0.00)$: ";
	detal[number - 1].Price = NULL;
}

void delsO(Orders* order) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите дату заказа: " << endl;
	order[number - 1].Date = " ";
	cout << endl << "Количество товара: ";
	order[number - 1].Count = NULL;
}

void delsH(HistoryAmount* amount) {
	int number;
	cout << "Введите номер: \n";
	cin >> number;
	cout << "Введите дату изменения цены: " << endl;
	amount[number - 1].DateOfChange = "";
	cout << endl << "Старая цена: ";
	amount[number - 1].OldPrice = NULL;
	cout << endl << "Новая цена: ";
	amount[number - 1].NewPrice = NULL;
}

void sortH (HistoryAmount* amount) {
	int tapChoice;
	cout << "По какому критерию производить сортировку: " << "\n";
	cout << "1. Старая цена" << "\n";
	cout << "2. Новая цена" << "\n";
	cin >> tapChoice;
	if (tapChoice == 1)
	{
		for (int i = 0; i < amH; i++) {
			for (int j = i + 1; j < amH; j++) {
				if (amount[i].OldPrice > amount[j].OldPrice) {
					swap(amount[i], amount[j]);
				}
			}
		}
	}
	else 
	{
		for (int i = 0; i < amH; i++) {
			for (int j = i + 1; j < amH; j++) {
				if (amount[i].NewPrice > amount[j].NewPrice) {
					swap(amount[i], amount[j]);
				}
			}
		}
	}
	for (int k = 0; k < amH; k++)
	{
		cout << amount[k].DateOfChange << "\n";
		cout << amount[k].OldPrice << "\n";
		cout << amount[k].NewPrice << "\n";
	}
}

void dop1(Details* detal)
{
	for (int i = 0; i + 1 < amD; i++) {
		for (int j = 0; j + 1 < amD - i; j++) {
			if (detal[j + 1].Price < detal[j].Price) {
				swap(detal[j], detal[j + 1]);
			}
		}
	}
	for (int k = 0; k < amD; k++)
	{
		detal[k].Price;
	}
}

void dop2(Details* detal) {
	int key = 0;
	int i = 0;
	for (int j = 1; j < amD; j++) {
		key = detal[j].Price;
		i = j - 1;
		while (i >= 0 && detal[i].Price > key) {
			detal[i + 1] = detal[i];
			i = i - 1;
			detal[i + 1].Price = key;
		}
	}
	for (int k = 0; k < amD; k++)
	{
		detal[k].Price;
	}
}

void dop3(Details* detal) {
	int smallest_id;

	for (int i = 0; i < amD; i++) {
		smallest_id = i;
		for (int j = i + 1; j < amD; j++) {
			if (detal[j].Price < detal[smallest_id].Price)
				smallest_id = j;
		}
		//меняем местами элементы
		swap(detal[smallest_id], detal[i]);
	}
}

void dop4_1(HistoryAmount* amount)
{
	string doc;
	cout << "Введите номер иззменения цены: \n";
	cin >> doc;
	for (int i = 0; i < amH; i++)
	{
		if ((doc == amount[i].DateOfChange))
		{
			cout << "Старая цена: " << amount[i].OldPrice << "\n";
			cout << "новая цена: " << amount[i].NewPrice << "\n";
		}
	}
}

void dop4_2(HistoryAmount* amount)
{
	int doc;
	cout << "Введите старую цену: \n";
	cin >> doc;
	for (int i = 0; i < amH; i++)
	{
		if ((doc == amount[i].OldPrice))
		{
			cout << "новая цена: " << amount[i].NewPrice << "\n";
			cout << "Дата изменения цены: " << amount[i].DateOfChange << "\n";
		}
	}
}

void dop4_3(HistoryAmount* amount)
{
	int doc;
	cout << "Введите новую цену: \n";
	cin >> doc;
	for (int i = 0; i < amH; i++)
	{
		if ((doc == amount[i].NewPrice))
		{
			cout << "Старая цена: " << amount[i].OldPrice << "\n";
			cout << "Дата изменения цены: " << amount[i].DateOfChange << "\n";
		}
	}
}

void dop6_1(HistoryAmount* amount)
{
	int dot, sod;
	cout << "Введите номер изменения цены: \n";
	cin >> dot;
	for (int i = 0; i < amH; i++)
	{
		if ((dot * 10) + 4000 == amount[i].IdH)
		{
			cout << "| Какие данные удалить? |\m";
			cout << "| 1. Дата изменения     |\n";
			cout << "| 2. Старая цена        |\n";
			cout << "| 3. Новая цена         |\n";
			cin >> sod;
			if (sod == 1)
				amount[i].DateOfChange = "";
			else if (sod == 2)
				amount[i].OldPrice = NULL;
			else if (sod == 3)
				amount[i].NewPrice = NULL;
			else "Неверное значение!";
		}
	}
}

void dop6_2(Details *detal)
{
	int dot, sod;
	cout << "Введите номер детали: \n";
	cin >> dot;
	for (int i = 0; i < amD; i++)
	{
		if ((dot * 10) + 2000 == detal[i].IdD)
		{
			cout << "| Какие данные удалить? |\m";
			cout << "| 1. Артикуль           |\n";
			cout << "| 2. Название детали    |\n";
			cout << "| 3. Цена               |\n";
			cin >> sod;
			if (sod == 1)
				detal[i].Articul = "";
			else if (sod == 2)
				detal[i].NameD = "";
			else if (sod == 3)
				detal[i].Price = NULL;
			else "Неверное значение!";
		}
	}
}

void dop6_3(Sellers *point)
{
	int dot, sod;
	cout << "Введите номер поставщика: \n";
	cin >> dot;
	for (int i = 0; i < amS; i++)
	{
		if ((dot * 10) + 1000 == point[i].IdS)
		{
			cout << "| Какие данные удалить? |\m";
			cout << "| 1. Имя                |\n";
			cout << "| 2. Адрес              |\n";
			cout << "| 3. Телефон            |\n";
			cin >> sod;
			if (sod == 1)
				point[i].Name = "";
			else if (sod == 2)
				point[i].Adress = "";
			else if (sod == 3)
				point[i].Phone = "";
			else "Неверное значение!";
		}
	}
}

void findH(Sellers *point) {
	int i = 0;
	string tos;
	cout << "Введите имя для поиска: \n";
	cin >> tos;
	for (int p = 0; p < amS; p++)
	{
		for (i = point[p].Name.find(tos, i++); i != string::npos; i = point[p].Name.find(tos, i + 1))
		{
			cout << i << "\n";
		}
	}
}

void dop8_1(Sellers *point) {
	string tos;
	cout << "Введите имя для поиска: \n";
	cin >> tos;
	for (int i = 0; i < amS; i++)
	{
		size_t pos = point[i].Name.find(tos);
		if (pos != string::npos) {
			cout << "Найден на позиции " << pos << ", строки " << i + 1 << "\n";
		}
		else
			cout << "Не найдено\n";
	}
}

void dop8_2(Sellers* point) {
	string tos;
	cout << "Введите код страны для поиска: \n";
	cin >> tos;
	for (int i = 0; i < amS; i++)
	{
		size_t pos = point[i].Phone.find(tos);
		if (pos != string::npos) {
			cout << "Найден на позиции " << pos << ", строки " << i + 1 << "\n";
		}
		else
			cout << "Не найдено\n";
	}
}

void dop8_3(Sellers* point) {
	string tos;
	cout << "Введите название страны для поиска: \n";
	cin >> tos;
	for (int i = 0; i < amS; i++)
	{
		size_t pos = point[i].Adress.find(tos);
		if (pos != string::npos) {
			cout << "Найден на позиции " << pos << ", строки " << i + 1 << "\n";
		}
		else
			cout << "Не найдено\n";
	}
}

void search_int() {

	int x = 0; 
	int a = 0;
	int b = amO - 1; 

	int WhatFind ;
	cout << "Введите число для поиска:\n";
	cin >> WhatFind;
	bool found; 

	for (found = false; (CountA[a] < WhatFind) && (CountA[b] > WhatFind) && !found; )
	{

		x = a + ((WhatFind - CountA[a]) * (b - a)) / (CountA[b] - CountA[a]);
		
		if (CountA[x] < WhatFind)
			a = x + 1;
		else if (CountA[x] > WhatFind)
			b = x - 1;
		else
			found = true;
	}

	if (CountA[a] == WhatFind)
		cout << WhatFind << " элемент найден в позиции " << a + 1 << endl;
	else if (CountA[b] == WhatFind)
		cout << WhatFind << " элемент найден в позиции " << b + 1 << endl;
	else
		cout << "Sorry. Not found" << endl;
}

int binary() {
	int key; 

	sort(CountA, CountA + amO); 

	cout << endl << "Введите ключ:\n";

	cin >> key; 

	bool flag = false;
	int l = 0;
	int r = amO - 1; 
	int mid;

	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2; 

		if (CountA[mid] == key) flag = true;
		if (CountA[mid] > key) r = mid - 1; 
		else l = mid + 1;
	}

	if (flag) cout << "Индекс элемента " << key << " в массиве равен: " << mid << "\n";
	else cout << "Извините, но такого элемента в массиве нет\n";
	return 0;
}

void sortOrd(Orders *order) {
	int smallest_id;

	for (int i = 0; i < amD; i++) {
		smallest_id = i;
		for (int j = i + 1; j < amD; j++) {
			if (CountA[j] < CountA[smallest_id])
				smallest_id = j;
		}
		//меняем местами элементы
		swap(CountA[smallest_id], CountA[i]);
		swap(order[smallest_id], order[i]);
	}
	cout << "Данные отсортированы!\n";
	for (int i = 0; i < amO; i++)
	{
		cout << CountA[i] << "\n";
	}
}

void searchErat() {
	// Решето Эратосфена 

	//Проводим главный цикл. - Начало работы решета
	for (int i = 2; i * i <= amO; i++)
	{
		if (CountA[i])
			//Если текущее число не равно 0 - начинаем от него искать сложные
			for (int j = i * i; j <= amO; j += i)
		
				CountA[j] = 0;
	}

	for (int i = 2; i < amO; i++)
	{
		if (CountA[i])
		{
			cout << CountA[i] << ' ';
		}
	}

	cout << endl << endl;
	delete[] CountA; //И освобождаем массив
}

void searchString() {
	int k, num = 0, counter = 0;
	string TTTR;
	ifstream file1("file1.txt");
	ofstream file2("file2.txt");
	while (getline(file1, TTTR))
	{
		if (TTTR[0] == 'a' || TTTR[0] == 'A')
		{
			file2 << TTTR << '\n';
		}
	}
}

void gnomesort(int* l, int* r) {
	int* i = l;
	while (i < r) {
		if (i == l || *(i - 1) <= *i) i++;
		else swap(*(i - 1), *i), i--;
	}
}

void treesort(int* l, int* r) {
	multiset<int> m;
	for (int* i = l; i < r; i++)
		m.insert(*i);
	for (int q : m)
		*l = q, l++;
}

void MSDsort(int* l, int* r) {
	for (int* i = l; i < r; i++) {
		int minz = *i, * ind = i;
		for (int* j = i + 1; j < r; j++) {
			if (*j < minz) minz = *j, ind = j;
		}
		swap(*i, *ind);
	}
}

//void sorts() {
//	gnomesort(3, 4);
//}

int main()
{
	setlocale(LC_CTYPE, "RU");
	Sellers* point = new Sellers[3];
	Details* detal = new Details[5];
	Orders* order = new Orders[7];
	HistoryAmount* amount = new HistoryAmount[2];

	Menu();
	system("cls");
	while (_stateMenu != 0) {

		switch (_stateMenu)
		{
		case 1:
			MenuSel();
			system("cls");
			switch (selch)
			{
			case 1:
				system("cls");
				InfSel(point);
				system("pause");
				system("cls");
				break;
			case 2:
				system("cls");
				GetSel(point);
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				DelSel(point);
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				DelFileS();
				system("pause");
				system("cls");
				break;
			case 5:
				system("cls");
				SearchS(point);
				system("pause");
				system("cls");
				break;
			case 6:
				system("cls");
				reFillS(point);
				system("pause");
				system("cls");
				break;
			case 7:
				system("cls");
				findH(point);
				system("pause");
				system("cls");
				break;
			default:
				system("cls");
				Menu();
				break;
			}
			Menu();
			break;
		case 2:
			MenuDet();
			system("cls");
			switch (detch)
			{
			case 1:
				system("cls");
				InfDet(detal);
				system("pause");
				system("cls");
				break;
			case 2:
				system("cls");
				GetDet(detal);
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				DelDet(detal);
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				DelFileD();
				system("pause");
				system("cls");
				break;
			case 5:
				system("cls");
				SearchD(detal);
				system("pause");
				system("cls");
				break;
			case 6:
				system("cls");
				reFillD(detal);
				system("pause");
				system("cls");
				break;
			case 7:
				system("cls");
				int sortChoice;
				cout << "Методы сортировки:" << "\n";
				cout << "1. Пузырьком" << "\n";
				cout << "2. Вставками" << "\n";
				cout << "3. Выбором" << "\n";
				cin >> sortChoice;
				if (sortChoice == 1)
				{
					dop1(detal);
				}
				else if (sortChoice == 2)
				{
					dop2(detal);
				}
				else 
				{
					dop3(detal);
				}
				system("pause");
				system("cls");
				break;
			default:
				system("cls");
				Menu();
				break;
			}
			Menu();
			break;
		case 3:
			MenuOrd();
			system("cls");
			switch (ordch)
			{
			case 1:
				system("cls");
				InfOrd(order);
				system("pause");
				system("cls");
				break;
			case 2:
				system("cls");
				GetOrd(order);
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				DelOrd(order);
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				DelFileO();
				system("pause");
				system("cls");
				break;
			case 5:
				system("cls");
				SearchO(order);
				system("pause");
				system("cls");
				break;
			case 6:
				system("cls");
				reFillO(order);
				system("pause");
				system("cls");
				break;
			case 7:
				system("cls");
				search_int();
				system("pause");
				system("cls");
				break;
			case 8:
				system("cls");
				binary();
				system("pause");
				system("cls");
				break;
			case 9:
				system("cls");
				sortOrd(order);
				system("pause");
				system("cls");
				break;
			default:
				system("cls");
				Menu();
				break;
			}
			Menu();
			break;
		case 4:
			MenuHis();
			system("cls");
			switch (hisch)
			{
			case 1:
				system("cls");
				InfHis(amount);
				system("pause");
				system("cls");
				break;
			case 2:
				system("cls");
				GetHis(amount);
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				DelHis(amount);
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				DelFileH();
				system("pause");
				system("cls");
				break;
			case 5:
				system("cls");
				SearchH(amount);
				system("pause");
				system("cls");
				break;
			case 6:
				system("cls");
				reFillH(amount);
				system("pause");
				system("cls");
				break;
			case 7: 
				system("cls");
				sortH(amount);
				system("pause");
				system("cls");
				break;
			case 8:
				system("cls");
				delsH(amount);
				system("pause");
				system("cls");
				break;
			default:
				system("cls");
				Menu();
				break;
			}
			Menu();
			break;
			break;
		case 5:
			MenuDop();
			system("cls");
			switch (nodt)
			{
			case 1:
				system("cls");
				dop4_1(amount);
				system("pause");
				system("cls");
				break;
			case 2:
				system("cls");
				dop4_2(amount);
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				dop4_3(amount);
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				dop6_1(amount);
				system("pause");
				system("cls");
				break;
			case 5:
				system("cls");
				dop6_2(detal);
				system("pause");
				system("cls");
				break;
			case 6:
				system("cls");
				dop6_3(point);
				system("pause");
				system("cls");
				break;
			case 7:
				system("cls");
				dop8_1(point);
				system("pause");
				system("cls");
				break;
			case 8:
				system("cls");
				dop8_2(point);
				system("pause");
				system("cls");
				break;
			case 9:
				system("cls");
				dop8_3(point);
				system("pause");
				system("cls");
				break;
			case 10: 
				system("cls");
				searchString();
				system("pause");
				system("cls");
				break;
			case 11:
				system("cls");
				//gnomesort();
				system("pause");
				system("cls");
				break;
			case 12:
				system("cls");
				//treesort();
				system("pause");
				system("cls");
				break;
			case 13:
				system("cls");
				//MSDsort();
				system("pause");
				system("cls");
				break;
			default:
				break;
			}
		default:
			system("cls");
			system("pause");
			system("cls");
			Menu();
			break;
		}
	}
}
*/