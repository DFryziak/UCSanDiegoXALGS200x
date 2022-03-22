#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {

	int rows = a.size() + 1;
	int cols = b.size() + 1;

	// Allocate the array
	int** d = new int*[rows];
	for (int row = 0; row < rows; row++)
		d[row] = new int[cols];

	// Esta parte no hace falta ya que al inicializarse todos los valores son cero.
	// Inicializo la primera fila y primera columna con las distancias de edicion
	//for (int row = 0; row < rows; row++) {
	//	d[row][0] = 0;
	//}
	//for (int col = 0; col < cols; col++) {
	//	d[0][col] = 0;
	//}

	// Barro la matriz, primero por columna
	for (int col = 1; col < cols; col++) {
		for (int row = 1; row < rows; row++) {
			int insertion = d[row][col - 1];
			int deletion = d[row - 1][col];
			int match = d[row - 1][col - 1] + 1;
			int mismatch = d[row - 1][col - 1];

			int max = std::max(insertion, deletion);
			if (a[row - 1] == b[col - 1]) {
				max = std::max(max, match);
			}
			else {
				max = std::max(max, mismatch);
			}
			d[row][col] = max;
		}
	}

	int value = d[rows - 1][cols - 1];


	// Deallocate the array
	for (int i = 0; i < rows; i++)
		delete[] d[i];
	delete[] d;


	return value;
}


int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	int m;
	std::cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; i++) {
		std::cin >> b[i];
	}

	std::cout << lcs2(a, b) << std::endl;
}
