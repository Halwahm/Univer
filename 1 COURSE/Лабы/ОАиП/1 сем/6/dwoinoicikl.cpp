#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    double a = 1.5 * pow(10, 8), y, t, j = 6, i, b;
    

    for ( b = 2.4; b <= 3; b+=0.2) {
            do {
                cout << " i = "; cin >> i;
                cout << "b = " << b << endl;
               
                y = a / (b + exp(b)) / (1 + j * i);
                t = cos(y + 1) / sqrt(abs(-2 * j));

                cout << "y = " << y << endl;
                cout << "t = " << t << endl;
          

            } while (b < 3);
    }
    return 0;
}

