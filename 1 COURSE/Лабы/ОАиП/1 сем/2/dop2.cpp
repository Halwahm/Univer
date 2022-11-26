#include <iostream>
using namespace std;
void ask() {  

	double w, v, b = 40, x = 1.1, a = 5e-6;

	w = (a + b) * tan(x) / (x + 1);
	v = 1/2 * b - sqrt(w - a * b);

	cout << "w = " << w << endl << "v = " << v;

} 