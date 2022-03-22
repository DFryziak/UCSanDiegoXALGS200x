#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

void swap(vector<string> &a, int i, int j) {
	string aux = a[i];
	a[i] = a[j];
	a[j] = aux;
}

bool isBetter1(string a, string b) {

	if (a.compare(b) == 0) return false;

	int max = std::max(a.size(), b.size());

	for (size_t i = 0; i < max * 2; i++) {
		char ca = a[i % a.size()];
		char cb = b[i % b.size()];

		if (ca > cb) return true;
		if (ca < cb) return false;
	}

	return false;
}

bool isBetter(string a, string b) {
	
	string s1 = a.append(b);
	string s2 = b.append(a);

	return s1 > s2;
	
}

string largest_number(vector<string> &a) {
	//write your code here
	std::stringstream ret;

	while (a.size() > 0) {
		int best = 0;
		for (size_t i = 1; i < a.size(); i++) {
			if (isBetter(a[i], a[best])) {
				best = i;
			}
		}

		ret << a[best];
		swap(a, best, a.size() - 1);
		a.pop_back();
	}

	string result;
	ret >> result;
	return result;
}

int main() {
	int n;
	std::cin >> n;
	vector<string> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	std::cout << largest_number(a);
}
