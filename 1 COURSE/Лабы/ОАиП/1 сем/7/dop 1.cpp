#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "ressian");
    int i, b, b1, b2, b3;
     int arr [] = {11, 13, 17, 19, 23, 29, 31};
     for (i = 0; i < 7; i++) {
         b = arr[i] * arr[i];
         b1 = b / 100;
         b2 = (b % 100) / 10;
         b3 = b % 10;
         if (b1 != b2 && b1 != b3 && b2 != b3);
         cout << b << endl;
    }
     return 0;

}