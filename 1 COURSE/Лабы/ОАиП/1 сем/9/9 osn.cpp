#include <iostream>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");
    cout << "Метод трапеции: ";
    float s = 0, x = 0, h, a3 = 1, b3 = 4;
    int n = 200, i;
        x = a3;
        for (i = 1; i < n; i++) {
            h = (b3 - a3) / n;
            s += h * ((4 + pow(x, 4)) + (4 + pow(x + h, 4)) / 2);
            x += h;
            if (x > (b3 - h)) break;
        }
        cout << s << endl;

        cout << "Метод параболы: ";
        float s2, s1, k, z;
        int o;
        h = (b3 - a3) / (2 * n);
        x = a3 + 2 * h;
        s2 = 0;
        s1 = 0;
        k = 1;
        for (o = 1; o < 2 * n; o++) {
            s2 += (4 + pow(x, 4));   
            x += h;
            s1 += (4 + pow(x, 4));
            x += h;
            k += 1;
            if (k < n) break;
        }
        z = (h / 3) * (4 + pow(a3, 4)) + 4 * (4 + pow(a3 + h, 4)) + (4 * s1) + (2 * s2) + (4 + pow(b3, 4));
        cout << z << endl;

        cout << "Метод дихотомии: " << endl;
        float a, b, e = 0.0001;
        cout << "Введите a и b: " << endl;
         cin >> a >> b;
         do {
             x = (a + b) / 2;
             if (((pow(x, 3) + x - 2) * (pow(a, 3) + a - 2)) <= 0)
                 b = x;
             else a = x;
         } while (abs(a - b) > 2 * e);
         cout << x;
    return 0;
}

