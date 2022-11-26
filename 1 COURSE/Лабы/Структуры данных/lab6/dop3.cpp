

#include <iostream>
#include <fstream>

using namespace std;

//Определить структуру для представления информации о сданных студентом экзаменах, содержащую поля: ФИО студента,
//число экзаменов, полученные оценки. Определить функции для обработки отдельного объекта (например, для проверки,
//сданы ли все экзамены на 4 и 5). Написать функцию для обработки массива структур. В результате обработки требуется
//вычислить характеристику успеваемости студентов, то есть отношение числа студентов, сдавших экзамены на 4 и 5, к
//общему числу студентов, в процентах. 

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

void main()
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
		case 4: cout << "До свидания!"; break;
		}
	} while (choose != 4);
}

