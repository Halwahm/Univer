#include <iostream>

using namespace std;

int main() {

	setlocale(LC_CTYPE, "Russian");
	cout << "¬ведите кол-во лет" << endl;
	float n;
	cin >> n;
	cout << "¬ведите уценку в %" << endl;
	float p;
	cin >> p;
	float s, sum = 0;
	for (int i = 0; i < n; i++) {
		cout << "¬ведите стоимость за " << i + 1 << " год" << endl;
		cin >> s;
		sum = sum * (1 - (p / 100)) + s;
	}
	cout << sum;

	return 0;
}