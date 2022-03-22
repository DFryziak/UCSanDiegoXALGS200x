#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int select(vector<int> v)
{
	int min = -1;
	for (size_t i = 0; i < v.size(); i++) {
		if (v[i] != -1) {
			if (min == -1 || v[i] < v[min]) {
				min = i;
			}
		}
	}
	return min;
}

long long max_dot_product(vector<int> a, vector<int> b) {
	// write your code here
	long long result = 0;
	for (size_t i = 0; i < a.size(); i++) {
		int m = select(a);
		int n = select(b);
		result += ((long long)a[m]) * b[n];
		a[m] = -1;
		b[n] = -1;
	}
	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n), b(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	for (size_t i = 0; i < n; i++) {
		std::cin >> b[i];
	}
	std::cout << max_dot_product(a, b) << std::endl;
}
