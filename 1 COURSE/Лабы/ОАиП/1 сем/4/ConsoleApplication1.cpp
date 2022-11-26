#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");

    int a, b, c, sum = 0;

    cout << "Введите а " << endl; cin >> a;
    cout << "Введите b " << endl; cin >> b;
    cout << "Введите c " << endl; cin >> c;

    if (a % 5 == 0) {
        sum = sum + a;
    }
    if (b % 5 == 0) {
        sum = sum + b;
    }
    if (c % 5 == 0) {
        sum = sum + c;
    }
    if (sum == 0) {
        cout << "Error";
    }
    else 
    {
        cout << sum;
    }

    return 0;
}

