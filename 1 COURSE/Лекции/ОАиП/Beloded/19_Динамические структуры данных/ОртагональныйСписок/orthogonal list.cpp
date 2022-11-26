/*
* Author: Yaroslav Voroshilov,
* BELSTU, FIT, ПОИБМС, 1st year, group #7 
*/
#include <iostream>
#include <iomanip>

#define NODETYPE 0;
#define ORTHNODETYPE 1;

using namespace std;

struct Node {
	int data;
	Node *next;
};

class List {
	private:
	Node *head;
	public:
	List (): head(nullptr) {};
	void newNode (int newData = 0);
	int getData (int pos);
	void setData (int pos, int newData);
	void insert (int pos, int newData = 0);
	void erase (int pos);
	void clear ();
	Node* search (int val);

	Node *const getHead ();
	void printAll ();

};

struct OrthNode {
	int data;
	OrthNode *next;
	List *trail;
};

class OrthogonalList {
	private:
	OrthNode *head;
	public:
	OrthogonalList (): head(nullptr) {};
	void newOrthNode (int newData = 0);
	void newTrailNode (int trailN, int newData = 0);
	int getData (int trailN, int posInColumn);
	void setData (int trailN, int posInColumn, int newData = 0);
	void insert (int trailN, int posInColumn, int newData = 0);
	void erase (int trailN, int posInColumn);
	void clear ();
	void clearTrail (int trailN);
	void* search(int val, int &type);

	void printAll ();
};

void testOrthogonalList ();

int main () {
	testOrthogonalList();
	system("pause");
	return 0;
}

void testOrthogonalList () {
	OrthogonalList l;
	cout << "--------------List building--------------"<< endl;
	l.newOrthNode(1);
	l.newOrthNode(2);
	l.newOrthNode(13);
	l.newOrthNode(14);
	l.newOrthNode(2345);
	l.newTrailNode(4, 45);
	l.newTrailNode(4, 432);
	l.newTrailNode(1, 33);
	l.newTrailNode(2, 4);
	l.newTrailNode(1, 5);
	l.newTrailNode(1, 6);
	l.printAll();
	cout << "--------------Inserting--------------" << endl;
	l.insert(4, 4, 15);
	l.insert(3, 1, 78);
	l.printAll();
	cout << "--------------Deleting--------------" << endl;
	l.erase(2, 1);
	l.erase(5, 1);
	l.printAll();
	cout << "--------------Searching--------------" << endl;
	int t;
	cout << ((Node*)l.search(432, t))->data << endl;
	cout << ((OrthNode*)l.search(78, t))->data << endl;
	cout << "--------------Clearing--------------" << endl;
	l.clearTrail(4); cout << endl;
	l.printAll();
	l.clear();
	l.printAll();
}

//--------------Ordinary linked linear list methods--------------
/*
* RUS: Стандартные функции для линейного списка. Реализованы без каких-либо особенностей.
* Примечание 1: Индексация списка происходит с головы, начиная с единицы.
* Примечание 2: функция insert() вставляет элемент в то место, в котором он будет под
* номером pos после вставки.
* ENG: There are some common functions for linked linear list. Implemented without any 
* extra features.
* Note 1: List indexing begins from the head, starting from one.
* Note 2: Insert() function inserts an element in exactly that place where it will be
* on the position defined by "pos" after insertion happened.
*/

void List::newNode (int newData) {
	Node *cur = head, *tmp = new Node;
	tmp->data = newData;
	tmp->next = nullptr;
	if (head) {
		while (cur->next) {
			cur = cur->next;
		}
		cur->next = tmp;
	} else {
		head = tmp;
	}
}

int List::getData (int pos) {
	Node *cur = head;
	for (int i = 1; i < pos; i++) {
		cur = cur->next;
	}
	return cur->data;
}

void List::setData (int pos, int newData) {
	Node *cur = head;
	for (int i = 1; i < pos; i++) {
		cur = cur->next;
	}
	cur->data = newData;
}

void List::insert (int pos, int newData) {
	Node *cur = head, *tmp = new Node;
	tmp->data = newData;
	tmp->next = nullptr;
	for (int i = 1; i < pos - 1; i++) {
		cur = cur->next;
	}
	tmp->next = cur->next;
	cur->next = tmp;
}

void List::erase (int pos) {
	Node *cur = head;
	for (int i = 1; i < pos - 1; i++) {
		cur = cur->next;
	}
	if (cur == head) {
		head = head->next;
		delete cur;
	} else {
		Node *del = cur->next;
		cur->next = cur->next->next;
		delete del;
	}
}

void List::clear () {
	Node *cur = head->next, *prev = head;
	while (cur) {
		prev = cur;
		cur = cur->next;
		delete prev;
	}
	head = nullptr;
}

Node* List::search (int val) {
	Node *cur = head;
	while (cur && (cur->data != val)) {
		cur = cur->next;
	}
	return cur;
}

Node *const List::getHead () {
	return head;
}

void List::printAll () {
	Node *cur = head;
	if (!cur) {
		cout << "The list is empty!" << endl;
		return;
	}
	while (cur) {
		cout << cur->data << ' ';
		cur = cur->next;
	} cout << endl;
}

//--------------Orthogonal list methods--------------
/*
* RUS: Все функции для ортогонального списка реализованы с помощью функций, определённых
* для обычного линейного связного списка. Большинство из них имеют аргумент posInColumn,
* значение которого может быть либо 1, тогда метод выполняет действия с гирляндой, либо
* больше. В этом случае будут выполняться действия с хвостом, то есть списком.
* ENG: All the functions below implemented with the help of methods defined for ordinary
* linear linked list. Most of them have "posInColumn" argument which value can be either
* 1 (in this case method works with a "гирлянда") or bigger. In this case the method
* will work with a trail that is a list.
*/

void OrthogonalList::newOrthNode (int newData) {
	OrthNode *cur = head, *tmp = new OrthNode;
	tmp->data = newData;
	tmp->next = nullptr;
	tmp->trail = nullptr;
	if (cur) {
		while (cur->next) {
			cur = cur->next;
		}
		cur->next = tmp;
	} else {
		head = tmp;
	}
}

void OrthogonalList::newTrailNode (int trailN, int newData) {
	OrthNode *cur = head;
	for (int i = 1; i < trailN; i++) {
		cur = cur->next;
	}
	if (!cur->trail) cur->trail = new List;
	cur->trail->newNode(newData);
}

int OrthogonalList::getData (int trailN, int posInColumn) {
	OrthNode *cur = head;
	for (int i = 1; i < trailN; i++) {
		cur = cur->next;
	}
	if (posInColumn > 1) {
		return cur->trail->getData(posInColumn - 1);
	} else {
		return cur->data;
	}
}

void OrthogonalList::setData (int trailN, int posInColumn, int newData) {
	OrthNode *cur = head;
	for (int i = 1; i < trailN; i++) {
		cur = cur->next;
	}
	if (posInColumn > 1) {
		cur->trail->setData(posInColumn - 1, newData);
	} else {
		cur->data = newData;
	}
}

void OrthogonalList::insert (int trailN, int posInColumn, int newData) {
	OrthNode *cur = head;
	for (int i = 1; i < trailN - 1; i++) {
		cur = cur->next;
	}
	if (posInColumn == 1) {
		if (cur == head) {
			OrthNode *tmp = new OrthNode;
			tmp->data = newData;
			tmp->next = head;
			tmp->trail = nullptr;
			head = tmp;
		} else {
			OrthNode *tmp = new OrthNode;
			tmp->data = newData;
			tmp->next = cur->next;
			tmp->trail = nullptr;
			cur->next = tmp;
		}
	} else {
		if (cur != head) cur = cur->next;
		cur->trail->insert(posInColumn - 1, newData);
	}
}

void OrthogonalList::erase (int trailN, int posInColumn) {
	OrthNode *cur = head;
	for (int i = 1; i < trailN - 1; i++) {
		cur = cur->next;
	}
	if (posInColumn == 1) {
		clearTrail(trailN);
		if (cur == head) {
			head = head->next;
			delete cur;
		} else {
			OrthNode *del = cur->next;
			cur->next = cur->next->next;
			delete del;
		}
	} else {
		if (cur == head) head->trail->erase(posInColumn - 1);;
		cur->next->trail->erase(posInColumn - 1);
	}
}

void OrthogonalList::clear () {
	OrthNode *cur = head->next, *prev = head;
	while (cur) {
		prev = cur;
		if (cur->trail && cur->trail->getHead()) cur->trail->clear();
		cur = cur->next;
		delete prev;
	}
	head = nullptr;
}

void OrthogonalList::clearTrail (int trailN) {
	OrthNode *cur = head;
	for (int i = 1; i < trailN; i++) {
		cur = cur->next;
	}
	if (cur->trail && cur->trail->getHead()) cur->trail->clear();
}

/*
* RUS: Функция search() может вернуть как OrthNode, так и Node, поэтому я решил, что
* правильнее всего сделать одну функцию, возвращающую неопределённый указатель, а не две
* функции: для OrthNode и для Node. Решение о конвертации (или не конвертации) в необходимый 
* пользователю тип остаётся за самим пользователем.
* ENG: The search() function can return OrthNode as well as Node, so i decided that
* the most appropriate way is to write only one function returns void pointer, rather than
* two functions: for OrthNode and Node. The decision about converting (or not) to a necessary
* type is up to user.
*/
void* OrthogonalList::search (int val, int &type) {
	OrthNode *cur = head;
	while (true) {
		if (!cur) return nullptr;
		if (cur->data == val) {
			type = ORTHNODETYPE;
			return (void*)cur;
		}
		Node *found = (cur->trail) ? cur->trail->search(val) : nullptr;
		if (found) {
			type = NODETYPE;
			return (void*)found;
		}
		cur = cur->next;
	}
}

/*
* RUS: Эта функция выводит весь список на экран. Она создаёт массив, в котором будут храниться
* головы всех хвостов. Затем запускает цикл, в котором одновременно выводится гирлянда и заполняется
* массив голов хвостов. После этого начинается цикл, на каждом шаге которого выводится один ряд 
* висюлек и который будет продолжаться до тех пор, пока выводится хотя бы одна висюлька. Такая
* реализация была необходима, чтобы ортогональный список выводился в удобочитаемом виде.
* ENG: This function prints the whole list on the screen. It creates an array which will contain
* heads of all trails. Then a loop will begin which will display a "гирлянда" and fullfill the array
* of heads of all trails. After it another loop begins which will display one row of "висюлька" 
* at every step and it will go on while at least one "висюлька" is displaying. Such implementation
* is needed for better readability of the orthogonal list.
*/
void OrthogonalList::printAll () {
	const int MAXTRAILS = 100;
	const int WIDTH = 5;
	OrthNode *cur = head;
	if (!cur) {
		cout << "The list is empty!" << endl;
		return;
	}
	Node *arr[MAXTRAILS];
	int trailCnt = 0;
	for (int i = 0; cur; i++) {
		trailCnt++;
		cout << setw(WIDTH) << cur->data;
		arr[i] = cur->trail ? cur->trail->getHead() : nullptr;
		cur = cur->next;
	} cout << endl;
	for (int i = 0; i < trailCnt; i++) {
		if (arr[i]) {
			cout << setw(WIDTH) << "|";
		} else {
			cout << setw(WIDTH) << ' ';
		}
	} cout << endl;
	bool done;
	do {
		done = true;
		for (int i = 0; i < trailCnt; i++) {
			if (!arr[i]) {
				cout << setw(WIDTH) << ' ';
				continue;
			}
			done = false;
			cout << setw(WIDTH) << arr[i]->data;
			arr[i] = arr[i]->next;
		} cout << endl;
	} while (!done);
}