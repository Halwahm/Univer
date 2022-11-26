#include <iostream>
using namespace std;
void c14v1();
void c14v2();
void v4c1();
void v15c1();
void v6c1();

int main()
{
    setlocale(LC_CTYPE, "Russian");
    c14v1();
    c14v2();
    v4c1();
    v15c1();
    v6c1();
    return 0;
}

void c14v1() {
    int A, result = 0;;
    cout << "Введите число: ";
    cin >> A;
    char tmp[33];
    _itoa_s(A, tmp, 2);
    cout << "Число в двоичном виде: " << tmp << endl;
    for (int i = 4; i <= 10; i++)
    {
        if ((A >> i) & 1 == 1) {
            result++;
        }
    }
    cout << "Кол-во единиц равно " << result << endl;
}

void c14v2() {
    cout << "-----------------------------------------------------------------------------" << endl;
    char tmp[33];
    int A, B, n, m;
    cout << "Введите A: ", cin >> A;
    cout << "Введите B: ", cin >> B;
    cout << "Введите n: ", cin >> n;
    cout << "Введите m: ", cin >> m;
    _itoa_s(A, tmp, 2); cout << "Число A: " << tmp << endl;
    _itoa_s(B, tmp, 2); cout << "Число B: " << tmp << endl;
    B ^= 7 << m;
    B |= ((A & (7 << n)) >> n) << m;
    _itoa_s(B, tmp, 2); cout << "new B = " << tmp << endl;
}

void v4c1() {
    cout << "-----------------------------------------------------------------------------" << endl;
    int A; 
    char tmp[33];
    cout << "Введите число: ";
    cin >> A;
    _itoa_s(A, tmp, 2);
    cout << "Число в двоичном виде: " << tmp << endl;
    if ((A & 3) == 0)
        cout << "Число кратно 4" << endl;
    else
        cout << "Число не кратно 4" << endl;
}

void v15c1() {
    cout << "-----------------------------------------------------------------------------" << endl;
    int chislo;
    char tmp[33];
    cout << "Введите число: ";
    cin >> chislo;
    _itoa_s(chislo, tmp, 2);
    cout << "Число в двоичной системе счисления: " << tmp << endl;
    if ((chislo & 1) == 0)
        cout << "Число кратно 2" << endl;
    else
        cout << "Число не кратно 2" << endl;
}

void v6c1() {
    cout << "-----------------------------------------------------------------------------" << endl;
    int A, mask = 0xAA; char tmp[33]; //0xAA - 10101010
    cout << "Введите число А, не более 512: " << endl;
    cin >> A;
    _itoa_s(A, tmp, 2);
    cout << "Число А: " << tmp << endl;
    _itoa_s(mask, tmp, 2);
    cout << "Маска для А: " << tmp << endl;
    _itoa_s(A | mask, tmp, 2);
    cout << "Результат: " << tmp << endl << endl;
}