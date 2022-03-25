#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;

long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a * b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	else {
		assert(0);
	}
}

void min_max(int i, int j, vector<char> &operators, long long(&m)[15][15], long long(&M)[15][15], long long &min, long long &max) {
	// min = numeric_limits<long long>::max();
	// max = numeric_limits<long long>::min();
	max = LLONG_MIN;
	min = LLONG_MAX;

	// Go through all operators between i and j.
	for (int k = i; k < j; k++) {
		long long a = eval(M[i][k], M[k + 1][j], operators[k]);
		long long b = eval(M[i][k], m[k + 1][j], operators[k]);
		long long c = eval(m[i][k], M[k + 1][j], operators[k]);
		long long d = eval(m[i][k], m[k + 1][j], operators[k]);
		
		min = std::min(min, std::min(a, std::min(b, std::min(c, d))));
		max = std::max(max, std::max(a, std::max(b, std::max(c, d))));
	}
}

long long get_maximum_value(const string &exp) {

	if (exp.size() <= 0) {
		return 0;
	}

	int n = (exp.size() - 1) / 2; // Number of operators.
	// vector<char> operators(n);
	// vector<long long> operands(n + 1);
	vector<char> operators;
	vector<long long> operands;
	for (int i = 0; i < exp.size(); i++) {
		if (i % 2 == 0) {
			operands.push_back(exp[i] - 48);
		}
		else {
			operators.push_back(exp[i]);
		}
	}

	long long M[15][15];
	long long m[15][15];
	for (int i = 0; i <= n; i++) {
		m[i][i] = operands[i];
		M[i][i] = operands[i];
	}

	for (int s = 1; s <= n; s++) { // If there are n+1 digits, distances go from 1 to n.
		for (int i = 0; i <= n - s; i++) {
			int j = i + s;
			long long min, max;
			min_max(i, j, operators, m, M, min, max);
			m[i][j] = min;
			M[i][j] = max;
		}
	}

	return M[0][n];
}

int main() {
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
}
