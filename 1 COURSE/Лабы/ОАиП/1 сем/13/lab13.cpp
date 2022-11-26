#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <string.h>

using namespace std;

void v14c1();
void v14c2();
void dop1();
void dop4();
void dop2();

int main()
{
	setlocale(LC_CTYPE, "Russian");
	v14c1();
	v14c2();
	dop1();
    dop4();
    dop2();
	return 0;
}

void v14c1()
{
    int i, n, probel = 0, kolich = 0, minslovo = 1000, maxslovo = 0, max = 0, min = 1000;
    char s[256], ns[256] ;
    cout << "Введите предложение" << endl; 
    gets_s(ns);
    s[0] = ' ';
    for (i = 0; ns[i]; i++)
    {
        s[i + 1] = ns[i];
        /*cout << s[i];*/
    }
    s[i + 1] = ' ';
    for (i = 1; s[i]; i++)
    {
        if (s[i] == ' ')
        {
            n = i;
            for (int l = probel; l < n; l++)
            {
                kolich++;
                //cout << s[l];
            }
            //cout << endl;
            if (kolich > max)
            {
                max = kolich;
                maxslovo = probel;
            }
            if (kolich < min)
            {
                min = kolich;
                minslovo = probel;
            }
            //cout << probel << " " << n << " " <<  " " << maxslovo << " " << minslovo;
            probel = n;
            kolich = 0;
            cout << endl;
        }
    }
    cout << "Самое короткое слово: ";
    for (i = minslovo + 1; s[i] != ' '; i++)
    {
        cout << s[i];
    }
    cout << endl;

    cout << "Самое длинное слово: ";
    for (i = maxslovo + 1; s[i] != ' '; i++)
    {
        cout << s[i];
    }
    cout << endl;
}

void v14c2()
{
    cout << "-------------------------------------------------";
    int i, n, probel = 0;
    char s[256];
    cout << endl << "Введите десятичные символы" << endl;
    gets_s(s);

    for (i = 0; s[i]; i++)
    {
        if (s[i] == ' ')
        {
            n = i;
            if (s[i - 1] % 2 == 0)
            {
                for (int l = probel; l < n; l++)
                {
                    cout << s[l];
                }
                cout << endl;
            }
            probel = n;
        }
    }
    cout << endl;
}

void dop1()
{
    cout << endl << "-------------------------------------------------";
    int i, n, probel = 0;
    char ns[256], ok[256], s[256];
    cout << endl << "Введите предложение" << endl;
    gets_s(ns);
    s[0] = ' ';
    for (i = 0; ns[i]; i++)
    {
        s[i + 1] = ns[i];
        /*cout << s[i];*/
    }
    s[i + 1] = ' ';

    cout << "Введите окончание" << endl;
    gets_s(ok);

    for (i = 0; s[i]; i++)
    {
        if (s[i] == ' ')
        {
            n = i;
            if (s[i - 1] == ok[1] or s[i - 2] == ok[0])
            {
                for (int l = probel; l < n; l++)
                {
                    cout << s[l];
                }
                cout << endl;
            }
            probel = n;
        }
    }
    cout << endl;
}

void dop4()
{
    cout << endl << "------------------------------------------------ - ";
    int i, n, probel = 0, token = 1;
    char s[256], ns[256];
    cout << endl << "Введите предложение" << endl;
    gets_s(ns);
    s[0] = ' ';
    for (i = 0; ns[i]; i++)
    {
        s[i + 1] = ns[i];
        /*cout << s[i];*/
    }
    s[i + 1] = ' ';
    for (i = 1; s[i]; i++)
    {
        if (s[i] == ' ')
        {
            n = i;
            token++;
            if ((token % 2) != 0)
            {
                for (int g = n - 1; g > probel; g--)
                {
                    
                    cout << s[g];
                }
                cout << " ";
            }
            probel = i;
        }
    }
}

void dop2()
{
    int i, j;
    short el1 = 0, el2 = 0, el3 = 0, el4 = 0;
    cout << endl << "-------------------------------------------------" << endl;
    char A[6][256] = { {"goad"}, {"nightoa"}, {"goatd"}, {"work"}, {"namedaog"}, {"beats"} }; //goad
    char s[5];
    cout << "Введите буквы: ";
        gets_s(s);
        for (i = 0; i < 6; i++) //пользуемся гибкостью цикла for: используем неявное преобразование в тип boolean (true/false)
        {
            for (j = 0; A[i][j]; j++)
            {
                if (A[i][j] == s[0])
                {
                    if (el1 == 0)
                    {
                        el1++;
                    }
                }
                if (A[i][j] == s[1])
                {
                    if (el2 == 0)
                    {
                        el2++;
                    }
                }
                if (A[i][j] == s[2])
                {
                    if (el3 == 0)
                    {
                        el3++;
                    }
                }
                if (A[i][j] == s[3])
                {
                    if (el4 == 0)
                    {
                        el4++;
                    }
                }
                if (el1 + el2 + el3 + el4 == 4)
                {
                    for (int z = 0; A[i][z]; z++)
                    {
                        cout << A[i][z];
                    }

                    el1 = 0;
                    el2 = 0;
                    el3 = 0;
                    el4 = 0;
                }
            } 
            cout << endl;
        }
}

