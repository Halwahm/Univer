#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const short N = 3;

struct client
{
	string name; 
	string address;
	string phone;
	string check; //реквизиты
	string person; //контактное лицо
};

struct rent
{
	string floor; //этаж
	string area; //площадь
	string conditioner;
	string price; //аренда
};

struct treaty
{
	string name_place; 
	string name_client;
	string renral_period; //период аренды
};

void place_entry(rent point[])
{
	cout << "Количество торговых точек: " << N << endl;

	for (short i = 0; i < N; i++)
	{
		cout << "\tТочка №" << i + 1 << endl;
		cout << "Введите этаж точки:\n";
		cin >> point[i].floor;
		cout << "Введите площадь:\n";
		cin >> point[i].area;
		cout << "Введите наличие кондиционера:\n";
		cin >> point[i].conditioner;
		cout << "Введите стоимость аренды:\n";
		cin >> point[i].price;
	}
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

void delete_place(rent point[])
{
	short numCin;
	cout << "Введите номер точки, информацию о котором Вы хотите удалить:\n";
	cin >> numCin;
	cout << endl;
	short i = numCin - 1;
    point[i].floor = ' ';
	point[i].area = ' ';
	point[i].conditioner = ' ';
	point[i].price = ' ';
	cout << endl;
}

void client_entry(client client[])
{
	short num;
	cout << "Введите количество клиентов: ";
	cin >> num;
	for (short i = 0; i < num; i++)
	{
		cout << "\tКлинт №" << i + 1 << endl;
		cout << "Введите имя клиента:\n";
		cin >> client[i].name;
		cout << "Введите адрес клиента:\n";
		cin >> client[i].address;
		cout << "Введите телефон клинта:\n";
		cin >> client[i].phone;
		cout << "Введите реквизиты:\n";
		cin >> client[i].person;
		cout << "Введите контактное лицо:\n";
		cin >> client[i].check;
		cout << endl;
	}
}

void treaty_place(treaty treaty_n[]) //kak dop
{
		cout << "Введите точку: ";
		short i;
		cin >> i;
	ofstream file1("information.txt");

	cout << "\tТочка №" << i << '\n';
	file1 << "\tТочка №" << i << '\n';
	cout << "Введите название точки:\n";
	file1 << "\nНазвание точки: ";
	cin >> treaty_n[i].name_place;
	file1 << treaty_n[i].name_place;
	cout << "Введите имя клиента:\n";
	file1 << "\nИмя клиента: ";
	cin >> treaty_n[i].name_client;
	file1 << treaty_n[i].name_client;
	cout << "Введите период аренды:\n";
	file1 << "\nПериод аренды: ";
	cin >> treaty_n[i].renral_period;
	file1 << treaty_n[i].renral_period << "\n\n";

	cout << endl;
}

void search(client clients[]) {
	string name;
	cout << "Введите имя клиента: ";
	cin >> name;
	for (short i = 0; i < N; i++) {
		if (name == clients[i].name)
		{
			cout << "Клиент " << "по имени " << clients[i].name << '\n';
		}
	}
	cout << "\n\n";
}

struct product
{
	string name; 
	string sroc; 
	string material;
	string price; 
};

void tovar(product material[]) {

	for (short i = 0; i < 1; i++) {
		cout << "Введите название товара" << endl;
		cin >> material[i].name;
		cout << "Введите срок хранения продукта" << endl;
		cin >> material[i].sroc;
		cout << "Введите материал изготовления товара" << endl;
		cin >> material[i].sroc;
		cout << "Введите цену товара" << endl;
		cin >> material[i].price;

		cout << endl;

		cout << "Название товара: " << material[i].name << endl;
		cout << "Cрок хранения продукта: " << material[i].sroc << endl;
		cout << "Материал изготовления товара: " << material[i].material << endl;
		cout << "Цена товара: " << material[i].price;
	}
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	rent point[N];
	client client[N];
	treaty treaty_n[N];
	product material[N];
	short choose;
	do {
		cout << "Введите желаемую операцию: " << endl;
		cout << "1 - ввод информации об аренде торговых точек" << endl;
		cout << "2 - вывод информации об аренде торговых точек" << endl;
		cout << "3 - удаление информации об аренде торговых точек" << endl;
		cout << "4 - ввод информации о клиентах" << endl;
		cout << "5 - оформить договор по аренде" << endl;
		cout << "6 - выход из программы" << endl;
		cout << "7 - имя клинта" << endl;
		cout << "8 - информация о товаре" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1: place_entry(point); break;
		case 2: output_place(point); break;
		case 3: delete_place(point); break;
		case 4: client_entry(client); break;
		case 5: treaty_place(treaty_n); break;
		case 6: cout << endl << "До свидания!" << endl; break;
		case 7: search(client); break; //dop
		case 8: tovar(material); break; //dop
		}
	} while (choose != 8);
}