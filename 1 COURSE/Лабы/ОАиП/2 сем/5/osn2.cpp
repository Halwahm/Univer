/*#include <iostream>  
#include<fstream>

# define size 100  

using namespace std;

void enter_new();
void out();
void search();

//�������. ���� �������� ������� � ������������: �������� ������ �������, ������������ ������, 
//��������� ���������; �����, �������� ��� �����, ���� �����, ���� ��������. 
//����� ������� �� ������������.

union forLombard
{
	char str[20];
	int limb;
};

struct Lombard
{
	forLombard name;
	forLombard surname;
	forLombard middleName;
	forLombard date_of_birthday;
	forLombard place_of_live;
	forLombard name_of_product;
	forLombard sum;
	forLombard sum_of_client;
	forLombard date_of_issue;
	forLombard shelfLife;
};

Lombard base_of_lombard[size];
int current_size = 0; int choice;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "������� �����:" << endl;
	cout << "1-��� ����� ������" << endl;
	cout << "2-��� ������ ������" << endl;
	cout << "3-��� ������ ����������" << endl;
	cout << "4-��� ������" << endl;
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1:  enter_new();	break;
		case 2:  out();  break;
		case 3:  search();	break;
		}
	} while (choice != 4);
}
void enter_new()
{
	cout << "���� ����������" << endl;
	if (current_size < size)
	{
		cout << "������ �����  ";
		cout << current_size + 1;
		cout << "\n";
		cout << "                     " << "������ �������" << "\n";
		cout << endl << "�������" << endl;
		cin >> base_of_lombard[current_size].name.str;
		cout << "���" << endl;
		cin >> base_of_lombard[current_size].surname.str;
		cout << "��������" << endl;
		cin >> base_of_lombard[current_size].middleName.str;
		cout << "���� ��������" << endl;
		cin >> base_of_lombard[current_size].date_of_birthday.str;
		cout << "����� ����������" << endl;
		cin >> base_of_lombard[current_size].place_of_live.str;
		cout << "                     " << "���������� � ������" << "\n";
		cout << "������������ ������" << endl;
		cin >> base_of_lombard[current_size].name_of_product.str;
		cout << "��������� ���������" << endl;
		cin >> base_of_lombard[current_size].sum.limb;
		cout << "����� ��� �����" << endl;
		cin >> base_of_lombard[current_size].sum_of_client.limb;
		cout << "���� �����" << endl;
		cin >> base_of_lombard[current_size].date_of_issue.str;
		cout << "���� ��������" << endl;
		cin >> base_of_lombard[current_size].shelfLife.str;
		current_size++;

	}
	else
		cout << "������� ������������ ���-�� �����";
	cout << "��� ������?" << endl;
	cin >> choice;
}
void out()
{
	int sw, n;
	cout << "1-������� 1 ������" << endl;
	cout << "2-������� ��� ������" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "����� ��������� ������: " << endl;
		cin >> n;
		cout << endl;
		cout << "                     " << "������ �������" << "\n";
		cout << "�������:";
		cout << base_of_lombard[n - 1].surname.str;
		cout << endl;
		cout << "���:";
		cout << base_of_lombard[n - 1].name.str;
		cout << endl;
		cout << "��������:";
		cout << base_of_lombard[n - 1].middleName.str;
		cout << endl;
		cout << "���� ��������:";
		cout << base_of_lombard[n - 1].date_of_birthday.str;
		cout << endl;
		cout << "����� ����������:";
		cout << base_of_lombard[n - 1].place_of_live.str;
		cout << endl;
		cout << "                     " << "���������� � ������" << "\n";
		cout << "������������ ������:";
		cout << base_of_lombard[n - 1].name_of_product.str;
		cout << endl;
		cout << "��������� ���������:";
		cout << base_of_lombard[n - 1].sum.limb;
		cout << endl;
		cout << "����� ��� �����:";
		cout << base_of_lombard[n - 1].sum_of_client.limb;
		cout << endl;
		cout << "���� �����:";
		cout << base_of_lombard[n - 1].date_of_issue.str;
		cout << endl;
		cout << "���� ��������:";
		cout << base_of_lombard[n - 1].shelfLife.str;
		cout << endl;
	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "                     " << "������ �������" << "\n";
			cout << "�������:";
			cout << base_of_lombard[i].surname.str;
			cout << endl;
			cout << "���:";
			cout << base_of_lombard[i].name.str;
			cout << endl;
			cout << "��������:";
			cout << base_of_lombard[i].middleName.str;
			cout << endl;
			cout << "���� ��������:";
			cout << base_of_lombard[i].date_of_birthday.str;
			cout << endl;
			cout << "����� ����������:";
			cout << base_of_lombard[i].place_of_live.str;
			cout << endl;
			cout << "                     " << "���������� � ������" << "\n";
			cout << "������������ ������:";
			cout << base_of_lombard[i].name_of_product.str;
			cout << endl;
			cout << "��������� ���������:";
			cout << base_of_lombard[i].sum.limb;
			cout << endl;
			cout << "����� ��� �����:";
			cout << base_of_lombard[i].sum_of_client.limb;
			cout << endl;
			cout << "���� �����:";
			cout << base_of_lombard[i].date_of_issue.str;
			cout << endl;
			cout << "���� ��������:";
			cout << base_of_lombard[i].shelfLife.str;
			cout << endl;

		}
	}
	cout << "��� ������?" << endl;
	cin >> choice;
}
void search()
{
	char name[16];
	cout << "������� ������������ ������:" << "\n";
	cin >> name;
	for (int z = 0; z < current_size; z++)
	{
		if (strcmp(name, base_of_lombard[z].name_of_product.str) == 0)
		{
			cout << " " << "\n������ �������: " << "\n\n";
			cout << "�������:";
			cout << base_of_lombard[z].surname.str;
			cout << endl;
			cout << "���:";
			cout << base_of_lombard[z].name.str;
			cout << endl;
			cout << "��������:";
			cout << base_of_lombard[z].middleName.str;
			cout << endl;
			cout << "���� ��������:";
			cout << base_of_lombard[z].date_of_birthday.str;
			cout << endl;
			cout << "����� ����������:";
			cout << base_of_lombard[z].place_of_live.str;
			cout << endl;
			cout << " " << "\n���������� � ������: " << "\n\n";
			cout << "������������ ������:";
			cout << base_of_lombard[z].name_of_product.str;
			cout << endl;
			cout << "��������� ���������:";
			cout << base_of_lombard[z].sum.limb;
			cout << endl;
			cout << "����� ��� �����:";
			cout << base_of_lombard[z].sum_of_client.limb;
			cout << endl;
			cout << "���� �����:";
			cout << base_of_lombard[z].date_of_issue.str;
			cout << endl;
			cout << "���� ��������:";
			cout << base_of_lombard[z].shelfLife.str;
			cout << endl;

		}
	}
	cout << "��� ������?" << endl;
	cin >> choice;
}*/