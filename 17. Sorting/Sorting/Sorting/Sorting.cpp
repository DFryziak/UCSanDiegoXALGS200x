#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	return j;
}

// Version original, no optimizada cuando el vector tiene elementos iguales.
void randomized_quick_sort1(vector<int> &a, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	int m = partition2(a, l, r);

	randomized_quick_sort1(a, l, m - 1);
	randomized_quick_sort1(a, m + 1, r);
}

// Primer intento necesito dos swap. Se puede mejorar!
vector<int> partition3(vector<int> &a, int l, int r)
{
	vector<int> m(2);
	int x = a[l]; // pivot.
	int m1 = l; // j apunta al pivot si no avanza, o al ultimos elemento que es como mucho el valor del pivot.
	int m2 = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] < x) {
			m1++;
			m2++;
			swap(a[i], a[m1]);
			if (m2 > m1) swap(a[m2], a[i]);
		}
		else if (a[i] == x) {
			m2++;
			swap(a[i], a[m2]);
		}
	}

	swap(a[l], a[m1]);

	m[0] = m1;
	m[1] = m2;

	return m;
}

// Basado en el problema de la bandera de Holanda de Dijkstra. Tengo un pdf en la carpeta del curso.
vector<int> partition_dutch_flag(vector<int> &a, int l, int r)
{
	vector<int> m(2);

	int pivot = a[l];

	int h = l + 1;
	int k = l + 1;
	int t = r + 1;

	while (k < t) {
		if (a[k] < pivot) {
			swap(a[h], a[k]);
			h++;
			k++;
		}
		else if (a[k] == pivot) {
			k++;
		}
		else {
			t--;
			swap(a[k], a[t]);
		}
	}

	h--;
	swap(a[l], a[h]);

	m[0] = h;
	m[1] = t - 1;

	return m;
}


void randomized_quick_sort2(vector<int> &a, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	// vector<int> m = partition3(a, l, r);
	vector<int> m = partition_dutch_flag(a, l, r);

	randomized_quick_sort2(a, l, m[0] - 1);
	randomized_quick_sort2(a, m[1] + 1, r);
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	// randomized_quick_sort1(a, 0, a.size() - 1);
	randomized_quick_sort2(a, 0, a.size() - 1);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << ' ';
	}
}
