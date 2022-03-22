#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
	long long sum = 0;

	long long current = 0;
	long long next = 1;

	for (long long i = 0; i <= to; ++i) {
		if (i >= from) {
			sum += current;
		}

		long long new_current = next;
		next = next + current;
		current = new_current;
	}

	return sum % 10;
}

int fibonacci_sum_fast(long long n) {

	if (n <= 1)
		return n;

	int pisano = 60;

	int fib_n = (n + 2) % 60;
	int previous = 0;
	int current = 1;
	for (int i = 2; i <= fib_n; i++) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % 10;
	}

	if (current == 0) {
		return 9;
	}
	else {
		return current - 1;
	}
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {

	if (from == 0) {
		return fibonacci_sum_fast(to);
	}

	long long sum = fibonacci_sum_fast(to) - fibonacci_sum_fast(from - 1);

	if (sum < 0) {
		sum = 10 + sum;
	}

	return sum;
}

int main() {
	//long long from, to;
	//std::cin >> from >> to;
	//std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';

	for (long long from, to = 0; std::cin >> from >> to;) {
		std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
		std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
	}
}