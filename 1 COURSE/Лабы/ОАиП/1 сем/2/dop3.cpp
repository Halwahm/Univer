#include <iostream>
using namespace std;
void asd() {

	double s, t, x = 0.1, j = 12, y = 5e-6;

	s = 0.4 * x - 1 / j * tan (9*y);
	t = s - sin(s);

	cout << " s = " << s << endl << "t = " << t;

}