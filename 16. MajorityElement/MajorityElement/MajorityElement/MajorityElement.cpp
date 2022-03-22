#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

bool is_majority(vector<int> &a, int value, int left, int right) {

	if (left > right) return -1;

	int c = 0;
	int n = right - left + 1;
	int m = n / 2 + 1;
	for (size_t i = left; i <= right; i++) {
		if (a[i] == value) c++;
		if (c >= m) return true;

	}

	return false;
}

int get_majority_element(vector<int> &a, int left, int right) {

	if (right >= a.size())
		right = right - 1;

	if (left > right) return -1;

	//write your code here
	if (left == right) {
		return a[left];
	}
	else if (left < right) {
		// Busco el elemento mayoritario de una mitad y de otra en forma recursiva.
		// Luego, tengo dos canditatos, pero solo uno puede ser elemento mayoritario
		// ya que no pueden haber dos elementos que aparezcan n/2 + 1 veces.

		int mid = (int)((left + right)*.5);
		int mElem1 = get_majority_element(a, left, mid);
		int mElem2 = get_majority_element(a, mid + 1, right);

		if (mElem1 != -1 && is_majority(a, mElem1, left, right))
			return mElem1;
		
		if (mElem2 != -1 && is_majority(a, mElem2, left, right))
			return mElem2;
	}

	return -1;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
