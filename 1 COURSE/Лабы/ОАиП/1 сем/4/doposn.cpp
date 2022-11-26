#include <iostream>

using namespace std;

void main() {

	setlocale(LC_CTYPE, "Russian");

	int k;
	cout << ("Что вы любите: 1) Чай, 2) Кофе");
	cin >> k;
	switch (k) {
	case 1:  puts("Хорощий выбор!"); break;
	case 2:  puts("Всё ясно... зависимый"); break;
	default: puts("А больше пить нечего)"); break;

	}

}