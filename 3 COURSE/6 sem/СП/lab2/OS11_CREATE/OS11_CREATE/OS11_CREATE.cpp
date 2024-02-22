// HT-Storage Created filename=xxxxx, snapshotinterval=xx  capacity = xxxx, maxkeylength = xxx, maxdatalength = xxx

#pragma comment(lib, "D:\\6sem\\SP\\Labs\\LAB03\\OS11_CREATE\\OS11_CREATE\\OS11HTAPI.lib")

#include <iostream>
#include "HT.h"

using namespace std;

bool isNum(char *);

int main(int argc, char * argv[])
{

	setlocale(LC_ALL, "ru");

	if (argc != 6) // + 1 параметр как имя самой программы
	{
		cout << endl << "ошибочное число параметров командной строки: " << endl << endl;
		cout << "пример: OS11_CREATE.exe filename snapshotinterval capacity maxkeylength maxdatalength";
		return -1;
	}

	if (!isNum(argv[2]) || !isNum(argv[3]) || !isNum(argv[4]) || !isNum(argv[5]))
	{
		cout << endl << "нарушение формата параметра командной строки - обнаружено нечисловое значение" << endl;
		return -1;
	}


	HTHANDLE* ht = NULL;

	try
	{
		ht = Create(atoi(argv[3]), atoi(argv[2]), atoi(argv[4]), atoi(argv[5]), argv[1]);
		if (ht != NULL)
			cout << "HT-Storage Created filename= " << argv[1] << ", snapshotinterval = " << argv[2] << ", capacity = " << argv[3] << ", maxkeylength = " << argv[4] << ", maxdatalength = " << argv[5];
		else throw "ошибка создания экземпляра хранилища";

		char errorInfo[255] = "";
	
		if (!Close(ht, errorInfo)) throw "ошибка закрытия экземпляра хранилища";

	}
	catch (char* msg)
	{
		cout << msg << endl;
	}
}

bool isNum(char * param)
{
	bool isdig = true;

	for (unsigned int i = 0; i < strlen(param); i++)
	{
		if (!isdigit(param[i]))
		{
			isdig = false;
			break;
		}
	}

	return isdig;
}
