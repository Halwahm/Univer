#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

void v14c1();
void v14c2();
void dop1();
void dop2();
void dop3();

int main()
{
	setlocale(LC_CTYPE, "Russian");

	v14c1();
	v14c2();
    dop1();
    dop2();
    dop3();
	return 0;
}

void v14c1()
{
    const short m = 2, n = 5;
    int mas[n][n] = {}, mass[n][n] = {};
    for (short i = 0; i < n; i++)
    {
        for (short l = 0; l < n; l++) {
            mass[i][l] = mas[i][l] = rand() % 10;

        }
    }
    for (short i = 0; i < n; i++)
    {
        mass[i][m] = mas[m][i];
        mass[m][i] = mas[i][m];
    }
    cout << "1------------------";
    cout << endl;
    for (short i = 0; i < n; i++)
    {
        for (short l = 0; l < n; l++) {
            cout << mas[i][l] << " ";
        }
        cout << endl;
    }
    cout << "3------------------";
    cout << endl;
    for (short i = 0; i < n; i++)
    {
        for (short l = 0; l < n; l++) {
            cout << mass[i][l] << " ";
        }
        cout << endl;
    }
}

void v14c2()
{
    cout << "-------------------------------------------------" << endl;
    int mas[4][4] =
    {
        {4,0,28,2},
        {6,0,-6,0},
        {0,0,0,0},
        {8,9,4,1}
    };
    short i, j, k = 0, n = 0;
    for (i = 0; i < 4; i++) 
    {
        for (j = 0; j < 4; j++) 
        {
            if (mas[i][j] == 0) 
                k++;
        }
        if (k == 4) 
            n = i;
    }
    for (j = 0; j < 4; j++) 
    {
        mas[j][n] = mas[j][n] / 2;
    }
    for (i = 0; i < 4; i++) 
    {
        for (j = 0; j < 4; j++)
            cout << "Массив: " << mas[i][j] << endl;

        cout << endl;
    }
}

void dop1()
{
    cout << "-------------------------------------------------" << endl;
    const short n = 2, m = 2 * n - 1;
    short p, q, mass = 0;
    int a[2 * n][2 * n] = { 0 }, b[2 * n][2 * n] = { 0 };
    for (short i = 0; i < 2 * n; i++)
    {
        for (short l = 0; l < 2 * n; l++) {
            a[i][l] = rand() % 100;
        }

    }
    cout << endl;

    for (short i = 0; i < 2 * n; i++)
    {
        for (short l = 0; l < 2 * n; l++) {
            cout << a[i][l] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (short i = 0; i < 2 * n; i++)
    {
        for (short l = 0; l < 2 * n; l++) 
        {

            if (i < n && l < n)(b[i + 2][l + 2] = a[i][l]);
            if (i < 2 * n && l < 2 * n && i > n - 1 && l > n - 1)(b[i - 2][l - 2] = a[i][l]);
            if (l < 2 * n && i < n && l > n - 1)(b[i + 2][l - 2] = a[i][l]);
            if (i < 2 * n && i > n - 1 && l < n)(b[i - 2][l + 2] = a[i][l]);
        }
    }
    for (short i = 0; i < 2 * n; i++)
    {
        for (short l = 0; l < 2 * n; l++) 
        {
            cout << b[i][l] << " ";
        }
        cout << endl;
    }
    cout << endl;

}


void dop2()
{
    cout << "-------------------------------------------------" << endl;
    const int n = 5;
    int sq[n][n] = { 0 }, a, i, j;
    for (i = 0; i < n; i++) //заполнение массива с заданным свойством
    {
        a = i + 1;
        for (j = 0; j < n; j++)
        {
            sq[i][j] = a;
            a++;
            if (a > n)
                a = 1;
        }
    }
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++)
            cout << sq[i][j] << " ";
        cout << endl;
    }
}

void dop3()
{
    cout << "-------------------------------------------------" << endl;
    short n, i, j;
    cout << "Введите кол-во строк матрицы ";
    cin >> n;
    float** arr = new float* [n];
    float max = 0;
    short i_max, j_max, count;
    
    for (i = 0; i < n; ++i)
    {
        arr[i] = new float[n];
        for (j = 0; j < n; ++j)
        {
            cin >> arr[i][j];
            if (((!i) && (!j)) || (arr[i][j] > max))
            {
                max = arr[i][j];
                i_max = i;
                j_max = j;
            }
        }
    }
    arr[i_max][j_max] = arr[0][0];
    arr[0][0] = max;
    for (count = 1; count < n; count++)
    {
        max = arr[0][1];
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (((i != j) || ((i >= count) && (j >= count))) && (arr[i][j] > max))
                {
                    max = arr[i][j];
                    i_max = i;
                    j_max = j;
                }
        arr[i_max][j_max] = arr[count][count];
        arr[count][count] = max;
    }
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
            cout << setw(5) << arr[i][j];
        cout << endl;
    }
}