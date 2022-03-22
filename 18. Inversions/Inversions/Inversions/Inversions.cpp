#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions_naive(vector<int> &a, vector<int> &b, size_t left, size_t right) {

	long long number_of_inversions = 0;
	if (right <= left + 1) return number_of_inversions;
	size_t ave = left + (right - left) / 2;
	number_of_inversions += get_number_of_inversions_naive(a, b, left, ave);
	number_of_inversions += get_number_of_inversions_naive(a, b, ave, right);
	//write your code here
	return number_of_inversions;
}

int merge(vector<int> &a, int left, int mid, int right)
{
	if (right <= left) return 0;

	vector<int> l(mid - left + 1);
	vector<int> r(right - mid);

	for (int i = left; i <= mid; i++) {
		l[i - left] = a[i];
	}

	for (int i = mid + 1; i <= right; i++) {
		r[i - mid - 1] = a[i];
	}

	int i = left;
	int j = 0;
	int k = 0;
	int number_of_inversions = 0;
	while (j < l.size() && k < r.size()) {
		if (l[j] <= r[k]) {
			a[i] = l[j];
			j++; i++;
		}
		else {
		    // https://medium.com/@ssbothwell/counting-inversions-with-merge-sort-4d9910dc95f0
			// Al momento de agregar r[k], r[k] forma una inversion con todos los elementos de 
			// l[i] que no fueron agregados.
			a[i] = r[k];
			k++; i++;
			number_of_inversions = number_of_inversions + l.size() - j;
		}
	}

	while (j < l.size()) {
		a[i] = l[j];
		j++; i++;
	}

	while (k < r.size()) {
		a[i] = r[k];
		k++; i++;
	}

	return number_of_inversions;
}


long long get_number_of_inversions_fast(vector<int> &a, vector<int> &b, size_t left, size_t size) {

	long long number_of_inversions = 0;

	if (left + 1 >= size) return number_of_inversions;

	int q = (left + (size - 1)) / 2;

	number_of_inversions += get_number_of_inversions_fast(a, b, left, q + 1);
	number_of_inversions += get_number_of_inversions_fast(a, b, q + 1, size);
	number_of_inversions += merge(a, left, q, size - 1);

	return number_of_inversions;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	vector<int> b(a.size());
	std::cout << get_number_of_inversions_fast(a, b, 0, a.size()) << '\n';
}
