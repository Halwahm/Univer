#include <iostream>
#include <cmath>
using namespace std;
void one();
void two();


int main() {
	setlocale(LC_CTYPE, "russian");
	
	one();
	//two();
	return 0;
}
void one(){
	cout << "14 variant: " << endl;
	double z = 0, c = 10.1, x;
	int i;
	int y[6] = { 4, -6, 3, -3, 9, 5 };
		for (i = 0; i < 6; i++) {
			if (y[i] > c)
			z = pow(sin(c), 2);
		}
	z += z;
	cout << "z = " << z << endl;
		for (i = 0; i < 6; i++) {
			if (y[i] <= c)
			z = pow(cos(c), 2);
		}
	z += z;
	cout << "z = " << z << endl;
}
void two()
{
	int x[5] = { 9, 1.7, 4, 6, 3 };
	float m, max, a;
	max = x[0];
	int i;
	for (i = 0; i < 5; i++) {
		if (x[i] > max)
			max = x[i];
		m = 1 + max;
		a = (pow(x[i], 2) + m);
	}
	a += a;
	cout << "a = " << a;
}