//7 variant
/*Дан указатель p1 на корень непустого дерева. 
Написать функцию вывода количества листьев данного дерева. */

/*
#include <iostream> 
using namespace std;

struct node {
	int info;
	node* l, * r;
};

node* tree1 = NULL;

void push(int a, node** t) {
	if ((*t) == NULL) {
		(*t) = new node;
		(*t)->info = a;
		(*t)->l = (*t)->r = NULL;
		return;
	}

	if (a > (*t)->info)
		push(a, &(*t)->r);
	else
		push(a, &(*t)->l);
}

void print(node* t, int u) {
	if (t == NULL) return;
	else
	{
		print(t->r, ++u);
		for (int i = 0; i < u; ++i)
			cout << "|";
		cout << t->info << endl;
		u--;
	}
	print(t->l, ++u);


}
void printLeaf(node* t)
{


	if ((t->l == nullptr) && (t->r == nullptr))
	{
		cout << t->info << " ";
	}
	else
	{
		if (t->l) printLeaf(t->l);
		if (t->r) printLeaf(t->r);
	}
}
void del(node** t)
{
	if (t != nullptr)
	{
		if ((*t)->l)del(&(*t)->l);
		if ((*t)->r)del(&(*t)->r);
		delete* t;
		*t = nullptr;
	}
}
void check(node* t)
{
	if (t == NULL)
	{
		cout << "Дерева нет" << endl;
	}
	else
	{
		return;
	}
}

int main() {
	setlocale(0, "");
	int Amount, newNumber;
	cout << "Введите количество элементов:\t";
	cin >> Amount;
	cout << "\nВводите Числа:\n";
	for (int i = 0; i < Amount; ++i) {
		cin >> newNumber;
		push(newNumber, &tree1);
	}
	cout << "\nДерево:\n";
	print(tree1, 0);
	cout << endl;
	cout << "Листья:";
	printLeaf(tree1);
	del(&tree1);
	cout << endl;
	check(tree1);
}
*/