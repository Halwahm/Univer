#include <iostream>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian"); // локализация 
    float a, b, c, d;

    cin >> a;
    cout << "Сбито самолётов " << a << endl;
    cin >> b;
    cout << "Сбито ракет " << b << endl;
    cin >> c;
    cout << "Сбито спутников " << c << endl;

    d = (50 * a) + (100 * b) + (200 * c);

    cout << "У игрока очков " << d << endl;

    return 0;
}