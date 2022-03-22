#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

// Esta version no usa programacion dinamica y tampoco es correcto el algoritomo
// Ej;
// 8 = 1 * 3 * 2 + 1 + 1 : 4 operaciones
// 8 = 1 * 2 * 2 * 2 : 3 operaciones
// De esta forma vemos que se puede obtener un mejor resultado
vector<int> optimal_sequence_naive(int n) {
	std::vector<int> sequence;
	while (n >= 1) {
		sequence.push_back(n);
		if (n % 3 == 0) {
			n /= 3;
		}
		else if (n % 2 == 0) {
			n /= 2;
		}
		else {
			n = n - 1;
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

vector<int> optimal_sequence(int n) {

	int infinite = 1000001;
	vector<vector<int>> sequences;
	vector<int> min_num_op(n + 1);

	min_num_op[0] = 0;
	min_num_op[1] = 0;
	sequences.push_back(vector<int>(0));
	sequences.push_back(vector<int>{ 1 });
	for (int ni = 2; ni <= n; ni++) {

		min_num_op[ni] = infinite;
		int ioption = 0;

		if (ni % 3 == 0) {
			if (min_num_op[ni / 3] + 1 < min_num_op[ni]) {
				min_num_op[ni] = min_num_op[ni / 3] + 1;
				ioption = 3;
				// sequence[sequence.size() - 1] = 3;
			}
		}

		if (ni % 2 == 0) {
			if (min_num_op[ni / 2] + 1 < min_num_op[ni]) {
				min_num_op[ni] = min_num_op[ni / 2] + 1;
				ioption = 2;
				// sequence[sequence.size() - 1] = 2;
			}
		}

		if (min_num_op[ni - 1] + 1 < min_num_op[ni]) {
			min_num_op[ni] = min_num_op[ni - 1] + 1;
			ioption = 1;
			// sequence[sequence.size() - 1] = 1;
		}

		switch (ioption) {
		case 3:
		{
			vector<int> sequence(sequences[ni / 3].begin(), sequences[ni / 3].end());
			sequence.push_back(ni);
			sequences.push_back(sequence);
			break;
		}
		case 2:
		{
			vector<int> sequence(sequences[ni / 2].begin(), sequences[ni / 2].end());
			sequence.push_back(ni);
			sequences.push_back(sequence);
			break;
		}
		case 1:
		{
			vector<int> sequence(sequences[ni - 1].begin(), sequences[ni - 1].end());
			sequence.push_back(ni);
			sequences.push_back(sequence);
			break;
		}
		default:
			break;
		}
	}

	return sequences[sequences.size() - 1];
}

int main() {
	int n;
	std::cin >> n;
	vector<int> sequence = optimal_sequence(n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i) {
		std::cout << sequence[i] << " ";
	}
}
