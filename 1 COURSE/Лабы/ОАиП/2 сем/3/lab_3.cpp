#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void osn1() {
	/*Скопировать из файла FILE1 в файл FILE2 строки, начиная с к до к + 3.
    Подсчитать количество гласных букв в FILE2.*/

	    short k, num = 0, counter = 0;
		cout << "Введите, с какой строки копировать:\n";
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
		cout << "------------------------------------------------" << '\n';
}

void osn2() {
/* Скопировать из файла FILE1 в файл FILE2 строки, начиная с N до K.
Подсчитать количество согласных букв в файле FILE2.*/

	short n, k, num = 0, counter = 0;
	cout << "Введите, с какой строки копировать:\n";
	cin >> n;
	cout << "Введите, до какой строки копировать:\n";
	cin >> k;
	string str;
	ifstream file1("fileMain2_1_1.txt");
	ofstream file2("fileMain2_1_2.txt");
	while (getline(file1, str))
	{
		if (num >= n && num <= k)
		{
			file2 << str << '\n';
			for (int j = 0; j < 8; j++)
			{
				if (str[j] == 'q' || str[j] == 'w' || str[j] == 'r' || str[j] == 't' || str[j] == 'p' || str[j] == 's' || str[j] == 'd' || str[j] == 'f' ||
					str[j] == 'g' || str[j] == 'h' || str[j] == 'j' || str[j] == 'k' || str[j] == 'l' || str[j] == 'z' || str[j] == 'x' || str[j] == 'c' ||
					str[j] == 'v' || str[j] == 'b' || str[j] == 'n' || str[j] == 'm')
					counter++;
			}
		}
		num++;
	}
	cout << counter << " согласных букв.\n";
	cout << "------------------------------------------------" << '\n';
}

void dop1() {
	/*Скопировать в файл FILE2 только те строки из FILE1, которые
	начинаются с буквы «А».*/

	int k, num = 0, counter = 0;
	string str;
	ifstream file1("file2_1_1.txt");
	ofstream file2("file2_1_2.txt");
	while (getline(file1, str))
	{
		if(str[0] == 'a' || str[0] == 'A')
		{
			file2 << str << '\n';
		}
	}
 cout << "------------------------------------------------" << '\n';
}

void dop2() {
	/* Скопировать из файла FILE1 в файл FILE2 все строки, начинающиеся
на букву «С», расположенные между строками с номерами N1 и N2. Определить
количество слов в первой строке файла FILE2.*/
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
	cout << "------------------------------------------------" << '\n';
}

void dop3() {
	/*Ввести с клавиатуры строку символов, состоящую из цифр и слов,
разделенных пробелами, и записать ее в файл. Прочитать из файла данные,
вывести слова строки и записать их в другой файл.*/
	    char buff[50];
	    char str[50];
	    short countWordITF = 0;
	    short counterNumbers = 0;
	    short counterNumbers_1 = 0;
	    ofstream fout_1("t_3var1.txt");
	    cin.getline(str, 50);
	    fout_1 << str << '.' << '\n';
	    fout_1.close();
	    ifstream fin("t_3var1.txt");
	    fin.getline(buff, 50);
	    cout << buff << endl;
	    for (short i = 0; i < strlen(buff); i++)
	    {
	        if (buff[i] == ' ' || buff[i] == '.') {
	            countWordITF++;
	        }
	    }
	    fin.close();
	    ofstream fout_2("t_3var2.txt");
	    ifstream fin_1("t_3var1.txt");
	    for (short i = 0; i < countWordITF; i++)
	    {
	        fin_1 >> buff;
	        short buff_len = strlen(buff);
	        for (short j = 0; j < buff_len; j++) {
	            if (buff[j] == '1' || buff[j] == '2' || buff[j] == '3' || buff[j] == '4' || buff[j] == '5' || buff[j] == '6' || buff[j] == '7' || buff[j] == '8' || buff[j] == '9' || buff[j] == '0') {
	                counterNumbers++;
	            }
	        }
	        if (counterNumbers > 0) {
	            counterNumbers_1++;
	        }
	        else {
	            cout << buff << endl;
	            fout_2 << buff << " ";
	        }
	        counterNumbers = 0;
	    }
	    cout << "Наборов символов :  " << counterNumbers_1 << endl;
	    cout << "Количество слов :  " << countWordITF - counterNumbers_1 << endl;
	    fout_2.close();
	    fin_1.close();
	cout << "------------------------------------------------" << '\n';
}

void dop4() {
	short number;
	cout << "Введите задаваемое число: "; cin >> number;

	ifstream file1("F1.txt");
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	//osn1();
	//osn2();
	//dop1();
	//dop2();
	//dop3();
	dop4();
	return 0;
}