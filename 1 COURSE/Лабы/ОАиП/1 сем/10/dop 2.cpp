#include <iostream>
#include <ctime>

int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	const int N = 100;
	int i, sz, A[N], k = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0;
	int rmx = 99;
	cout << "Введите количество недель ";
	cin >> sz;
	k = sz * 7;
	cout << "Массив А:" << endl;
	srand((unsigned)time(NULL));
	for (i = 0; i < k; i++)
	{
		A[i] = rand() % rmx;
		cout << "[" << i + 1 << " день]  " << A[i] << endl;
	}
	for (i = 0; i < k; i++)
	{
		if (i < 7) {
			m1 = m1 + A[i];
		}
		else if (7 < i && i < 15) {
			m2 = m2 + A[i];
		}
		else if (14 < i && i < 22) {
			m3 = m3 + A[i];
		}
		else if (21 < i && i < 29) {
			m4 = m4 + A[i];
		}
	}
	cout << endl;

	if (m1 * (sz - 1) > m2 + m3 + m4) {
		cout << "В первую неделю выпало больше всего осадков";
	}
	else if (m2 * (sz - 1) > m1 + m3 + m4) {
		cout << "Во вторую неделю выпало больше всего осадков";
	}
	else if (m3 * (sz - 1) > m1 + m2 + m4) {
		cout << "В третью неделю выпало больше всего осадков";
	}
	else if (m4 * (sz - 1) > m1 + m2 + m3) {
		cout << "В четвертую неделю выпало больше всего осадков";
	}
	return 0;
}