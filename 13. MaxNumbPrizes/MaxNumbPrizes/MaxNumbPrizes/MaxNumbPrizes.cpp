#include <iostream>
#include <vector>

using std::vector;



vector<int> optimal_summands(int n) {
	vector<int> summands;
	//write your code here
	int candidate = 1;
	while (n > 0) {
		if (n - candidate <= candidate) {
			summands.push_back(n);
			n = 0;
		}
		else {
			summands.push_back(candidate);
			n = n - candidate;
		}

		candidate++;
	}

	return summands;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> summands = optimal_summands(n);
	std::cout << summands.size() << '\n';
	for (size_t i = 0; i < summands.size(); ++i) {
		std::cout << summands[i] << ' ';
	}
}
