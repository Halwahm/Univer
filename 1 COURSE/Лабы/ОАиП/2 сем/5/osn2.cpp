/*#include <iostream>  
#include<fstream>

# define size 100  

using namespace std;

void enter_new();
void out();
void search();

//Ломбард. База хранимых товаров и недвижимости: анкетные данные клиента, наименование товара, 
//оценочная стоимость; сумма, выданная под залог, дата сдачи, срок хранения. 
//Выбор товаров по наименованию.

union forLombard
{
	char str[20];
	int limb;
};

struct Lombard
{
	forLombard name;
	forLombard surname;
	forLombard middleName;
	forLombard date_of_birthday;
	forLombard place_of_live;
	forLombard name_of_product;
	forLombard sum;
	forLombard sum_of_client;
	forLombard date_of_issue;
	forLombard shelfLife;
};

Lombard base_of_lombard[size];
int current_size = 0; int choice;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите число:" << endl;
	cout << "1-для ввода записи" << endl;
	cout << "2-для вывода записи" << endl;
	cout << "3-для поиска информации" << endl;
	cout << "4-для выхода" << endl;
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1:  enter_new();	break;
		case 2:  out();  break;
		case 3:  search();	break;
		}
	} while (choice != 4);
}
void enter_new()
{
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер  ";
		cout << current_size + 1;
		cout << "\n";
		cout << "                     " << "Анкета клиента" << "\n";
		cout << endl << "Фамилия" << endl;
		cin >> base_of_lombard[current_size].name.str;
		cout << "Имя" << endl;
		cin >> base_of_lombard[current_size].surname.str;
		cout << "Отчество" << endl;
		cin >> base_of_lombard[current_size].middleName.str;
		cout << "Дата рождения" << endl;
		cin >> base_of_lombard[current_size].date_of_birthday.str;
		cout << "Место проживания" << endl;
		cin >> base_of_lombard[current_size].place_of_live.str;
		cout << "                     " << "Информация о товаре" << "\n";
		cout << "Наименование товара" << endl;
		cin >> base_of_lombard[current_size].name_of_product.str;
		cout << "Оценочная стоимость" << endl;
		cin >> base_of_lombard[current_size].sum.limb;
		cout << "Сумма под залог" << endl;
		cin >> base_of_lombard[current_size].sum_of_client.limb;
		cout << "Дата сдачи" << endl;
		cin >> base_of_lombard[current_size].date_of_issue.str;
		cout << "Срок хранения" << endl;
		cin >> base_of_lombard[current_size].shelfLife.str;
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
	cout << "1-вывести 1 строку" << endl;
	cout << "2-вывести все строки" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "Номер выводимой строки: " << endl;
		cin >> n;
		cout << endl;
		cout << "                     " << "Анкета клиента" << "\n";
		cout << "Фамилия:";
		cout << base_of_lombard[n - 1].surname.str;
		cout << endl;
		cout << "Имя:";
		cout << base_of_lombard[n - 1].name.str;
		cout << endl;
		cout << "Отчество:";
		cout << base_of_lombard[n - 1].middleName.str;
		cout << endl;
		cout << "Дата рождения:";
		cout << base_of_lombard[n - 1].date_of_birthday.str;
		cout << endl;
		cout << "Место проживания:";
		cout << base_of_lombard[n - 1].place_of_live.str;
		cout << endl;
		cout << "                     " << "Информация о товаре" << "\n";
		cout << "Наименование товара:";
		cout << base_of_lombard[n - 1].name_of_product.str;
		cout << endl;
		cout << "Оценочная стоимость:";
		cout << base_of_lombard[n - 1].sum.limb;
		cout << endl;
		cout << "Сумма под залог:";
		cout << base_of_lombard[n - 1].sum_of_client.limb;
		cout << endl;
		cout << "Дата сдачи:";
		cout << base_of_lombard[n - 1].date_of_issue.str;
		cout << endl;
		cout << "Срок хранения:";
		cout << base_of_lombard[n - 1].shelfLife.str;
		cout << endl;
	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "                     " << "Анкета клиента" << "\n";
			cout << "Фамилия:";
			cout << base_of_lombard[i].surname.str;
			cout << endl;
			cout << "Имя:";
			cout << base_of_lombard[i].name.str;
			cout << endl;
			cout << "Отчество:";
			cout << base_of_lombard[i].middleName.str;
			cout << endl;
			cout << "Дата рождения:";
			cout << base_of_lombard[i].date_of_birthday.str;
			cout << endl;
			cout << "Место проживания:";
			cout << base_of_lombard[i].place_of_live.str;
			cout << endl;
			cout << "                     " << "Информация о товаре" << "\n";
			cout << "Наименование товара:";
			cout << base_of_lombard[i].name_of_product.str;
			cout << endl;
			cout << "Оценочная стоимость:";
			cout << base_of_lombard[i].sum.limb;
			cout << endl;
			cout << "Сумма под залог:";
			cout << base_of_lombard[i].sum_of_client.limb;
			cout << endl;
			cout << "Дата сдачи:";
			cout << base_of_lombard[i].date_of_issue.str;
			cout << endl;
			cout << "Срок хранения:";
			cout << base_of_lombard[i].shelfLife.str;
			cout << endl;

		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}
void search()
{
	char name[16];
	cout << "Введите наименование товара:" << "\n";
	cin >> name;
	for (int z = 0; z < current_size; z++)
	{
		if (strcmp(name, base_of_lombard[z].name_of_product.str) == 0)
		{
			cout << " " << "\nАнкета клиента: " << "\n\n";
			cout << "Фамилия:";
			cout << base_of_lombard[z].surname.str;
			cout << endl;
			cout << "Имя:";
			cout << base_of_lombard[z].name.str;
			cout << endl;
			cout << "Отчество:";
			cout << base_of_lombard[z].middleName.str;
			cout << endl;
			cout << "Дата рождения:";
			cout << base_of_lombard[z].date_of_birthday.str;
			cout << endl;
			cout << "Место проживания:";
			cout << base_of_lombard[z].place_of_live.str;
			cout << endl;
			cout << " " << "\nИнформация о товаре: " << "\n\n";
			cout << "Наименование товара:";
			cout << base_of_lombard[z].name_of_product.str;
			cout << endl;
			cout << "Оценочаня стоимость:";
			cout << base_of_lombard[z].sum.limb;
			cout << endl;
			cout << "Сумма под залог:";
			cout << base_of_lombard[z].sum_of_client.limb;
			cout << endl;
			cout << "Дата сдачи:";
			cout << base_of_lombard[z].date_of_issue.str;
			cout << endl;
			cout << "Срок хранения:";
			cout << base_of_lombard[z].shelfLife.str;
			cout << endl;

		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}*/