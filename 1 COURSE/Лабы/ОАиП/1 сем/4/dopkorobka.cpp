#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "Russian");
    double a, b, c, r, s, t;
    cout << "Введите значение длины коробки : "; cin >> a;
    cout << "Введите значение ширины коробки : "; cin >> b;
    cout << "Введите значение высоты коробки : "; cin >> c;
    cout << "Введите значение длины посылки : "; cin >> r;
    cout << "Введите значение ширины посылки : "; cin >> s;
    cout << "Введите значение высоты посылки : "; cin >> t;
    if ((a <= r) and (b <= s) and (c <= t))
        cout << "Можно";
    else cout << "Нельзя";
    return 0;
}