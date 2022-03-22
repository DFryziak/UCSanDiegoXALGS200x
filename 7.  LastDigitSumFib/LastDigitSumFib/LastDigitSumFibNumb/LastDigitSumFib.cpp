#include <iostream>
#include <vector>

// Calcula el periodo de Fi (mod m).
int pisano(int m) {

	if (m <= 1) return 0; // No hay periodo.

	// Sabemos que el periodo de pisano comienza con el par de valores 0 1.
	// Y todo par de valores define la serie.

	int previous = 0;
	int current = 1;

	for (int i = 0, l = m * m; i < l; i++) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % m;

		if (previous == 0 && current == 1) {
			return i + 1;
		}

	}
}


int fibonacci_sum_naive(long long n) {
	if (n <= 1)
		return n;

	long long previous = 0;
	long long current = 1;
	long long sum = 1;

	for (long long i = 2; i <= n; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		sum += current;
	}

	return sum % 10;
}


int fibonacci_sum_fast(long long n) {

	if (n <= 1)
		return n;

	// Hay que calcular el ultimo digito de la Suma(F(i)) = Si
	// Si = F(i+2) - 1.

	// Por lo tanto habria que calcular el ultimo digito de F(i+2)-1
	// Calcular el ultimo digito de F(i+2) es igual a F((i+2)%60) % 10.

	int pisano = 60; // para modulo 10 el periodo es 60.

	// Calcular Fi%10 hasta (i+2)%60

	int fib_n = (n + 2) % 60;
	int previous = 0;
	int current = 1;
	for (int i = 2; i <= fib_n; i++) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % 10;
	}

	// En current tengo el ultimo digito de F(i+2).
	
	// Si es 0 entonces F(i+2) - 1 = 9 
	if (current == 0) {
		return 9;
	}
	else {
		return current - 1;
	}
}


int main() {
	// Probar 614162383528 igual a 9

	//long long n = 0;
	//std::cin >> n;
	//std::cout << fibonacci_sum_naive(n);

	//int64_t n = 0;
	//std::cin >> n;
	//std::cout << fibonacci_sum_fast(n) << '\n';

	for (int64_t n; std::cin >> n;) {
		// std::cout << fibonacci_sum_naive(n) << '\n';
		std::cout << fibonacci_sum_fast(n) << '\n';
	}

	//for (int n; std::cin >> n;) {
	//	std::cout << pisano(n) << '\n';
	//}
}
