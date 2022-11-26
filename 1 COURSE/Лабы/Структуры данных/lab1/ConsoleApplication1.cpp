//#include <iostream>
//#include <deque>
//#include <forward_list>
//#include <vector>
//#include <array>
//#include <list>
//
//using namespace std;
//
//void z1();
//void z2();
//void z3();
//void z4();
//void z5();
//void z6();
//void z7();
//void z8();
//void z9();
//void z10();
//void z13();
//void z12();
//void zz13();
//void dop2();
//void dop3();
//
//int main()
//{
//	setlocale(LC_CTYPE, "Russian");
//
//	/*z1();
//	z2();
//	z3();
//	z4();
//	z5();
//	z6();
//	z7();
//	z8();
//	z9();
//	//z10();
//	z13();
//	//z12();
//	zz13();*/
//	dop2();
//	dop3();
//	return 0;
//}
//
//void z1()
//{
//	enum State
//	{
//		ON,
//		OFF=6,
//		SLEEP
//	};
//	cout << "Введите состояние ПК" << endl;
//	State state;
//	char word[6];
//	
//	cin >> word;
//
//	switch (word[1])
//	{
//	case 'n':
//	{
//		state = ON;
//		break;
//	}
//
//	case 'f':
//	{
//		state = OFF;
//		break;
//	}
//
//	case 'l':
//	{
//		state = SLEEP;
//		break;
//	}
//}
//	switch (state)
//	{
//	case ON:
//	{
//		cout << "active";
//		break;
//	}
//
//	case OFF:
//	{
//		cout << "no active";
//		break;
//	}
//
//	case SLEEP:
//	{
//		cout << "sleep";
//		break;
//	}
//	}
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z2()
//{
//	enum Color
//	{
//		RED,
//		ORANGE,
//		YELLOW,
//		GREEN,
//		BLUE, 
//		PURPLE
//	};
//	cout << "Введите цет радуги" << endl;
//	Color color;
//	char word[7];
//	cin >> word;
//
//	switch (word[0]) {
//	case 'r':
//	{
//		color = RED;
//		cout << "RED";
//		break;
//	}
//	case 'o':
//	{
//		color = ORANGE;
//		cout << "ORANGE";
//		break;
//	}
//	case 'y':
//	{
//		color = YELLOW;
//		cout << "YELLOW";
//		break;
//	}
//	case 'g':
//	{
//		color = GREEN;
//		cout << "GREEN";
//		break;
//	}
//	case 'b':
//	{
//		color = BLUE;
//		cout << "BLUE";
//		break;
//	}
//	case 'p':
//	{
//		color = PURPLE;
//		cout << "PURPLE";
//		break;
//	}
//}
//	cout << endl;
//
//	switch (color) {
//	case RED:
//	{
//		cout << "RED";
//		break;
//	}
//	case ORANGE:
//	{
//		cout << "ORANGE";
//		break;
//	}
//	case YELLOW:
//	{
//		cout << "YELLOW";
//		break;
//	}
//	case GREEN:
//	{
//		cout << "GREEN";
//		break;
//	}
//	case BLUE:
//	{
//		cout << "BLUE";
//		break;
//	}
//	case PURPLE:
//	{
//		cout << "PURPLE";
//		break;
//	}
//}
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z3(){
//	cout << "Введите название планеты" << endl;
//	enum Planet
//	{
//		MERCURY,
//		VENERA,
//		EARTH,
//		MARS,
//		JUPITER,
//		SATURN,
//		URANUS,
//		NEPTUNE
//	};
//
//	Planet planet;
//	char word[8];
//	cin >> word;
//
//	switch (word[0]) {
//	case 'm':
//	{
//		cout << "mercury" << endl;
//		planet = MERCURY;
//		break;
//	}
//	case 'M':
//	{
//		cout << "mars" << endl;
//		planet = MARS;
//		break;
//	}
//	case 'e':
//	{
//		cout << "earth" << endl;
//		planet = EARTH;
//		break;
//	}
//	case 'v':
//	{
//		cout << "venera" << endl;
//		planet = VENERA;
//		break;
//	}
//	case 'j':
//	{
//		cout << "jupiter" << endl;
//		planet = JUPITER;
//		break;
//	}
//	case 's':
//	{
//		cout << "saturn" << endl;
//		planet = SATURN;
//		break;
//	}
//	case 'u':
//	{
//		cout << "uranus" << endl;
//		planet = URANUS;
//		break;
//	}
//	case 'n':
//	{
//		cout << "neptune" << endl;
//		planet = NEPTUNE;
//		break;
//	}
//	}
//	cout << endl;
//
//	switch (planet) {
//	case MERCURY:
//	{
//		cout << "mercury" << endl;
//		break;
//	}
//	case MARS:
//	{
//		cout << "mars" << endl;
//		break;
//	}
//	case EARTH:
//	{
//		cout << "earth" << endl;
//		break;
//	}
//	case VENERA:
//	{
//		cout << "venera" << endl;
//		break;
//	}
//	case JUPITER:
//	{
//		cout << "jupiter" << endl;
//		break;
//	}
//	case SATURN:
//	{
//		cout << "saturn" << endl;
//		break;
//	}
//	case URANUS:
//	{
//		cout << "uranus" << endl;
//		break;
//	}
//	case NEPTUNE:
//	{
//		cout << "neptune" << endl;
//		break;
//	}
//	}
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z4() {
//	cout << "Введите номер дня недели (1-7)" << endl;
//	enum Day
//	{
//		MONDAY,
//		THUESDAY,
//		WEDNESDAY,
//		THURSDAY,
//		FRIDAY,
//		SUNDAY,
//		SATURDAY
//	};
//
//	Day day;
//	int number;
//	cin >> number;
//
//	switch (number) {
//	case 1:
//	{
//		day = MONDAY;
//		break;
//	}
//	case 2:
//	{
//		day = THUESDAY;
//		break;
//	}
//	case 3:
//	{
//		day = WEDNESDAY;
//		break;
//	}
//	case 4:
//	{
//		day= THURSDAY;
//		break;
//	}
//	case 5:
//	{
//		day = FRIDAY;
//		break;
//	}
//	case 6:
//	{
//		day = SATURDAY;
//		break;
//	}
//	case 7:
//	{
//		day = SUNDAY;
//		break;
//	}
//	}
//	cout << endl;
//
//	switch (day) {
//	case MONDAY:
//	{
//		cout << "monday" << endl;
//		break;
//	}
//	case THUESDAY:
//	{
//		cout << "thuesday" << endl;
//		break;
//	}
//	case WEDNESDAY:
//	{
//		cout << "wednesday" << endl;
//		break;
//	}
//	case THURSDAY:
//	{
//		cout << "thursday" << endl;
//		break;
//	}
//	case FRIDAY:
//	{
//		cout << "friday" << endl;
//		break;
//	}
//	case SATURDAY:
//	{
//		cout << "saturday" << endl;
//		break;
//	}
//	case SUNDAY:
//	{
//		cout << "sunday" << endl;
//		break;
//	}
//	}
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z5() {
//    forward_list<int> arr = { 10, 23, 4 };
//	arr.insert_after(arr.before_begin(), 0); 
//	forward_list<int>::iterator it = arr.begin();
//	advance(it, 3);                     // Перемещаем итератор
//	arr.insert_after(it, 55);                // В позицию 4
//	for (int& el : arr) cout << el << ' ';
//	cout << endl;                  
//
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z6() {
//	/*list<int> newlist = {6, 2, 0};
//	auto iter = newlist.begin();
//	newlist.emplace_after(iter, 15);
//	for (int n : newlist)
//		cout << n << endl;*/
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z7() {
//	short max = 0;
//	vector<short>vect;
//	for (short i = 0; i < 5; i++)
//		vect.push_back(10 - i);
//
//	for (short i = 0; i < vect.size(); i++)
//		cout << vect[i] << ' ';
//
//	for (short i = 0; i < 5; i++)
//	{
//		if (vect[i] > max)
//			max = vect[i];
//	}
//	cout << '\n' << "max = " << max;
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z8() {
//	short i, min = 110;
//	deque<short>deq;
//	for (i = 0; i < 4; i++)
//	{
//		deq.push_back(i);
//		deq.push_front(10 - i);
//	}
//
//	for (i = 0; i < deq.size(); i++)
//	{
//		cout << deq[i] << ' ';
//
//		if (deq[i] < min)
//			min = deq[i];
//	}
//	/*for (i = 0; i < 2; i++)
//	{
//		deq.push_front(i);
//	}*/
//	cout << '\n' << "min = " << min << ' ';
//	for (i = 0; i < deq.size(); i++)
//	{
//		cout << deq[i] << ' ';
//	}
//	cout << endl << "--------------------------------" << endl;
//}
//
//void z9() {
//	array<int, 4>newarray = { 9, 8, 7, 6 };
//	short max = 0, min = 10, i = 0;
//	for (i; i < 4; i++)
//	{
//		if (newarray[i] > max)
//			max = newarray[i];
//
//		if (newarray[i] < min)
//			min = newarray[i];
//	}
//	cout << "sum = " << min + max;
//	cout << endl << "--------------------------------" << endl;
//}
//
//void zz13() {
//	cout << endl << "--------------------------------" << endl;
//	list<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//
//	cout << "Введите номер элемента в списке: ";
//	int val;
//	cin >> val;
//
//	int first = numbers.front();
//	int last = numbers.back();
//
//	for (int n : numbers)
//	{
//		cout << n << "\t";
//		cout << endl;
//	}
//
//
//	auto begin = numbers.begin();
//	for (int i = 0; i < val - 1; i++)
//	{
//		begin++;
//	}
//
//	numbers.push_front(*begin);
//	numbers.erase(begin++);
//
//	first = numbers.front();
//	last = numbers.back();
//
//	for (int n : numbers)
//		cout << n << "\t";
//	cout << endl;
//}
//
//void z13() {
//	cout << endl << "--------------------------------" << endl;
//
//	forward_list<int> newlist = { 2, 4, 6, 7, 8 };
//	forward_list<int> newlist_1;
//
//	int first = newlist.front();
//	for (int n : newlist)
//		cout << n << "\t";
//	cout << endl;
//
//	cout << "Введите количество элементов списка: ";
//	int val, point;
//	cin >> val;
//	cout << "Введите элемент номер 1: ";
//	cin >> point;
//
//	newlist_1.emplace_front(point);
//
//	auto iter = newlist_1.begin();
//	for (int i = 1; i < val; i++)
//	{
//		cout << "Введите элемент номер " << i << ": ";
//		cin >> point;
//		iter = newlist_1.emplace_after(iter, point);
//	}
//
//	newlist_1.resize(val);
//	cout << "вывод списка: ";
//	first = newlist_1.front();
//	for (int n : newlist_1)
//		cout << n << " ";
//	cout << endl;
//}
//
//void z12() {
//	short i, work = 1;
//	deque<short>deq;
//	for (i = 0; i < 4; i++)
//	{
//		deq.push_back(i);
//		deq.push_front(10 - i);
//	}
//
//	for (i = 0; i < deq.size(); i++)
//	{
//		cout << deq[i] << ' ';
//		work *= deq[i];
//	}
//	cout << endl << "work = " << work;
//	cout << endl << "--------------------------------" << endl;
//}
//
//union Myunion
//{
//	int a;
//	float b;
//	char c[10];
//};
//
//void dop2() {
//	cout << endl << "--------------------------------" << endl;
//	//Показатель того, что одновременно можно использовать лишь одно из значений в union (последнюю использованную)
//	Myunion u;
//	cin >> u.a >> u.b >> u.c;
//	cout << u.a << ' ' << u.b << ' ' << ' ' << u.c;
//}
//
//void dop3() {
//	cout << endl << "--------------------------------" << endl;
//	short sum = 0;
//	vector<short>vect;
//	for (short i = 10; i < 20; i++)
//		vect.push_back(i);
//
//	for (short i = 0; i < vect.size(); i++)
//	{
//		cout << vect[i] << ' ';
//		sum += vect[i];
//	}
//	cout << endl << "sum = " << sum;
//
//	for (short i = 30; i < 40; i++)
//		vect.push_back(i - 1);
//
//	cout << endl;
//
//	for (short i = 0; i < vect.size(); i++)
//	{
//		cout << vect[i] << ' ';
//		sum += vect[i];
//	}
//	cout << endl << "sum = " << sum;
//}