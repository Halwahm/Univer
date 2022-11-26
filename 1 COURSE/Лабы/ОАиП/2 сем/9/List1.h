#pragma once
using namespace std;
const unsigned int NAME_SIZE = 30;

struct Address
{
	char name[NAME_SIZE];
	char surname[NAME_SIZE];
	char parentname[NAME_SIZE];
	int month;
	int year;
	int day;
	int course;
	int group;
	float math;
	float OAIP;
	float English;
	float Yap;
	float Kyar;
	Address* next;
	Address* prev;
};
void insert(Address* e, Address** phead, Address** plast);
Address* setElement();
void outputList(Address** phead, Address** plast);
void studentOld(Address** phead, Address** plast);
void studentYoung(Address** phead, Address** plast);
void outputFirstCourse(Address** phead, Address** plast);
void outputSecondCourse(Address** phead, Address** plast);
void outputThirdCourse(Address** phead, Address** plast);
void outputFourthCourse(Address** phead, Address** plast);
void average(Address** phead, Address** plast);