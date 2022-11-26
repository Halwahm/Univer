/*
#include<iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

//Построить хеш - таблицу из слов произвольного 
//текстового файла, задав ее размерность с экрана.
//Вывести построенную таблицу слов на экран.
//Осуществить поиск введенного слова.
//Выполнить программу для различных размерностей 
//таблицы и сравните количество сравнений.
//Удалить все слова, начинающиеся на указанную букву, 
//выведите таблицу.

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

		cout << "hashTableRow[" << i << "] ---> ";
		while (t) {
			cout << t->data << " | ";
			t = t->next;
		}
		cout << endl;
	}


}
int main() {
	setlocale(LC_CTYPE, "rus");
	ifstream fin("words.txt");
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
	char p;
	for (;;) {
		cout << "Введите  слово(ключ), которые хотите удалить: " << endl;
		cin >> p;

		Node* t;
		int a = 0;

		while (a < SIZE) {
			if (!mass[a])
				continue;

			t = mass[a]->next;
			while (t) {
				if ((t->data)[0] == p) {
					if (!t->next) {
						(t->prev)->next = nullptr;
						break;

					}
					else {
						(t->prev)->next = t->next;
						(t->next)->prev = t->prev;

					}
				}
				t = t->next;
			}
			a++;
		}
		system("cls");
		showHashTable(mass, SIZE);
	}
}
*/