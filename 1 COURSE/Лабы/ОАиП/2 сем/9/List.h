#pragma once
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct address
{
	char name[NAME_SIZE];
	char surname[NAME_SIZE];
	char parentname[NAME_SIZE];
	char type[NAME_SIZE];
	char number[NAME_SIZE];
	char sum[NAME_SIZE];
	char date[NAME_SIZE];
	address* next;
	address* prev;
};
void insert(address* e, address** phead, address** plast);
address* setElement();
void outputList(address** phead, address** plast);
void find(char name[NAME_SIZE], address** phead);
void countList(address** phead, address** plast);
void delAll(address** phead, address** plast);