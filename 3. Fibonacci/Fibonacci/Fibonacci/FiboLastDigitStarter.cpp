#include <iostream>
#include <cassert>
#include "FiboLastDigitStarter.h"

int get_fibonacci_last_digit_fast(int n) {
	if (n <= 1)
		return n;

	int previous = 0;
	int current = 1;

	for (int i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % 10;
	}

	return current;
}


int get_fibonacci_last_digit_naive(int n) {
	if (n <= 1)
		return n;

	int previous = 0;
	int current = 1;

	for (int i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % 10;
}

void FiboLastDigitStarter::test_solution() {
	assert(get_fibonacci_last_digit_fast(3) == 2);
	assert(get_fibonacci_last_digit_fast(331) == 9);
	assert(get_fibonacci_last_digit_fast(327305) == 5);
}

int FiboLastDigitStarter::main() {
	test_solution();

	//int n;
	//std::cin >> n;
	//// int c = get_fibonacci_last_digit_naive(n);
	//int c = get_fibonacci_last_digit_fast(n);
	//std::cout << c << '\n';

	return 0;
}
