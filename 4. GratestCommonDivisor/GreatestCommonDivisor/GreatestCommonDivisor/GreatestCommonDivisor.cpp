#include <iostream>
#include <cassert>

int64_t get_rand(int64_t l = 1, int64_t h = 10000000000000000000)
{
	int64_t offset = l;
	int64_t range = h - l + 1;

	int64_t random = offset + (rand() % range);

	return random;
}

int64_t gcd_naive(int64_t a, int64_t b) {
	int64_t current_gcd = 1;
	for (int64_t d = 2; d <= a && d <= b; d++) {
		if (a % d == 0 && b % d == 0) {
			if (d > current_gcd) {
				current_gcd = d;
			}
		}
	}
	return current_gcd;
}

int64_t gcd_fast(int64_t a, int64_t b) {
	// Hipotesis: d divide a y b si y solo si divide a' y b.
	// Lemma: gdc(a ,b) = gdc(a',b) = gdc(b, a')
	// Comparten divisores, por lo tanto comparte el GCD (maximo).

	// Caso base.
	if (b == 0) {
		return a;
	}

	return gcd_fast(b, a%b);
}

int main() {
	int a, b;
	std::cin >> a >> b;
	std::cout << gcd_fast(a, b) << std::endl;


	//while (true) {
	//	int a = get_rand();
	//	int b = get_rand();
	//	
	//	int naive = gcd_naive(a, b);
	//	int fast = gcd_fast(a, b);
	//	assert(naive == fast);
	//	
	//	std::cout << "Naive " << naive << std::endl;
	//	std::cout << "Fast " << fast << std::endl;
	//}
	return 0;
}