#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const short N = 10;

struct client
{
	string name;
	string address;
	string phone;
	string check; //реквизиты
	string person; //контактное лицо

	int index;
};

struct rent
{
	string floor; //этаж
	string area; //площадь
	string conditioner;
	string price; //аренда

	int index;
};

struct WUZ //dop3
{
	string name;
	string address;
	string contest;
	string payment;
	string specialties;
};

struct treaty
{
	string name_place;
	string name_client;
	string renral_period; 

	int index;
};

void place_entry(rent point[])
{
	short num;
	cout << "Количество торговых точек: ";
	cin >> num;

	for (short i = 0; i < num; i++)
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

		point[i].index = i;
		cout << "index: " << point[i].index + 1;
		cout << endl;
	}

	short index_user;
	cout << "Введите индекс точки, которую хотите найти: ";
	cin >> index_user;

	for (short i = 0; i < num; i++)
	{
		if (point[i].index == index_user - 1) {
			cout << "Точка " << i + 1 << " найдена" << endl;
			cout << "Floor: " << point[i].floor << "  " << "Area: " << point[i].area;
			cout << '\n';
		}
	}
	cout << "\n";
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

		client[i].index = i;
		cout << "index: " << client[i].index + 1;
		cout << endl;
	}

	short index_user;
	cout << "Введите индекс пользователя, которого хотите найти: "; 
	cin >> index_user;

	for (short i = 0; i < num; i++)
	{
		if (client[i].index == index_user - 1) {
			cout << "Пользователь " << i + 1 << " найден" << endl;
			cout << "Name: " << client[i].name << "  " << "Phone: " << client[i].phone;
			cout << '\n';
		}
	}
}

void treaty_place(treaty treaty_n[]) 
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

	treaty_n[i].index = i;
	cout << "index: " << treaty_n[i].index + 1; //это договор по 1 точке, поэтому, смысла искать 1 точку нет
	cout << endl;
}

void search(client clients[], rent point[]) {
	string name, floor;
	cout << "Введите имя клиента: ";
	cin >> name;
	for (short i = 0; i < N; i++) {
		if (name == clients[i].name)
		{
			cout << "Клиент по имени " << clients[i].name << '\n';
		}
	} 
	//dop
	cout << "Введите этаж точки, которую хотите найти: ";
	cin >> floor;
	for (short i = 0; i < N; i++)
	{
		if (floor == point[i].floor)
		{
			cout << "Точка на " << i + 1 << " этаже найдена с площадью: " << point[i].area;
		}
	}
	cout << "\n\n";
}

//struct product
//{
//	string name;
//	string sroc;
//	string material;
//	string price;
//};
//
//void tovar(product material[]) {
//
//	for (short i = 0; i < 1; i++) {
//		cout << "Введите название товара" << endl;
//		cin >> material[i].name;
//		cout << "Введите срок хранения продукта" << endl;
//		cin >> material[i].sroc;
//		cout << "Введите материал изготовления товара" << endl;
//		cin >> material[i].sroc;
//		cout << "Введите цену товара" << endl;
//		cin >> material[i].price;
//
//		cout << endl;
//
//		cout << "Название товара: " << material[i].name << endl;
//		cout << "Cрок хранения продукта: " << material[i].sroc << endl;
//		cout << "Материал изготовления товара: " << material[i].material << endl;
//		cout << "Цена товара: " << material[i].price;
//	}
//}

void dop2() {
	ifstream file1("file2_1_1.txt");
	string str;
	int counter = 1;
	while (getline(file1, str))
	{
		if (str[0] == 'A' or str[0] == 'a')
		{
			cout << endl << str;

			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ' ')
				{
					counter++;
				}
			}
		}
	}
	cout << endl << "В строках с буквой 'а' по " << counter << " слова" << endl;
}

void dop3(WUZ students[]) {
	string buf;
	short num;
	do {
		cout << "Введите количество ВУЗ-ов (не более " << N << "): ";
		cin >> num;
	} while (num < 1 || num > N);
	fflush(stdin);
	ofstream file1("information1.txt");
	for (short i = 0; i < num; i++)
	{
		cout << "\tВУЗ №" << i + 1 << '\n';
		file1 << "\tВУЗ №" << i + 1 << '\n';
		cout << "Введите название ВУЗ-а:\n";
		file1 << "\nНазвание ВУЗ-а: ";
		cin >> students[i].name;
		file1 << students[i].name;
		cout << "Введите размер оплаты:\n";
		file1 << "\nРазмер оплаты:\n ";
		cin >> students[i].payment;
		file1 << students[i].payment;
		cout << "\n\n";
	}

	for (short i = 1; i < 2; i++)
	{
		if (students[0].payment < students[1].payment)
		{
			cout << "Оплата больше в ВУЗ-е номер " << i + 1 << '\n';
		}
		else
		{
			cout << "Оплата больше в ВУЗ-е номер" << i << '\n';
		}
	}
	cout << '\n';
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	rent point[N];
	client client[N];
	treaty treaty_n[N];
	WUZ students[N];
	/*product material[N];*/
	short choose;
	do {
		cout << "Введите желаемую операцию: (1, 4)" << endl;
		cout << "1 - ввод информации об аренде торговых точек" << endl;
		cout << "2 - вывод информации об аренде торговых точек" << endl;
		cout << "3 - удаление информации об аренде торговых точек" << endl;
		cout << "4 - ввод информации о клиентах" << endl;
		cout << "5 - оформить договор по аренде" << endl;
		cout << "7 - выход из программы" << endl;
		cout << "6 - имя клинта" << endl;
		cout << "8 - dop2" << endl;
		cout << "9 - dop3" << endl;
		//cout << "8 - информация о товаре" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1: place_entry(point); break;
		case 2: output_place(point); break;
		case 3: delete_place(point); break;
		case 4: client_entry(client); break;
		case 5: treaty_place(treaty_n); break;
		case 7: cout << endl << "До свидания!" << endl; break;
		case 6: search(client, point); break; //dop
		case 8: dop2(); break;
		case 9: dop3(students); break;
		//case 8: tovar(material); break; //dop
		}
	} while (choose != 7);
}