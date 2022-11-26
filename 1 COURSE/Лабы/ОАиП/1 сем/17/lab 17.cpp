#include <iostream>

using namespace std;

void task1_14();
void task2_14();
void task1_15();
void task1_5();
void task1_6();

int main()
{
    setlocale(LC_CTYPE, "Russian");
    task1_14();
    task2_14();
    task1_15();
    task1_5();
    task1_6();
    return 0;
}

void task1_14()
{
    //В одномерном массиве найти минимальный и максимальный элементы. Вычислить их разность.
    short i = 0, raz = 0,min = 1000, max = 0;
    short arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (i = 0; i < 10; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    for (i = 0; i < 10; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];        
        }
    }
    raz = max - min;
    cout << "Разность: " << raz << endl;
}

void task2_14()
{
    cout << "----------------------------------------------------" << endl;
    //Если в матрице имеется столбец, все элементы которого положительны, 
    //то знаки элементов предыдущего столбца изменить на противоположные.
    const short n = 3, m = 4;
    short arr[n][m] = {
        {1, 3, 4, -5},
        {2, 3, 4, 5},
        {-8, 2, -1, 4}
    }, newarr[n][m], ind[m];
    short i, j, count = 0, token = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (arr[j][i] < 0)
            {
                count = 1;
            }
        }
        if ((count != 1) and (i != 0))
        {
            ind[token] = i;
            token++;
        }
        count = 0;
    }
    cout << "=========" << endl;
    cout << "Положительный столбец: ";
    for (i = 0; i < token; i++)
    {
        cout << ind[i] + 1 << " ";
    }

    for (j = 0; j < token; j++)
    {
        for (i = 0; i < n; i++)
        {
            arr[i][ind[j] - 1] = arr[i][ind[j] - 1] * (-1);
        }
    }
    cout << endl << "=========" << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
    void task1_15()
    {
        cout << "----------------------------------------------------" << endl;
        //Дан одномерный массив. Определить, сколько отрицательных элементов находится 
        //после последнего минимального элемента.
        short arr[6] = { 1, 2, -7, -6, -5, 5 }, min = 100, indmin = 0, i, count = 0;
        for (i = 0; i < 6; i++)
        {
            cout << arr[i] << " " << endl;
            if (arr[i] < min)
            {
                min = arr[i];
                indmin = i;
            }
        }

        for (i = indmin + 1; i < 6; i++)
        {
            if (arr[i] < 0)
                count++;
        }
        cout << "Кол-во элементов: " << count << endl;
    }

    void task1_5()
    {
        cout << "----------------------------------------------------" << endl;
        //В одномерном массиве, содержащем 15 элементов, посчитать и вывести 
        //сумму всех четных элементов массива.
        short arr[15] = {}, i, sum = 0;

        cout << "Массив: " << endl;
        for (i = 0; i < 15; i++)
        {
            arr[i] = rand() % 10;
            cout << arr[i] << " ";
            if (i % 2 != 0)
                sum += arr[i];
        }
        cout << endl << "Сумма: " << sum << endl;
    }
    
    void task1_6()
    {
        cout << "----------------------------------------------------" << endl;
        //Найти сумму минимального и максимального элементов одномерного массива.
        short arr[10] = {}, i, sum = 0, max = 0, min = 110;

        cout << "Массив: " << endl;
        for (i = 0; i < 10; i++)
        {
            arr[i] = rand() % 10;
            cout << arr[i] << " ";
            if (arr[i] > max) max = arr[i];
            if (arr[i] < min) min = arr[i];
        }
        cout << endl << "Сумма: " << min + max;
    }