#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "russian");
    int n, sum = 0, i, x;
    cout << "Введите n: ";
    cin >> n;
    i = 0;
    cout << "Введите числа: " << endl;
    while (i < n)
    {
        cin >> x;
        if (x % 2 == 0)
            sum += x;
        i++;
    }
    cout << "Сумма: " << sum;
    return 0;
}