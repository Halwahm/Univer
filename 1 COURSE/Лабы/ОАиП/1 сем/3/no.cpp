#include <iostream>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian"); // ����������� 
    float a, b, c, d;

    cin >> a;
    cout << "����� �������� " << a << endl;
    cin >> b;
    cout << "����� ����� " << b << endl;
    cin >> c;
    cout << "����� ��������� " << c << endl;

    d = (50 * a) + (100 * b) + (200 * c);

    cout << "� ������ ����� " << d << endl;

    return 0;
}