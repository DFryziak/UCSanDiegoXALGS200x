#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

// Asumir que el polinomio tiene un numero par de factores. Se rellenan con 0.
vector<int> Mult(const vector<int> &A, const vector<int> &B, int n, int al, int bl) {
	// n es el tamano del problema, que es igual al grado del polinomo de mayor grado mas 1
	// Ej. x2 + x + 1 tiene tamano 3.

	// al y bl son los índices que me interesan de la primera mitad.

	vector<int> r(2 * n - 1);

	if (n == 1) {

		r[0] = A[al] * B[bl];
		return r;
	}

	// A = D1*x^(n/2) + D0.
	// B = E1*x^(n/2) + E0.
	// Al pedo ceil y floor pq asumimos que un numer par de factores.
	int p = std::ceil((float)n / 2);
	int q = std::floor((float)n / 2);
	vector<int> D1E1 = Mult(A, B, p, al, bl); // Se multiplica el polinomio de mayor grado de A por el polinomio de mayor grado de B.
	vector<int> D0E0 = Mult(A, B, q, al + p, bl + p); // Se multiplica el polinomio de menor grado de A por el polinomio de menor grado de B.
	for (size_t i = 0; i < D1E1.size(); i++) {
		r[i] = D1E1[i];
	}
	for (size_t i = D1E1.size() + 1; i < r.size(); i++) {
		r[i] = D0E0[i - D1E1.size() - 1];
	}

	vector<int> D1E0 = Mult(A, B, p, al, bl + p); // Se multiplica la mitad de mayor orden del polinomio A por la mitad de menor orden del polinomio B.
	vector<int> D0E1 = Mult(A, B, p, al + p, bl); // Se multiplica la mitad de menor orden del polinomio A por la mitad de mayor orden del polinomio B.
	for (size_t i = n - q; i < D1E0.size() + n - q; i++) {
		r[i] += D0E1[i - (n - q)] + D1E0[i - (n - q)];
	}

	return r;
}

int main()
{
	vector<int> A = { 0, 3, 2, 5};
	vector<int> B = { 0, 5, 1, 2};
	vector<int> r = Mult(A, B, 4, 0, 0);
	//vector<int> A = { 4, 3, 2, 1 };
	//vector<int> B = { 1, 2, 3, 4 };
	//vector<int> r = Mult(A, B, 4, 0, 0);
	//vector<int> A = { 1, 2 };
	//vector<int> B = { 2, 1 };
	//vector<int> r = Mult(A, B, 2, 0, 0);

	for (size_t i = 0; i < r.size(); i++) {
		std::cout << r[i] << ' ';
	}
}

