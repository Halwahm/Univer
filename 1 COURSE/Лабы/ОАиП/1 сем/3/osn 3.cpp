#include <iostream>
#include <iomanip>

using namespace std;

int main () {

    setlocale(LC_CTYPE, "Russian");
    char c, probel;
    probel = ' '; 

    cout << "Введите символ ";
    cin >> c;

    cout << setw((6)) << setfill(probel) << probel;
    cout << setw((1)) << setfill(c) << c;
    cout << endl;

    cout << setw((5)) << setfill(probel) << probel;
    cout << setw((3)) << setfill(c) << c;
    cout << endl;
   
    cout << setw((4)) << setfill(probel) << probel;
    cout << setw((5)) << setfill(c) << c;
    cout << endl;


    cout << setw((3)) << setfill(probel) << probel;
    cout << setw((7)) << setfill(c) << c;
    cout << endl;

    cout << setw((4)) << setfill(probel) << probel;
    cout << setw((5)) << setfill(c) << c;
    cout << endl;

    cout << setw((5)) << setfill(probel) << probel;
    cout << setw((3)) << setfill(c) << c;
    cout << endl;

    cout << setw((6)) << setfill(probel) << probel;
    cout << setw((1)) << setfill(c) << c;
    cout << endl;
    
   /* int arr[7] = {1, 3, 5, 6, 5, 3, 1};
    
    for (int i = 0; i <= 6; i++) {
        cout << setw(7 - arr[i]) << setfill(probel) << probel; 
        cout << setw(arr[i] * 2) << setfill(c) << c;
        cout << endl;
    } 
   
    */

    return 0;
}


