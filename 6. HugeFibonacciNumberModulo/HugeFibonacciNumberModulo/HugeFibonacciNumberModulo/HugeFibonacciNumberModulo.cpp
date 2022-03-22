#include <iostream>
#include <vector>


int64_t get_pisano_period(int64_t m) {
	std::vector<int64_t> v{ 1, 1 };
	while (true) {
		auto t = (v[v.size() - 1] + v[v.size() - 2]) % m;
		v.push_back(t);
		if (t == 0 && v.size() % 2 == 0 &&
			std::equal(v.begin(), v.begin() + v.size() / 2,
				v.begin() + v.size() / 2, v.end())) {
			return v.size() / 2;
		}
	}
	return v.size() / 2;
}

// Calculate and return Pisano Period
// The length of a Pisano Period for
// a given m ranges from 3 to m * m
int64_t pisano(int64_t m)
{
	if (m <= 1) return 0;

	int64_t previous = 0;
	int64_t current = 1;

	for (int64_t i = 0, ms = m * m; i < ms; i++) {
		int64_t tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % m;

		// Sabemos que es periodica.
		if (previous == 0 && current == 1) {
			return i + 1;
		}
	}
}

int64_t get_fibonacci_huge_fast(int64_t n, int64_t m) {

	int64_t period = pisano(m);
	int64_t fib = n % period;

	if (fib <= 1)
		return fib;

	int64_t previous = 0;
	int64_t current = 1;

	for (int64_t i = 2; i <= fib; ++i) {
		int64_t tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % m;
	}

	return current;
}


long long get_fibonacci_huge_naive(long long n, long long m) {
	if (n <= 1)
		return n;

	long long previous = 0;
	long long current = 1;

	for (long long i = 0; i < n - 1; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % m;
}

int main() {
	//long long n, m;
	//std::cin >> n >> m;
	// std::cout << get_fibonacci_huge_naive(n, m) << '\n';

	//int16_t m;
	//std::cin >> m;
	//std::cout << pisano(m) << '\n';

	int64_t n, m;
	std::cin >> n >> m;
	std::cout << get_fibonacci_huge_fast(n, m) << '\n';

}