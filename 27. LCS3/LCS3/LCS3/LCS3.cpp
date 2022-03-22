#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {

	int rows = a.size() + 1;
	int cols = b.size() + 1;
	int pages = c.size() + 1;

	// Allocate the array
	int*** d = new int**[pages];
	for (int page = 0; page < pages; page++) {
		d[page] = new int*[rows];
		for (int row = 0; row < rows; row++) {
			d[page][row] = new int[cols];
		}
	}

	for (int page = 0; page < pages; page++) {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				d[page][row][col] = 0;
			}
		}
	}

	//for (int row = 0; row < rows; row++) {
	//	for (int col = 0; col < cols; col++) {
	//		d[0][row][cols] = 0;
	//	}
	//}

	//for (int page = 0; page < pages; page++) {
	//	for (int row = 0; row < rows; row++) {
	//		d[page][row][0] = 0;
	//	}
	//	for (int col = 0; col < cols; col++) {
	//		d[page][0][col] = 0;
	//	}
	//}

	for (int page = 1; page < pages; page++) {
		for (int col = 1; col < cols; col++) {
			for (int row = 1; row < rows; row++) {
				int mismatch = d[page - 1][row - 1][col - 1];
				int match = d[page - 1][row - 1][col - 1] + 1;
				int op1 = d[page][row - 1][col - 1];
				int op2 = d[page - 1][row - 1][col];
				int op3 = d[page][row - 1][col];
				int op4 = d[page][row][col - 1];
				int op5 = d[page - 1][row][col];

				int max = std::max(std::max(std::max(std::max(op1, op2), op3), op4), op5);
				if (a[row - 1] == b[col - 1] && b[col - 1] == c[page - 1]) {
					max = std::max(max, match);
				}
				else {
					max = std::max(max, mismatch);
				}

				d[page][row][col] = max;
			}
		}
	}

	int value = d[pages - 1][rows - 1][cols - 1];


	// Deallocate the array
	for (int page = 0; page < pages; page++) {
		for (int row = 0; row < rows; row++) {
			delete[] d[page][row];
		}
	}
	delete[] d;

	return value;
}

int main() {
	size_t an;
	std::cin >> an;
	vector<int> a(an);
	for (size_t i = 0; i < an; i++) {
		std::cin >> a[i];
	}
	size_t bn;
	std::cin >> bn;
	vector<int> b(bn);
	for (size_t i = 0; i < bn; i++) {
		std::cin >> b[i];
	}
	size_t cn;
	std::cin >> cn;
	vector<int> c(cn);
	for (size_t i = 0; i < cn; i++) {
		std::cin >> c[i];
	}
	std::cout << lcs3(a, b, c) << std::endl;
}
