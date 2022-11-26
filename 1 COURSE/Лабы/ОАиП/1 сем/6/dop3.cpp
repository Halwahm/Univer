#include <iostream>

using namespace std;


int main()
{
    setlocale(LC_CTYPE, "Russian");
    double p, q;
    int i;
    cout << " p = "; 
     cin >> p;
    cout << " q = "; 
     cin >> q;

    for (i = 0; p < q; i++)
    {
        p = p * 1.03;
    }
    cout << p << endl;
    cout << "Кол-во дней " << i;
    return 0;
}
