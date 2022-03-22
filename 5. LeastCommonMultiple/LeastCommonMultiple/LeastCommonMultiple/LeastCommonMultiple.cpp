// LeastCommonMultiple.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <algorithm>

long long lcm_starter(int a, int b) {
	for (long l = 1; l <= (long long)a * b; ++l)
		if (l % a == 0 && l % b == 0)
			return l;

	return (long long)a * b;
}

int64_t lcm_naive1(int64_t a, int64_t b) {
	if (a <= 1) return b;
	if (b <= 1) return a;
	if (a % b == 0) return a;
	if (b % a == 0) return b;

	int64_t current_lcm = a * b;
	int64_t max, min;
	if (a >= b) {
		max = a;
		min = b;
	}
	else {
		max = b;
		min = a;
	}
	for (int64_t l = max + max; l < current_lcm; l += max) {
		if (l % min == 0) {
			return l;
		}
	}

	return current_lcm;
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

int64_t lcm_fast1(int64_t a, int64_t b) {
	// Busco todos los factores comunes entre a y b.
	// f1 = gcd(a,b) , f2 = gdc(a/f1, b/f1)..
	// hasta que no haya mas factores comunes. Multiplico por los factores que restan.

	int64_t l = 1;

	int64_t n1 = a;
	int64_t n2 = b;

	while (true) {
		int64_t gcd = gcd_fast(n1, n2);
		if (gcd != 1) {
			l *= gcd;
			n1 /= gcd;
			n2 /= gcd;
		}
		else {
			l *= n1 * n2;
			break;
		}
	}

	return l;
}

int64_t lcm_fast2(int64_t a, int64_t b) {
	// Luego de hacer la version 1 puede lograr hacer algo recursivo.

	int64_t gcd = gcd_fast(a, b);

	if (gcd == 1) {
		return a * b;
	}

	return gcd * lcm_fast2(a / gcd, b / gcd);
}

int64_t lcm_fast3(int64_t a, int64_t b) {
	// Por definicion
	// lcm(a,b) = a*b/gcd(a,b)

	return a * b / gcd_fast(a, b);
}

int main()
{
	int a, b;
	std::cin >> a >> b;
	std::cout << lcm_fast2(a, b) << std::endl;

	return 0;
}

