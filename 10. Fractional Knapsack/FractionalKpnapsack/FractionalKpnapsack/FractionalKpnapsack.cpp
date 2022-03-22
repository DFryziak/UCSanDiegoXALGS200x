#include <iostream>
#include <vector>

using std::vector;

int Select(vector<int> weights, vector<int> values, vector<int> track)
{
	int max = 0;
	for (int i = 1; i < values.size(); i++) {
		if ((double)values[i] / weights[i] > (double)values[max] / weights[max] && track[i] != 1)
			max = i;
	}

	return max;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
	double value = 0.0;

	// write your code here
	double currentWeight = 0.0;
	double nCandidates = 0;
	vector<int> track(values.size());
	while (currentWeight < capacity && nCandidates < weights.size()) { // Seguir mientras no se haya superado el peso total y haya candidatos.
		int i = Select(weights, values, track);
		track[i] = 1;
		if (weights[i] < capacity - currentWeight) {
			value += values[i];
			currentWeight += weights[i];
		}
		else {
			value += (capacity - currentWeight) * (double)values[i] / weights[i];
			currentWeight = capacity;
		}

		nCandidates++;
	}


	return value;
}

int main() {
	int n;
	int capacity;
	std::cin >> n >> capacity;
	vector<int> values(n);
	vector<int> weights(n);
	for (int i = 0; i < n; i++) {
		std::cin >> values[i] >> weights[i];
	}

	double optimal_value = get_optimal_value(capacity, weights, values);

	std::cout.precision(10);
	std::cout << optimal_value << std::endl;
	return 0;
}
