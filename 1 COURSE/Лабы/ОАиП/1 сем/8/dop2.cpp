#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "russian");
    int i, n, a, last = 0;
    cout << "Введите n: ";
     cin >> n;
    cout << "Введите последовательность целых чисел: " << endl;
    for (i = 1; i <= n; i++) {
        cin >> a;
        if (a < 0) {
            last = i;
        }
    }
    cout << "Номер последнего отрицательного элемента последовательности: " << last;
    return 0;
}