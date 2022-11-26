#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;


	/* 1. ��� ���� ������������ �����, ���������� �������� ���������� �������
�� �������, ������ ��������� ������� ����� �������� �������� ����������
�������� �������. ������� ����� ���� ��� �� ���������, ���������� k-�� (1) ������� �������� �������.*/
int osn1() {
	errno_t err;
	int columns = 4;
	    FILE* f;
	    err = fopen_s(&f, "matrix.txt", "w");
	    if (err != 0)
	    {
	        perror("���������� ������� ����\n");
	        return EXIT_FAILURE;
	    }
	    int Matrix[16] = { 2,7,12,-4,
	                       6,-45,0,13,
	                       96,43,-2,8,
	                       33,-5,63,-11 };
	    // ����� ������ �������
	    fprintf(f, "� ������� %d �������.\n============================\n", columns);
	    for (int j = 0; j < 16; j += 4)
	    {
	        for (int i = j; i < j + 4; i++)
	        {
	            fprintf(f, "%d\t", Matrix[i]);
	        }
	        fprintf(f, "\n", "\n");
	    }
	    fprintf(f, "\n============================\n");
	    // ����� ������ �������
		err = fopen_s(&f, "matrix_k.txt", "w");
		    if (err != 0)
		    {
		        perror("���������� ������� ����\n");
		        return EXIT_FAILURE;
		    }
			fprintf(f, "� ������� %d �������.\n============================\n", columns);
			    for (int i = 0; i < 16; i += 4)
			    {
			            fprintf(f, "%d\t", Matrix[i]);
			    }
			    fprintf(f, "============================\n");
			
			    printf("������ �������� � ���� matrix_k.txt\n");
			    fclose(f);
				return 0;
}


/*���������� ����� f � ����� �����. �������� ���� g, ������������ �� ����� f 
����������� ��������� ��������� ������ � ���� �� �����.*/
	int osn2() {
	errno_t err;
	FILE* f;
	err = fopen_s(&f, "fail_f.txt", "w");
	if (err != 0)
	{
		perror("���������� ������� ����\n");
		return EXIT_FAILURE;
	}
	int arr_1[7] = { 1, 2, 3, 0, 5, 1, 9 };
	fprintf(f, "������ �����\n============================\n");
	int arr_2[7] = {0,0,0,0,0,0,0};
	int n = 0, g = 0;
	for (int z = 0; z < 7; z++)
		fprintf(f, "%d\t", arr_1[z]);
	cout << "�������� � ���� fail_f" << endl;

	err = fopen_s(&f, "fail_g.txt", "w");
	if (err != 0)
	{
		perror("���������� ������� ����\n");
		return EXIT_FAILURE;
	}

	for (short i = 0; i < 7; i++)
	{
		if (arr_1[i] == 0 and g == 0)
		{
			cout << arr_1[i];
			fprintf(f, "%d\t", arr_1[i]);
			g++;
		}
		for (short j = 0; j < 7; j++) 
		{
			if (arr_1[i] == arr_2[j])
			{
				n++;
			}
		}
		if (!n)
		{
			cout << arr_1[i];
			fprintf(f, "%d\t", arr_1[i]);
		}
		arr_2[i] = arr_1[i];
		n = 0;
	}
	fclose(f);
	return 0;
}

/*������� ��������� ���� F1 �� �����, ��� �� 5 �����, � ��������
� ���� ����������. ����������� � ���� F2 ������ ������ �� F1, �������
���������� � �����.*/
int dop1() {
	FILE* F1;
	FILE* F2;
	char str[255];
	errno_t err;
	err = fopen_s(&F1, "f1_14.txt", "w");
	for (int i = 0; i < 6; i++)
	{
		printf("������  %d: \n", i + 1);
		gets_s(str);
		fputs(str, F1);
		fputs("\n", F1);
	}
	fclose(F1);
	err = fopen_s(&F1, "f1_14.txt", "r");
	err = fopen_s(&F2, "f2_14.txt", "w");

	while (fgets(str, 255, F1) != 0)
	{
		if (str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5'
			|| str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || str[0] == '0')
		{
			fputs(str, F2);
		}
	}
	fclose(F1);
	fclose(F2);
	return 0;
}

	/*2. ������� ��������� ���� F1 �� �����, ��� �� 6 �����, � ��������
� ���� ����������. ����������� � ���� F2 ������ �� ������ �� F1,
������� ������������� �������� ��. */
int dop2() {
	FILE* F1;
	FILE* F2;
	char str[255];
	errno_t err;
	err = fopen_s(&F1, "F1.txt", "w");
	for (int i = 0; i < 7; i++)
	{
		printf("������  %d: \n", i + 1);
		gets_s(str);
		fputs(str, F1);
		fputs("\n", F1);
	}
	fclose(F1);
	err = fopen_s(&F1, "F1.txt", "r");
	err = fopen_s(&F2, "F2.txt", "w");
	while (fgets(str, 255, F1) != NULL)
	{
		if (str[strlen(str) - 2] == 'A' || str[strlen(str) - 2] == 'a')
		{
			fputs(str, F2);
		}
	}
	fclose(F1);
	fclose(F2);
	return 0;
	}

	/*��� ���� ������������ �����, ���������� �������� ���������� �������
(�� �������), ������ ��������� ������� ����� �������� �������� ����������
�������� �������. ������� ����� ���� ��� �� ���������, ����������
����������������� �������.*/

int dop3() {
    int a; errno_t err, columns = 4;
    FILE* f;
    err = fopen_s(&f, "matrix.txt", "w");
    if (err != 0)
    {
        perror("���������� ������� ����\n");
        return EXIT_FAILURE;
    }
    int Matrix[16] = { 2,7,12,-4,
                     6,-45,0,13,
                     96,43,-2,8,
                     33,-5,63,-11 };
    // ����� ������ �������
    fprintf(f, "� ������� %d �������.\n============================\n", columns);
    for (int j = 0; j < 16; j += 4)
    {
        for (int i = j; i < j + 4; i++)
        {
            fprintf(f, "%d\t", Matrix[i]);
        }
        fprintf(f, "\n", "\n");
    }
    fprintf(f, "============================\n");
    // ����� ������ �������
    err = fopen_s(&f, "matrixT.txt", "w");
    if (err != 0)
    {
        perror("���������� ������� ����\n");
        return EXIT_FAILURE;
    }
    fprintf(f, "� ������� %d �������.\n============================\n", columns);
    for (int j = 0; j < 4; j++)
    {
        for (int i = j; i <= j + 12; i += 4)
        {
            fprintf(f, "%d\t", Matrix[i]);
        }
        fprintf(f, "\n", "\n");
    }
    fprintf(f, "============================\n");

    printf("������ �������� � ���� matrixT.txt\n");
    fclose(f);
	return 0;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	osn1();
	osn2();
	dop1();
	dop2();
	dop3();
	return 0;
}