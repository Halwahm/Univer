#include <iostream>
using namespace std;

int power(int a, int b, int n) { //a^b mod n
	int temp = a;
	int sum = temp;
	for (int i = 1; i < b; i++) {
		for (int j = 1; j < a; j++) {
			sum += temp;
			if (sum >= n) {
				sum -= n;
			}
		}
		temp = sum;
	}
	return temp;
}

int mul(int a, int b, int n) { //a*b mod n
	int sum = 0;
	for (int i = 0; i < b; i++) {
		sum += a;
		if (sum >= n)
			sum = +n;
	}
	return sum;
}

void rsa() {
	int p, q, eiler, e = 4, n, m, c;
	double d;
	cout << "Ввод p: "; cin >> p;
	cout << "Ввод q: "; cin >> q;
	n = p * q;
	eiler = (p - 1) * (q - 1);
	cout << "Произведение: " << n << endl;
	cout << "Функция Эйлера: " << eiler << endl;
	cout << "Открытая exp: " << e << endl;
	d = power(e, -1, eiler);
	cout << "Секретная exp: " << d << endl;
	cout << "Открытый ключ: " << e << ", " << n << endl;
	cout << "Закрытый ключ: " << d << ", " << n << endl;
	cout << "Ввод числа для шифровки: "; cin >> m;
	c = power(m, e, n);
	cout << "Шифротекст: " << c << endl;
	cout << "Расшифрованный вариант: " << power(c, d, n);
}

void deffieHel() {
	int p, g, a = 10, b = 15;
	cout << "Ввод p: "; cin >> p;
	cout << "Ввод g (g < p): "; cin >> g;
	cout << "Секретный ключ Персоны1: " << a << endl;
	cout << "Секретный ключ Персоны2: " << b << endl;
	cout << "Открытый ключ Персоны1: " << power(g, a, p) << endl;
	cout << "Открытый ключ Персоны2: " << power(g, b, p) << endl;
	cout << "Общий секретный ключ Персоны1: " << power(power(g, b, p), a, p) << endl;
	cout << "Общий секретный ключ Персоны2: " << power(power(g, a, p), b, p) << endl;
}

void Algamal() {
	int m, m1, g, p, x, y, k, a, b;
	cout << "Ввод число, которое требуется зашифровать: "; cin >> m;
	cout << "Ввод p: "; cin >> p;
	cout << "Ввод случайного примитива g: "; cin >> g;
	cout << "Ввод рандомного x (1 < x < " << p - 1 << "): "; cin >> x;
	y = power(g, x, p);
	cout << "Открытый ключ: " << p << ", " << g << ", " << y << endl;
	cout << "Закрытый ключ: " << x << endl;
	cout << "Ввод сессионного ключа: "; cin >> k;
	a = power(g, k, p);
	b = mul(power(y, k, p), m, p);
	cout << "Шифротекст (a, b): " << a << ", " << b << endl;
	m1 = mul(b, power(a, p - 1 - x, p), p);
	cout << "Расшифрованный вариант: " << m1;
}

void var1()
{
	int p = 17, q = 5, eiler, e = 3, n, m1 = 10, m2, c, d, s;
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	n = p * q;
	eiler = (p - 1) * (q - 1);
	cout << "Произведение:" << n << endl;
	cout << "Функция Эйлера: " << eiler << endl;
	cout << "Открытая экспонента: " << e << endl;
	/* d = power(e, -1, eiler); */
	d = 43;
	cout << "Секретная экспонента: " << d << endl;
	cout << "Открытый ключ: {" << e << ", " << n << "}" << endl;
	cout << "Закрытый ключ: {" << d << ", " << n << "}" << endl << endl;
	cout << "Число для зашифровки: " << m1 << endl;
	c = power(m1, e, n);
	cout << "Шифротекст: " << c << endl;
	cout << "Расшифровка: " << power(c, d, n) << endl; // power c d n
	s = power(m1, d, n); // power m1 d n
	m2 = power(s, e, n); // power s e n
	if (m1 == m2)
	{
		cout << "Подпись правильная!" << endl;
	}
	else
	{
		cout << "Подпись некорректная" << endl;
	}
}


int main() {
	setlocale(LC_ALL, "rus");
	int numb;
	do {
		cout << "\n1 - RSA" << endl;
		cout << "2 - Деффи-Хеллман" << endl;
		cout << "3 - Эля-Гамаль" << endl;
		cout << "4 - lab 5" << endl;
		cout << "5 - End" << endl;
		cin >> numb;

		switch(numb) {
		case 1: rsa(); break;
		case 2: deffieHel(); break;
		case 3: Algamal(); break;
		case 4: var1(); break;
		case 5: break;
		}
	} while (numb != 5);
}