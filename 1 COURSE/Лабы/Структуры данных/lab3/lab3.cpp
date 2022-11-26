#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const short N = 3;

void undefined()
{
    /*Запись в файл чётных чисел*/

    char name_file[20];
    string str;
    cout << "Название файла: "; cin >> name_file;
    ofstream file(name_file, ios_base::out | ios_base::trunc);
    cout << "Введите число n: ";
    short n = 0;
    cin >> n;

    for (short i = 0; i < n + 1; i++)
    {
        if (i % 2 == 0)
        {
            file.open(name_file, ios::app);
            file << i << endl;
            file.close();
        }
    }
}

struct WUZ
{
    string name;
    string address;
    string contest;
    string payment;
    string specialties;
};

void ifile(WUZ students[])
{
    string strInf;
    ifstream file1("information.txt");
    while (file1)
    {
        getline(file1, strInf);
        cout << strInf << '\n';
    }
}

void deleteWUZ(WUZ students[])
{
    ofstream file("information.txt", ios_base::trunc);
}

void deletefile() {
    remove("information.txt");
}

void dop1() {
    char buff[50];
    ifstream fin("dop1.doc");
    fin.getline(buff, 50);
    fin.close();
    cout << buff << endl;
}

void dop2() {
    short k, num = 0, counter = 0;
    cout << "Введите, с какой строки копировать: (k + 3 строк будет скопировано)\n";
    cin >> k;
    short k1 = k + 3;
    string str;
    ifstream file1("fileMain1_1.txt");
    ofstream file2("fileMain1_2.txt");
    while (getline(file1, str))
    {
        if (num >= k && num <= k1)
        {
            file2 << str << '\n';
            for (int j = 0; j < 8; j++)
            {
                if (str[j] == 'a' || str[j] == 'o' || str[j] == 'e' || str[j] == 'y' || str[j] == 'u' || str[j] == 'i')
                    counter++;
            }
        }
        num++;
    }
    cout << counter << " гласных букв.\n";
}

void dop3() {
    short n1, n2, num = 0, counter = 0;
    string str;
    cout << "Введите, с какой строки копировать:\n";
    cin >> n1;
    cout << "Введите, до какой строки копировать:\n";
    cin >> n2;
    ifstream file1("file9_1_1.txt");
    ofstream file2("file9_1_2.txt");

    while (getline(file1, str))
    {
        if (num >= n1 && num <= n2)
        {
            if (str[0] == 'C' || str[0] == 'c')
            {
                file2 << str << '\n';
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] == ' ')
                    {
                        counter++;
                    }
                }
            }
        }
        num++;
    }
    cout << "В первой строке второго файла " << ++counter << " слова.\n";
}

int main()
{
    setlocale(LC_ALL, "RU");

    short choose;
    WUZ students[N];
    do {
        cout << "Выберите, что сделать:\n1 — создание файла с присваиванием названия;\n2 — чтение файла;"
            "\n3 — удаление содержимого файла; \n4 — удаление файла; \n5 - доп1; \n6 - доп2; \n7 - доп3;"
            "\n8 — выход из программы.\n";
        cin >> choose;
        switch (choose)
        {
        case 1: undefined(); break;
        case 2: ifile(students); break;
        case 3: deleteWUZ(students); break;
        case 4: deletefile(); break;
        case 5: dop1(); break;
        case 6: dop2(); break;
        case 7: dop3(); break;
        case 8: main(); break;
        }
    } while (choose != 8);
    return 0;
}