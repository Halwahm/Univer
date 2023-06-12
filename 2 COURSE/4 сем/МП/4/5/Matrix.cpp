#include "stdafx.h"
#include <cmath>
#include <memory.h>
#include <ctime>
#include <iostream>
#include "MultyMatrix.h" // ��������� ������ 

#define N 6
int main()
{
	clock_t t1 = 0;
	clock_t t2 = 0;
	clock_t	t3 = 0;
	clock_t t4 = 0;
	int Mc[N + 1] = { 100,15,20,43,70,71,41 }, Ms[N][N], r = 0, rd = 0;

	memset(Ms, 0, sizeof(int) * N * N);
	t1 = clock();
	r = OptimalM(1, N, N, Mc, OPTIMALM_PARM(Ms));
	t2 = clock();
	setlocale(LC_ALL, "rus");
	std::cout << std::endl;
	std::cout << std::endl << "-- ����������� ������ (����������� �������) " << std::endl;
	std::cout << std::endl << "����������� �����(���):  " << ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC) << std::endl;
	std::cout << std::endl << "����������� ������: ";
	for (int i = 1; i <= N; i++) std::cout << "(" << Mc[i - 1] << "," << Mc[i] << ") ";
	std::cout << std::endl << "����������� ���������� �������� ���������: " << r;
	std::cout << std::endl << std::endl << "������� S" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < N; j++)  std::cout << Ms[i][j] << "  ";
	}
	std::cout << std::endl;

	memset(Ms, 0, sizeof(int) * N * N);
	t3 = clock();
	rd = OptimalMD(N, Mc, OPTIMALM_PARM(Ms));
	t4 = clock();
	std::cout << std::endl
		<< "-- ����������� ������ (���������� ����������������) " << std::endl;
	std::cout << std::endl << "����������� �����(���):  " << ((double)(t4 - t3)) / ((double)CLOCKS_PER_SEC) << std::endl;
	std::cout << std::endl << "����������� ������: ";
	for (int i = 1; i <= N; i++)
		std::cout << "(" << Mc[i - 1] << "," << Mc[i] << ") ";
	std::cout << std::endl << "����������� ���������� �������� ���������: "
		<< rd;
	std::cout << std::endl << std::endl << "������� S" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < N; j++)  std::cout << Ms[i][j] << "  ";
	}
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}