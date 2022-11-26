#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

const short N = 3;

int main();

// Основа 
/*Справочник абитуриента. Наименование вуза, адрес, конкурс прошлого года, 
размер оплаты при договорном обучении. Выбор по специальности.*/

struct WUZ
{
	string name;
	string address;
	string contest;
	string payment;
	string specialties;
};

void input(WUZ students[])
{
	short num;
	do {
		cout << "Введите количество ВУЗ-ов (не более " << N << "): ";
		cin >> num;
	} while (num < 1 || num > N);
	fflush(stdin);
	for (short i = 0; i < num; i++)
	{
		cout << "\tВУЗ №" << i + 1 << endl;
		cout << "Введите название ВУЗ-а:\n";
		cin >> students[i].name;
		cout << "Введите адрес:\n";
		cin >> students[i].address;
		cout << "Введите конкурс прошлого года:\n";
		cin >> students[i].contest;
		cout << "Введите размер оплаты:\n";
		cin >> students[i].payment;
		cout << "Введите специальность:\n";
		cin >> students[i].specialties;
		cout << "\n\n";
	}
}

void output(WUZ students[])
{
	short WuzNum;
	cout << "Введите номер ВУЗ-а, который вы хотите вывести:\n";
	cin >> WuzNum;
	short i = WuzNum - 1;
	cout << "\tВУЗ №" << WuzNum << '\n';
	cout << "Название ВУЗ-а: " << students[i].name << '\n';
	cout << "Адрес: " << students[i].address << '\n';
	cout << "Конкурс прошлого года: " << students[i].contest << '\n';
	cout << "Размер оплаты: " << students[i].payment << '\n';
	cout << "Cпециальность: " << students[i].specialties << "\n\n\n";
}

void deleteWUZ(WUZ students[])
{
	short numCin;
	cout << "Введите порядковый номер ВУЗ-а, информацию о котором Вы хотите удалить:\n";
	cin >> numCin;
	cout << '\n';
	short i = numCin - 1;
	students[i].name = ' ';
	students[i].address = ' ';
	students[i].contest = ' ';
	students[i].payment = ' ';
	students[i].specialties = ' ';
	cout << '\n';
}

void search(WUZ students[])
{
	string numSearch;
	cout << "Введите адрес искомого ВУЗ-а:\n";
	cin >> numSearch;
	for (short i = 0; i < N; i++)
	{
		if (numSearch == students[i].address)
		{
			cout << "ВУЗ №" << i + 1 << ": адрес" << students[i].address << '\n';
		}
	}
	cout << "\n\n";
}

void ofile(WUZ students[])
{
	string buf;
	short num;
	do {
		cout << "Введите количество ВУЗ-ов (не более " << N << "): ";
		cin >> num;
	} while (num < 1 || num > N);
	fflush(stdin);
	ofstream file1("information.txt");
	for (short i = 0; i < num; i++)
	{
		cout << "\tВУЗ №" << i + 1 << '\n';
		file1 << "\tВУЗ №" << i + 1 << '\n';
		cout << "Введите название ВУЗ-а:\n";
		file1 << "\nНазвание ВУЗ-а: ";
		cin >> students[i].name;
		file1 << students[i].name;
		cout << "Введите адрес ВУЗ-а:\n";
		file1 << "\nАдрес ВУЗ-а: ";
		cin >> students[i].address;
		file1 << students[i].address;
		cout << "Введите конкурс:\n";
		file1 << "\nКонкурс: ";
		cin >> students[i].contest;
		file1 << students[i].contest;
		cout << "Введите размер оплаты:\n";
		file1 << "\nРазмер оплаты:\n ";
		cin >> students[i].payment;
		file1 << students[i].payment;
		cout << "Введите специальность:\n";
		file1 << "\nСпециальность: ";
		cin >> students[i].specialties;
		file1 << students[i].specialties << "\n\n";
	}
	cout << "\n\n";
}

void ifile(WUZ students[])
{
	string strInf;
	ifstream file1("information.txt");
	while (file1)
	{
		getline(file1, strInf);
		cout << strInf << '\n';
	}
}

void osnova()
{
	setlocale(LC_ALL, "Russian");
	short choose;
	WUZ students[N];
	do {
		cout << "Выберите, что сделать:\n1 — ввод элементов структуры с клавиатуры;\n2 — вывод элементов стуктуры в консольное окно;"
			"\n3 — удаление заданной структурированной переменной; \n4 — поиск информации; \n5 — запись информации в файл; \n6 — чтение данных из файла; \n7 — выход из программы.\n";
		cin >> choose;
		switch (choose)
		{
		case 1: input(students); break;
		case 2: output(students); break;
		case 3: deleteWUZ(students); break;
		case 4: search(students); break;
		case 5: ofile(students); break;
		case 6: ifile(students); break;
		case 7: main(); break;
		}
	} while (choose != 7);
}


//Доп 1 
/*Определить структуру для представления информации о сданных студентом экзаменах, содержащую поля: ФИО студента,
число экзаменов, полученные оценки. Определить функции для обработки отдельного объекта (например, для проверки,
сданы ли все экзамены на 4 и 5). Написать функцию для обработки массива структур. В результате обработки требуется
вычислить характеристику успеваемости студентов, то есть отношение числа студентов, сдавших экзамены на 4 и 5, к
общему числу студентов, в процентах. */

struct Student {
	string name;
	short maths;
	short physics;
	short english;
	short oap;
	short lg;
};

void exams(Student* students, short SIZE) {

	short numStudents = 0;
	for (short i = 0; i < SIZE; ++i) {

		if ((students[i].maths == 5 || students[i].maths == 4) &&
			(students[i].physics == 5 || students[i].physics == 4) &&
			(students[i].english == 5 || students[i].english == 4) &&
			(students[i].oap == 5 || students[i].oap == 4) &&
			(students[i].lg == 5 || students[i].lg == 4))
		{
			cout << i << ") Студент: " << students[i].name << " сдал экзамены на 4 или 5" << endl;
			numStudents++;
		}
		else cout << i << ") Студент: " << students[i].name << " не сдал экзамены на 4 или 5" << endl;
	}
	cout << "Сотношение студентов, сдавших экзамен на 4 или 5, ко всем студентам " << ((double)numStudents / (double)SIZE) * 100 << " % " << endl;
}

void displayInfo(Student* students, short SIZE) {
	for (short i = 0; i < SIZE; ++i) {
		cout << "Имя студента: " << students[i].name << endl;
		cout << "Математика: " << students[i].maths << endl;
		cout << "Физика: " << students[i].physics << endl;
		cout << "Английский: " << students[i].english << endl;
		cout << "ОАП: " << students[i].oap << endl;
		cout << "ЯП: " << students[i].lg << endl;
		cout << "///////////////////////////////////////" << endl;
	}
}

void  ifileStud(Student* students, short SIZE) {
	ifstream fin("studentsInfo.txt");
	if (!fin.is_open()) {
		cout << "Не удаётся открыть файл для чтения " << endl;
		exit(EXIT_FAILURE);
	}
	for (short i = 0; i < SIZE; ++i) {
		fin >> students[i].maths;
		fin >> students[i].physics;
		fin >> students[i].english;
		fin >> students[i].oap;
		fin >> students[i].lg;
		fin >> students[i].name;
	}
	cout << "\nВыведена информация из файла studentsInfo.txt\n";
}

void dop1()
{
	setlocale(LC_CTYPE, "ru");
	const short SIZE = 7;
	Student students[SIZE];
	short choose;
	do {
		cout << "\nВыберите, что сделать:\n1 — проверить, сколько студентов положительно сдали экзамены;\n2 — вывести в консоль информацию о студенте;\n3 — вывести информацию из файла;\n4 — выход из программы.\n";
		cin >> choose;
		switch (choose)
		{
		case 1: exams(students, SIZE); break;
		case 2: displayInfo(students, SIZE); break;
		case 3: ifileStud(students, SIZE); break;
		case 4: main(); break;
		}
	} while (choose != 4);
}







//Доп 2  
/*Описать структуру с именем TRAIN, содержащую поля: названия пункта назначения,
номер поезда, время отправления. Написать программу, выполняющую ввод с клавиатуры
данных в массив, состоящий из восьми элементов типа TRAIN (записи должны быть размещены
в алфавитном порядке по названиям пунктов назначения); вывод на экран информации о поездах,
отправляющихся после введенного с клавиатуры времени (если таких поездов нет, то вывести сообщение об этом).*/

struct Train {
	string Place;// место назначения
	short NumTrain; // номер поезда
	string time; // время отбытия 
};


bool compTrain(Train lhs, Train rhs)
{
	return lhs.Place < rhs.Place;
}

void displayTrain(Train* trains, short SIZE) {
	sort(trains, trains + SIZE, compTrain);

	for (short i = 0; i < SIZE; ++i)
	{
		cout << "Номер поезда: " << trains[i].NumTrain << "\t";
		cout << "Место прибытия: " << trains[i].Place << "\t\t";
		cout << "Время прибытия на вокзал: " << trains[i].time << "\t";
		cout << "\n///////////////////////////////////////////////////////////////////////////////////" << endl;
	}
};

void displayTrainMode(Train* trains, short SIZE, string user_time)
{
	sort(trains, trains + SIZE, compTrain);

	if (user_time.size() > 5 || user_time.size() < 2)
	{
		cout << "Некорретная дата " << endl;
		exit(1);
	}

	istringstream x(user_time, istringstream::in);
	short time_user1;
	x >> time_user1;
	x.clear();

	short hours_user = time_user1 / 100; // часы 
	short minuts_user = time_user1 % 100;// минуты 

	if (hours_user < -1 || hours_user > 60 || minuts_user < -1 || minuts_user > 60)
	{
		cout << "Некорретная дата " << endl;
		exit(1);
	}


	cout << "Ваше время : " << hours_user << " часов, " << minuts_user << " минут " << endl;
	short all_user_time = hours_user * 60 * 60 + minuts_user * 60; //секунды с начатого дня

	vector <short> time_train;

	for (short i = 0; i < SIZE; i++)
	{
		istringstream x(trains[i].time, istringstream::in);
		short train_rail;
		x >> train_rail;
		short train_hours = train_rail / 100;
		short train_minuts = train_rail % 100;
		time_train.push_back((train_hours * 60 * 60) + (train_minuts * 60));
	}
	bool ones = false;

	for (short i = 0; i < SIZE; i++)
	{
		if (all_user_time < time_train[i])
		{
			cout << "Номер поезда: " << trains[i].NumTrain << "\t";
			cout << "Место прибытия: " << trains[i].Place << "\t\t";
			cout << "Время прибытия на вокзал: " << trains[i].time << "\t";
			cout << "\n////////////////////////////////////////////////////////////////////////////////////////" << endl;
			ones = true;
		}
	}
	if (ones == false)
	{
		cout << "Нет поездов." << endl;
	}
}
;

void ifileTrain(Train* trains, short SIZE)
{
	ifstream fin("trainsInfo.txt");

	if (!fin.is_open()) {
		cout << "Не удаётся открыть файл для чтения " << endl;
		exit(EXIT_FAILURE);
	}

	vector<string> fileinfo;
	string line, word;
	stringstream x;
	for (short i = 0; i < SIZE; ++i) {

		fin >> trains[i].NumTrain;//номер поезда 

		getline(fin, line);

		x << line; // деление строки
		while (x >> word)
		{
			fileinfo.push_back(word);
		}

		for (short k = 0; k < fileinfo.size(); ++k)
		{
			if (k == 0) { trains[i].Place = fileinfo[k]; }
			if (k == 1) { trains[i].time = fileinfo[k]; }
		}

		x.clear();
		line.clear();
		word.clear(); 
		fileinfo.clear();
	}

}

void dop2()
{
	setlocale(LC_CTYPE, "rus");
	const short SIZE = 5;
	Train trains[SIZE];
	ifileTrain(trains, SIZE);
	displayTrain(trains, SIZE);
	cout << "\nВведите дату (формат ЧЧММ): ";
	string user_time;
	cin >> user_time;
	cout << endl;
	displayTrainMode(trains, SIZE, user_time);



	short choose;
	WUZ students[N];
	do {
		cout << "\n1 - выход из программы.\n";
		cin >> choose;
		switch (choose)
		{
		case 1:  main(); break;
		}
	} while (choose != 1);

}



// Доп 3  
/*Определить структуру для представления информации о наличии санаторных путевок,
содержащую следующие поля: Название санатория, Место расположения, Лечебный профиль,
Количество путевок. Представить введенные данные в виде таблицы, сгруппировав их по
лечебным профилям санаториев. В пределах каждой группы данные отсортировать по названиям
санаториев. Организовать поиск информации и вывод результатов. */
struct Camp {
	string CampName;
	string CampPlace;
	string CampType;
	short voucher;
};

bool comp1(Camp lhs, Camp rhs)
{
	return lhs.CampName < rhs.CampName;
}

bool comp(Camp lhs, Camp rhs)
{
	return lhs.CampType < rhs.CampType;
}

void showInfo(Camp* lagger, short SIZE) {
	sort(lagger, lagger + SIZE, comp);
	short index1 = 0;
	short index2 = 0;

	for (short i = 0; i < SIZE; i++)
	{
		if (lagger[i].CampType == lagger[i + 1].CampType)
		{
			index1 = i;
			break;
		}
	}

	for (short i = SIZE; i > 0; i--)
	{
		if (lagger[i].CampType == lagger[i - 1].CampType)
		{
			index2 = i;
			break;
		}
	}

	sort(lagger + index1, lagger + index2 + 1, comp1);


	for (short i = 0; i < SIZE; ++i) {
		cout << "Название лагеря: " << lagger[i].CampName << "\t";
		cout << "Место лагеря: " << lagger[i].CampPlace << "\t";
		cout << "Профиль лечения: " << lagger[i].CampType << "\t\t";
		cout << "Количество путевок: " << lagger[i].voucher << "\t" << endl;
		cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	}

}

void ifileCamp(Camp* lagger, short SIZE)
{

	ifstream fin("lagggerInfo.txt");

	if (!fin.is_open()) {
		cout << "Не удаётся открыть файл для чтения " << endl;
		exit(EXIT_FAILURE);
	}

	vector<string> fileinfo;
	string line, word;
	stringstream x;
	for (short i = 0; i < SIZE; ++i) {
		fin >> lagger[i].voucher;
		getline(fin, line);
		x << line;
		while (x >> word)
		{
			fileinfo.push_back(word);
		}
		for (short k = 0; k < fileinfo.size(); k++)
		{
			if (k == 0) { lagger[i].CampName = fileinfo[k]; }
			if (k == 1) { lagger[i].CampPlace = fileinfo[k]; }
			if (k == 2) { lagger[i].CampType = fileinfo[k]; }
		}
		x.clear();
		line.clear();
		word.clear();
		fileinfo.clear();
	}
	cout << "\nИнформация считана из файла lagggerInfo.txt\n\n";
}


void dop3()
{

	setlocale(LC_CTYPE, "ru");
	const short SIZE = 5;
	Camp lager[SIZE];
	short choose;
	do {
		cout << "Выберите, что сделать:\n1 — вывести информацию из файла;\n2 — вывести в консоль информацию о путёвках;\n3 — выход\n";
		cin >> choose;
		switch (choose)
		{
		case 1: ifileCamp(lager, SIZE); break;
		case 2: showInfo(lager, SIZE); break;
		case 3: exit(0); break;
		}
	} while (choose != 3);
}


int main() {
	setlocale(LC_CTYPE, "Russian");
	short chooseM;
	cout << "Введите, какую лабораторную выполнить:\n1 — основа(14 вар);\n2 — доп 1;\n3 — доп 2;\n4 — доп 3;\n5 — завершение работы.\n";
	cin >> chooseM;
	switch (chooseM)
	{
	case 1: osnova(); break;
	case 2: dop1(); break;
	case 3: dop2(); break;
	case 4: dop3(); break;
	case 5: cout << "\nДо свидания!\n"; break;
	}
}