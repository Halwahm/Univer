#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    int i, kol = 0;
    int A[10] = { 4,4,4,4,9,0,1,7,8,7 };
    for (i = 0; i < 10; i++)
    {
        cout << "A[i] = " << A[i] << endl;
    }
    for (i = 1; i < 10; i++)
    {
        if (A[i - 1] == A[i])
        {
            kol++;
        }
        else
        {
            break;
        }
    }
    cout << "Hаибольшее число подряд идущих одинаковых элементов равно " << kol + 1;
    return 0;
}