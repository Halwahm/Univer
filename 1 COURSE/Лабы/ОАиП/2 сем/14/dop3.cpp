/*
//В текстовом файле содержатся целые числа.
//Построить хеш - таблицу из чисел файла.
//Осуществить поиск введенного целого числа в хеш - таблице.
//Сравнить результаты количества сравнений при
//различном наборе данных в файле.


#include<iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;


struct Node {
	string data;
	Node* next;
	Node* prev;
};

int getHashCode(string tmp, int SIZE) {
	int ASCIIsum = 0;

	for (int i = 0; i < tmp.length(); ++i) {
		ASCIIsum += int(tmp[i]);
	}
	return ASCIIsum % SIZE;

}

void addElement(Node*& head, string tmp) {

	Node* t = head;
	Node* buff;
	for (;;) {
		if (!t->next) {
			buff = new Node;
			buff->data = tmp;
			buff->next = NULL;
			t->next = buff;
			buff->prev = t;

			break;
		}
		t = t->next;
	}

}
void showHashTable(Node** mass, int SIZE) {

	Node* t;
	for (int i = 0; i < SIZE; ++i) {
		t = mass[i];

		if (!mass[i])
			continue;

		cout << "[" << i << "] ---> ";
		while (t) {
			cout << t->data << " | ";
			t = t->next;
		}
		cout << endl;
	}


}
int main() {
	setlocale(LC_CTYPE, "rus");
	ifstream fin("numbers.txt");
	int SIZE;
	cout << "Введите размер хеш-таблицы: " << endl;
	cin >> SIZE;
	string tmp;
	Node** mass = new Node * [SIZE];
	int hashCode;

	for (int i = 0; i < SIZE; ++i) {
		mass[i] = NULL;
	}


	while (getline(fin, tmp, ' ')) {

		//cout << tmp << endl;
		hashCode = getHashCode(tmp, SIZE);

		if (!mass[hashCode]) {
			mass[hashCode] = new Node;
			mass[hashCode]->data = tmp;
			mass[hashCode]->next = nullptr;
			mass[hashCode]->prev = nullptr;

		}
		else {
			addElement(mass[hashCode], tmp);
		}
	}

	showHashTable(mass, SIZE);

	for (;;) {
		cout << "Введите число, которое хотите удалить: " << endl;
		cin >> tmp;

		Node* t = mass[getHashCode(tmp, SIZE)]; // получаем список, который содержит нужный элемент
		Node* buff;

		if (t) {
			while (t) {
				if (t->data == tmp) {
					if (!t->next) { // удаяет последний элемент
						buff = t->next;
						(t->prev)->next = nullptr;
						delete buff;
						break;
					}

					else {
						(t->prev)->next = t->next;
						(t->next)->prev = t->prev;
						delete t;
						break;

					}
				}

				t = t->next;
			}
		}
		else cout << "Нет элементов с таким хеш-кодом: " << endl;

		system("cls");
		showHashTable(mass, SIZE);
	}

}
*/