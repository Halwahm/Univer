#include <iostream>

using namespace std;

void v14c1();
void v14c2();
void task2_16();
void task1_16();
void task1_10();

int main()
{
    setlocale(LC_CTYPE, "Russian");
    v14c1();
	v14c2();
    task2_16();
    task1_16();
    task1_10();
    return 0;
}

void v14c1()
{
	// В одномерном массиве, состоящем из n вещественных элементов, вычислить минимальный 
	// элемент массива и сумму модулей элементов массива, расположенных после первого отрицательного эле-мента.
	short i, min = 0, minind = 0, sum = 0;
	int n;
	cout << "Введите кол-во элементов: ";
	cin >> n;
	int* mas = new int[n];
	cout << "Введите " << n << " элементов" << endl;
	for (i = 0; i < n; i++)
		cin >> mas[i];

	min = mas[0];

	for (i = 0; i < n; i++)
	{
		if (min > mas[i])
		{
			min = mas[i];
			minind = i;

		}
	}
	cout << "min = " << min << endl;

	short first = 0;
	for (i = 0; i < n; i++)
	{
		if (mas[i] < 0) {
			first = i;
			break;
		}
	}
	for (i = first + 1; i < n; i++)
	{
		sum += abs(mas[i]);
	}
	cout << "SUM = " << sum;
}

void v14c2()
{
	//Написать программу, определяющую есть ли во введенном с клавиатуры тексте слово "БГТУ".
	cout << endl << "-------------------------------------------------" << endl;
	short i, j, token = 0;
	char s[5];
	cout << "Введите БГТУ: ";
	gets_s(s);
	cout << endl;
	char a[100];
	cout << "Введите текст: ";
	gets_s(a);

    for (i = 0; i < strlen(a) - 3; i++)
    {
        if ((a[i] == s[0]) and (a[i + 1] == s[1]) and (a[i + 2] == s[2]) and (a[i + 3] == s[3]))
            cout << endl << "Есть такое слово.";
    }
}

void task2_16()
{
    cout << endl << "-------------------------------------------------" << endl;
    //Определить самое короткое и самое длинное слово в строке.
    short i, n, probel = 0, kolich = 0, minslovo = 1000, maxslovo = 0, max = 0, min = 1000;
    char s[256], ns[256];
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

void task1_16()
{
    cout << endl << "-------------------------------------------------" << endl;
    //Задан массив A из n чисел. Подсчитать, сколько раз встречается в нем максимальное число.
    int array[1000];
    short i, max, n, token = 0;

    cout << "Введите размер массива: ";
    cin >> n;

    for (i = 0; i < n; i++)
    {
        cout << "array[" << i + 1 << "]" "= ";
        cin >> array[i];
    }

    max = array[0];

    for (i = 0; i < n; i++)
    {
        if (max < array[i])
        {
            max = array[i];
        }
    }

    for (i = 0; i < n; i++)
    {
        if (array[i] == max)
            token++;
    }

    cout << "Max = " << max << endl;
    cout << "Повторяется " << token << " раз(а)" << endl;
}

void task1_10()
{
    //Дан двумерный массив, состоящий из N строк и М столбцов, а также число k. 
    //Найти столбец, содержащий это число.
    cout << endl << "-------------------------------------------------" << endl;
    const short n = 5, m = 5;
    short i, j, k, tok[m] = {}, ind = 0;
    cout << "Введите k: "; cin >> k;
    
    short arr[n][m] = {};
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
            if (arr[i][j] == k) 
            {
                tok[ind] = j;
                ind++;
            }
        }
        cout << endl;
    }

    cout << endl << "Столбец с k = " << k << "находится под номером: ";
    for ( i = 0; i < ind; i++)
    {
        cout << tok[i] + 1 << " ";
    }
}