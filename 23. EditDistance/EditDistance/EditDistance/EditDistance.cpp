#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {

	int rows = str1.size() + 1;
	int cols = str2.size() + 1;

	// Allocate the array
	int** d = new int*[rows];
	for (int row = 0; row < rows; row++)
		d[row] = new int[cols];

	// Inicializo la primera fila y primera columna con las distancias de edicion
	for (int row = 0; row < rows; row++) {
		d[row][0] = row;
	}
	for (int col = 0; col < cols; col++) {
		d[0][col] = col;
	}


	// Barro la matriz, primero por columna
	for (int col = 1; col < cols; col++) {
		for (int row = 1; row < rows; row++) {
			int insertion = d[row][col - 1] + 1;
			int deletion = d[row - 1][col] + 1;
			int match = d[row - 1][col - 1];
			int mismatch = d[row - 1][col - 1] + 1;

			int min = std::min(insertion, deletion);
			if (str1[row - 1] == str2[col - 1]) {
				 min = std::min(min, match);				 
			}
			else {
				min = std::min(min, mismatch);				
			}
			d[row][col] = min;
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
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}
