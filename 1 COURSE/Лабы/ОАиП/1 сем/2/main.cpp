
#include <iostream>
using namespace std;
void main()
{
	double a = 1.5, b = -8.1, j = 4, t = 4e-8, s, w, v;

	s = sqrt((t * a) / t + 1) + 4 * exp(2*b);
	w = s * a / (1 + 0.1 * a);
	v = s + j * sqrt((pow(a, 2)) + (pow(b, 2)));
	cout << " s = " << s << endl << " w = " << w << endl << " v = " << v;

}