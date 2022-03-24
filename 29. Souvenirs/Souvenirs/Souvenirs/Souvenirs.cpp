#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <string>
using namespace std;

// Helper function for solving 3 partition problem.
// It returns 1 if there exist three subsets with a given sum.
int subset_sum_recur(vector<int> const &S, int n, int a, int b, int c) {

	// Return true if the subset is found.
	if (a == 0 && b == 0 & c == 0) {
		return true;
	}

	// Base case: no items left and the subset was not found.
	if (n < 0) {
		return false;
	}

	// Case 1. The current item becomes part of the first subset.
	bool A = false;
	if (a - S[n] >= 0) {
		A = subset_sum_recur(S, n - 1, a - S[n], b, c);
	}

	// Case 2. The current item becomes part of the second subset.
	bool B = false;
	if (!A && (b - S[n] >= 0)) {
		B = subset_sum_recur(S, n - 1, a, b - S[n], c);
	}

	// Case 3. The current item becomes part of the third subset.
	bool C = false;
	if ((!A && !B) && (c - S[n] >= 0)) {
		C = subset_sum_recur(S, n - 1, a, b, c - S[n]);
	}

	return A || B || C;
}

// Top-down without memoization.
int partition3_recur(vector<int> &A) {

	int n = A.size();

	if (n < 3) {
		return false;
	}

	int sum = accumulate(A.begin(), A.end(), 0);

	return !(sum % 3) && subset_sum_recur(A, n - 1, sum / 3, sum / 3, sum / 3);
}

// Top-down with memoization.
int subset_sum_dp_recur(vector<int> const &S, int n, int a, int b, int c, unordered_map<string, bool> &lookup) {
	// https://www.techiedelight.com/3-partition-problem/

	// A subset is found.
	if (a == 0 && b == 0 && c == 0) {
		return true;
	}

	// Base case: no items left.
	if (n < 0) {
		return false;
	}

	// Construct a unique map key from dynamic elements of the input.
	string key = to_string(a) + "|" + to_string(b) + "|" + to_string(c) + "|" + to_string(n);

	// if the subproblem is seen for the first time, solve it and 
	// store its result in a map.
	if (lookup.find(key) == lookup.end()) {

		// Case 1.
		bool A = false;
		if (a - S[n] >= 0) {
			A = subset_sum_dp_recur(S, n - 1, a - S[n], b, c, lookup);
		}

		// Case 2.
		bool B = false;
		if (!A && (b - S[n] >= 0)) {
			B = subset_sum_dp_recur(S, n - 1, a, b - S[n], c, lookup);
		}

		// Case 3.
		bool C = false;
		if ((!A && !B) && (c - S[n] >= 0)) {
			C = subset_sum_dp_recur(S, n - 1, a, b, c - S[n], lookup);
		}

		// return true if we get a solution.
		lookup[key] = A || B || C;
	}

	// return the subproblem solution from the map.
	return lookup[key];
}

// Function for solving the 3–partition problem. It returns true if the given
// set `S[0…n-1]` can be divided into three subsets with an equal sum.
int partition3_dp_recur(vector<int> &S) {

	int n = S.size();

	// Para que existan 3 subconjuntos deben haber al menos 3 elementos.
	if (n < 3) {
		return false;
	}

	int sum = accumulate(S.begin(), S.end(), 0);

	// create a map to store solutions to a subproblem.
	unordered_map<string, bool> lookup;

	return !(sum % 3) && subset_sum_dp_recur(S, n - 1, sum / 3, sum / 3, sum / 3, lookup);
}

// Bottom-up with tabulation.
int partition3_dp_iter(vector<int> const &S) {

	// https://www.geeksforgeeks.org/partition-problem-dp-18/
	// https://raymondkevin.top/2020/04/19/algorithmic-toolboxweek-6-dynamic-programming-2/
	// Extendemos el caso de 2 particiones a 3.

	int n = S.size();

	if (n < 3) {
		return false;
	}

	int sum = accumulate(S.begin(), S.end(), 0);
	if (sum % 3 != 0) {
		return false;
	}

	int dp[21][100][100];
	for (int i = 0; i <= n; i++) {
		dp[0][0][0] = 1; // con cualquier conjunto de elementos es posible obtener dos subconjutos que sumen cero.
										 // Ej. {9,2,4,5} es posible obtener dos conjuntos {}.
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= sum / 3; j++) {
			for (int k = 0; k <= sum / 3; k++) {
				dp[i][j][k] = dp[i - 1][j][k];
				if (j >= S[i - 1] && dp[i - 1][j - S[i - 1]][k]) dp[i][j][k] = 1;
				if (k >= S[i - 1] && dp[i - 1][j][k - S[i - 1]]) dp[i][j][k] = 1;
			}
		}
	}

	return dp[n][sum / 3][sum / 3];
}

int main() {
	int n;
	std::cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < A.size(); ++i) {
		std::cin >> A[i];
	}
	// std::cout << partition3_recursive(A) << '\n';
	// std::cout << partition3_dp_recur(A) << '\n';
	std::cout << partition3_dp_iter(A) << '\n';
}
