//Техника. Реализовать хеш-таблицу со 
//следующими полями: название товара,
//год выпуска. Ключ – год выпуска.

/*
#include <iostream>
#include <string>
using namespace std;

struct Node {
	string data;
	Node* next;
	Node* prev;
};

int Hash(string tmp, int SIZE) {

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

	const int SIZE = 3;
	int key;
	bool flag = false;
	string tmp;

	Node* mass[SIZE];

	for (int i = 0; i < SIZE; ++i) {
		mass[i] = NULL;
	}



	int hashCode = 0;

	for (;;) {
		if (flag) {
			cout << "Полученный хеш-код: " << hashCode << endl;
			cout << "========= Хеш-таблица с цепочками ========= " << endl;
			showHashTable(mass, SIZE);
			cout << " ========================================== " << endl;
		}

		cout << "1 - Добавить элемент в хеш-таблицу: " << endl;
		cout << "2 - Удалить элемент из хеш-таблицы: " << endl;
		cout << "Выберите, что хотите сделать: " << endl;
		cin >> key;
		switch (key)
		{
		case 1:
			cout << "Введите название товара: " << endl;
			cin.ignore();
			getline(cin, tmp);



			hashCode = Hash(tmp, SIZE);
			flag = true;

			if (!mass[hashCode]) {

				mass[hashCode] = new Node;
				mass[hashCode]->data = tmp;
				mass[hashCode]->next = NULL;
				mass[hashCode]->prev = NULL;
			}
			else {
				addElement(mass[hashCode], tmp);
			}
			break;

		case 2:
			cout << "Введите название товара(ключ), который хотите удалить из хеш-таблицы: " << endl;
			cin >> tmp;
			Node* t = mass[Hash(tmp, SIZE)]; // получаем список, который содержит нужный элемент
			Node* buff;

			if (t) {
				while (t) {
					if (t->data == tmp) {
						if (!t->next) { // удаляет последний элемент
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


			break;


		}

		system("cls");
	}
}
*/
