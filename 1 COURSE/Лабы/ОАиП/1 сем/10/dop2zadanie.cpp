#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    int i, kolvo = 0;
    int A[10] = { 4, 4, 3, 5, 5, 6, 3, 3, 0, 7 };
    for (i = 0; i < 10; i++)
    {
        cout << "A[i] = " << A[i] << endl;
    }
    for (i = 1; i <= 10; i++)
    {
        if (A[i - 1] == A[i]) {
            kolvo++;
        }
    }
    cout << "Количество пар: " << kolvo;
    return 0;
}