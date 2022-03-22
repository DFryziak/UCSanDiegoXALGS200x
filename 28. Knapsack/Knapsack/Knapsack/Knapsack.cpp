#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {

	int elements = w.size() + 1; 	// Numero de elementos
	int weights = W + 1; // Rango de pesos a calcular [0..W]

	// Allocate the array
	int** values = new int*[elements];
	for (int element = 0; element < elements; element++)
		values[element] = new int[weights];

	for (int element = 0; element < elements; element++) {
		for (int weight = 0; weight < weights; weight++) {
			values[element][weight] = 0;
		}
	}

	// Barro la matriz, primero por fila
	for (int element = 1; element < elements; element++) {
		for (int weight = 1; weight < weights; weight++) {
			
			values[element][weight] = values[element - 1][weight]; // Valor optimo para este peso, sin tener en cuenta el elemento actual.		

			int element_weight = w[element - 1];
			if (element_weight <= weight) { // el peso del elemento tiene que ser menor o igual a la capacidad de la mochila.
				int val = values[element - 1][weight - element_weight] + element_weight;
				if (values[element][weight] < val) {
					values[element][weight] = val;
				}
			}
		}
	}

	int value = values[elements - 1][weights - 1];

	// Deallocate the array
	for (int i = 0; i < elements; i++)
		delete[] values[i];
	delete[] values;


	return value;
}

int main() {
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
