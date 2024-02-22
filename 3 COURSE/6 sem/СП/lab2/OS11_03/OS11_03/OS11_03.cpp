#pragma comment(lib, "D:\\6sem\\SP\\Labs\\LAB03\\OS11_03\\OS11_03\\OS11HTAPI.lib")

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "HT.h"

using namespace std;

char* getRandomKey(char*, int);
char* getPseudoRandomKey7(char* buff_for_key);
char* getRandomKey_Test(char*, int);
bool LoggInfo(char *);

// поддержка управления стартом хранилища

const char hMutexStartName[] = "Local\\HTFMAP_STARTED_MUTEX";

const char HTFileName[] = "D:\\6sem\\SP\\Labs\\LAB03\\temp\\HT.dat";

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL)); // для генерации рандомных ключей

	HTHANDLE* ht = NULL;
	HANDLE hMutexStart = NULL;

	try
	{
		char errorInfo[255] = "";

		// проверим, что хранилище стартовано
		if ((hMutexStart = OpenMutex(NULL, false, hMutexStartName)) == NULL && GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			cout << endl << endl << "хранилище не стартовано - стартуйте хранилище для работы с ним" << endl;
			return 1;
		}
		else CloseHandle(hMutexStart);

		ht = Open(HTFileName, errorInfo);

		// размещаем массив для случайных значений ключей
		const int keys_QTT = 50;
		char ** Keys = new char *[keys_QTT];
		for (int i = 0; i < keys_QTT; i++) Keys[i] = new char[ht->htc.MaxKeyLength];

		// заполняем случайными значениями ключей
		for (int i = 0; i < keys_QTT; i++)
		{
			ZeroMemory(Keys[i], ht->htc.MaxKeyLength);
			// getRandomKey(Keys[i], ht->htc.MaxKeyLength); !!! тут подменяем вызов
			getPseudoRandomKey7(Keys[i]);
		}

		while (true)
		{
			for (int i = 1; i <= keys_QTT; i++)
			{
				char infobuff[255] = "\nпопытка удаления из хранилища элемента с ключом ";
				strcat(infobuff, Keys[i-1]);
				cout << infobuff;
				LoggInfo(infobuff);

				if (Delete(ht, new Element(Keys[i-1], strlen(Keys[i-1]))))
				{
					strcpy(infobuff, " - успех");
				}
				else
				{
					strcpy(infobuff, " - неуспех: ");
					strcat(infobuff, ht->LastErrorMessage);
				}

				cout << infobuff;
				LoggInfo(infobuff);

				Sleep(1000); // засыпаем на 1 сек
			}
		}

		// выполняет сохранение образа и завершает работу 
		// if (!Close(ht, errorInfo)) throw "ошибка закрытия экземпляра хранилища"; - приложение по условию задачи будет выполняться нелимитировано с завершением работы по нажатию Сtrl+C

	}
	catch (char* msg)
	{
		cout << msg << endl;
	}

}

char* getRandomKey(char* buff_for_key, int maxkeylength)
{
	// генерирует случайный ключ, принимает параметром адрес буфера для размещения результата - его же и возвращает параметром (NULL при ошибке)

	const int ENG_ALPHABET_LEN = 26; //мощность английского алфавита
	unsigned char EngAlphabet[ENG_ALPHABET_LEN + 1] = "abcdefghijklmnopqrstuvwxyz";

	char* result = buff_for_key;

	try
	{
		for (int i = 0; i < maxkeylength - 1; i++)
		{
			buff_for_key[i] = EngAlphabet[rand() % ENG_ALPHABET_LEN];
		}
	}
	catch (char* msg)
	{
		cout << msg << endl;
		result = NULL;
	}
	return result;
}


char* getPseudoRandomKey7(char* buff_for_key)
{
	char* result = buff_for_key;
	static int entrycount = 0; // счетчик вызова данной функции

	try
	{
		switch (++entrycount)
		{
		case 1:
		{
			strcpy(buff_for_key, "lugrzq");
			break;
		}
		case 2:
		{
			strcpy(buff_for_key, "vuaihc");
			break;
		}
		case 3:
		{
			strcpy(buff_for_key, "sfbvjd");
			break;
		}
		case 4:
		{
			strcpy(buff_for_key, "pnhhgi");
			break;
		}
		case 5:
		{
			strcpy(buff_for_key, "ziymcx");
			break;
		}
		case 6:
		{
			strcpy(buff_for_key, "zcrgnv");
			break;
		}
		case 7:
		{
			strcpy(buff_for_key, "gjvpms");
			break;
		}
		case 8:
		{
			strcpy(buff_for_key, "vuifip");
			break;
		}
		case 9:
		{
			strcpy(buff_for_key, "vqboby");
			break;
		}
		case 10:
		{
			strcpy(buff_for_key, "drljkx");
			break;
		}

		case 11:
		{
			strcpy(buff_for_key, "rfqhyt");
			break;
		}
		case 12:
		{
			strcpy(buff_for_key, "zmyrju");
			break;
		}
		case 13:
		{
			strcpy(buff_for_key, "uzlybv");
			break;
		}
		case 14:
		{
			strcpy(buff_for_key, "ycmgwv");
			break;
		}
		case 15:
		{
			strcpy(buff_for_key, "cfnwza");
			break;
		}
		case 16:
		{
			strcpy(buff_for_key, "stggtd");
			break;
		}
		case 17:
		{
			strcpy(buff_for_key, "foasre");
			break;
		}
		case 18:
		{
			strcpy(buff_for_key, "xazeii");
			break;
		}
		case 19:
		{
			strcpy(buff_for_key, "ptbiiq");
			break;
		}
		case 20:
		{
			strcpy(buff_for_key, "nxkoao");
			break;
		}

		case 21:
		{
			strcpy(buff_for_key, "lhhjqj");
			break;
		}
		case 22:
		{
			strcpy(buff_for_key, "cnxjme");
			break;
		}
		case 23:
		{
			strcpy(buff_for_key, "isvisn");
			break;
		}
		case 24:
		{
			strcpy(buff_for_key, "qkmdcw");
			break;
		}
		case 25:
		{
			strcpy(buff_for_key, "pnsnmx");
			break;
		}
		case 26:
		{
			strcpy(buff_for_key, "yeyyhy");
			break;
		}
		case 27:
		{
			strcpy(buff_for_key, "yzyyyz");
			break;
		}
		case 28:
		{
			strcpy(buff_for_key, "odevse");
			break;
		}
		case 29:
		{
			strcpy(buff_for_key, "bbrfeh");
			break;
		}
		case 30:
		{
			strcpy(buff_for_key, "dfsxld");
			break;
		}

		case 31:
		{
			strcpy(buff_for_key, "zaadpf");
			break;
		}
		case 32:
		{
			strcpy(buff_for_key, "yfzchc");
			break;
		}
		case 33:
		{
			strcpy(buff_for_key, "xerqbh");
			break;
		}
		case 34:
		{
			strcpy(buff_for_key, "wzlwkp");
			break;
		}
		case 35:
		{
			strcpy(buff_for_key, "jpukev");
			break;
		}
		case 36:
		{
			strcpy(buff_for_key, "gtuevq");
			break;
		}
		case 37:
		{
			strcpy(buff_for_key, "oxexvk");
			break;
		}
		case 38:
		{
			strcpy(buff_for_key, "etrjxk");
			break;
		}
		case 39:
		{
			strcpy(buff_for_key, "khaqxh");
			break;
		}
		case 40:
		{
			strcpy(buff_for_key, "tpzsoa");
			break;
		}

		case 41:
		{
			strcpy(buff_for_key, "uvysvx");
			break;
		}
		case 42:
		{
			strcpy(buff_for_key, "hpzcpe");
			break;
		}
		case 43:
		{
			strcpy(buff_for_key, "boffmu");
			break;
		}
		case 44:
		{
			strcpy(buff_for_key, "eghvkk");
			break;
		}
		case 45:
		{
			strcpy(buff_for_key, "vklglg");
			break;
		}
		case 46:
		{
			strcpy(buff_for_key, "jwlnye");
			break;
		}
		case 47:
		{
			strcpy(buff_for_key, "lmmxuv");
			break;
		}
		case 48:
		{
			strcpy(buff_for_key, "gtkkgp");
			break;
		}
		case 49:
		{
			strcpy(buff_for_key, "gfkrfi");
			break;
		}
		case 50:
		{
			strcpy(buff_for_key, "eosmzb");
			break;
		}
		default: break;

		}
	}
	catch (char* msg)
	{
		cout << msg << endl;
		result = NULL;
	}
	return result;
}

char* getRandomKey_Test(char* buff_for_key, int maxkeylength)
{
	// генерирует тестовый ключ, принимает параметром адрес буфера для размещения результата - его же и возвращает параметром (NULL при ошибке)

	char* result = buff_for_key;

	try
	{
		for (int i = 0; i < maxkeylength - 1; i++)
		{
			buff_for_key[i] = 'x';
		}
	}
	catch (char* msg)
	{
		cout << msg << endl;
		result = NULL;
	}
	return result;
}


bool LoggInfo(char * infostr)
{
	bool result = true;
	HANDLE logfile = NULL;

	try
	{
		logfile = CreateFile("D:\\6sem\\SP\\Labs\\LAB03\\temp\\OS11_03.log",
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (logfile == INVALID_HANDLE_VALUE)
		{
			throw "ошибка создания или открытия файла лога";
		}

		if (SetFilePointer(
			logfile,
			0,
			NULL,
			FILE_END) == INVALID_SET_FILE_POINTER)
		{
			throw "ошибка позиционирования указателя в файле лога";
		}

		DWORD byteswritten = 0;

		if (!WriteFile(logfile, infostr, strlen(infostr), &byteswritten, NULL))
		{
			throw "ошибка записи в файл лога";
		}
	}
	catch (char* msg)
	{
		cout << msg << endl;
		result = false;
	}

	if (logfile != NULL) CloseHandle(logfile);

	return result;
}