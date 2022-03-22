#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using std::vector;
using std::cin;
using std::cout;

using namespace std::chrono;

int get_rand(int l, int h)
{
	int offset = l;
	int range = h - l + 1;

	int random = offset + (rand() % range);

	return random;
}

void swap(vector<int32_t>& A, int i, int j)
{
	int32_t temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}

vector<int> generate_vec(int N, int M)
{
	int n = get_rand(2, N);
	// int n = 2000000;
	vector<int32_t> A(n);
	for (int i = 0; i < n; i++) {
		A[i] = get_rand(0, M);
	}

	return A;
}

// n^2 comparaciones.
int64_t MaxPairwiseProductNaive(const vector<int32_t>& A) {
	int product = 0;
	int n = A.size();
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			product = std::fmaxl(product, A[i] * A[j]);
		}
	}
	return product;
}

//long MaxPairwiseProduct(const vector<long>& numbers) {
//	long max1;
//	long max2;
//	long result;
//	if (numbers[0] >= numbers[1])
//	{
//		max1 = numbers[0];
//		max2 = numbers[1];
//	}
//	else
//	{
//		max1 = numbers[1];
//		max2 = numbers[0];
//	}
//
//	int n = numbers.size();
//
//	if (n == 2) {
//		result = max1 * max2;
//		return result;
//	}
//
//	for (int i = 2; i < n; ++i) {
//		if (numbers[i] > max1)
//		{
//			int aux = max1;
//			max1 = numbers[i];
//			max2 = aux;
//		}
//		else if (numbers[i] > max2)
//		{
//			max2 = numbers[i];
//		}
//	}
//
//	result = max1 * max2;
//	return result;
//}



// 2n comparaciones.
int64_t MaxPairwiseProductFast(vector<int32_t>& A)
{
	int sz = A.size();

	int index = 0;
	for (int i = 1; i < sz; i++) {
		if (A[i] > A[index]) {
			index = i;
		}
	}
	swap(A, index, sz - 1);

	index = 0;
	for (int i = 1; i < sz - 1; i++) {
		if (A[i] > A[index]) {
			index = i;
		}
	}
	swap(A, index, sz - 2);

	return A[sz - 1] * A[sz - 2];
}

// 1.5n comparaciones.
int64_t MaxPairwiseProductFaster(vector<int32_t>& A)
{
	if (A[0] > A[1])
		swap(A, 0, 1);

	int sz = A.size();
	for (int i = 2; i < sz; i++) {
		if (A[i] > A[0]) {
			swap(A, 0, i);
			if (A[0] > A[1]) {
				swap(A, 0, 1);
			}
		}

		//if (A[i] > A[1]) {
		//	swap(A, 1, 0);
		//	swap(A, i, 1);
		//}
		//else if (A[i] > A[0]) {
		//	swap(A, i, 0);
		//}
	}

	return A[0] * A[1];
}


void stress_test(int N, int M)
{
	int n, m;
	while (true) {
		n = get_rand(2, N);
		vector<int32_t> A(n);
		for (int i = 0; i < n; i++) {
			A[i] = get_rand(0, M);
		}
		for (int i = 0; i < n; i++) {
			cout << A[i] << ' ';
		}
		cout << '\n';
		int64_t result1 = MaxPairwiseProductNaive(A);
		// int64_t result2 = MaxPairwiseProductFast(A);
		int64_t result2 = MaxPairwiseProductFaster(A);
		if (result1 == result2) {
			cout << "Ok" << '\n';
		}
		else {
			cout << "Wrong answer: " << result1 << ' ' << result2 << '\n';
			return;
		}
	}

	return;
}


int main()
{
	// ========================================================
	//int n = 200000;
	//vector<int32_t> numbers(n);
	//for (int i = 0; i < n; ++i) {
	//	numbers[i] = i;
	//}

	//// Use auto keyword to avoid typing long
 //  // type definitions to get the timepoint
 //  // at this instant use function now()
	//auto start = high_resolution_clock::now();

	//long result = MaxPairwiseProductFast(numbers);

	//// After function call
	//auto stop = high_resolution_clock::now();


	//cout << result << '\n';


	//// Subtract stop and start timepoints and
	//// cast it to required unit. Predefined units
	//// are nanoseconds, microseconds, milliseconds,
	//// seconds, minutes, hours. Use duration_cast()
	//// function.
	//auto duration = duration_cast<milliseconds>(stop - start);
	//cout << "Tiempo: " << duration.count() << '\n';
	// ==========================================================

	// ======================================================
	int sz = 2000000;
	int M = 10000000;

	int w1 = 0;
	int w2 = 0;
	while (true) {
		vector<int> A = generate_vec(sz, M);

		auto start = high_resolution_clock::now();
		int64_t result = MaxPairwiseProductFast(A);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
		cout << "FAST Resultado: " << result << '\n';
		cout << "Tiempo:" << duration.count() << '\n';

		start = high_resolution_clock::now();
		int64_t result2 = MaxPairwiseProductFaster(A);
		stop = high_resolution_clock::now();
		auto duration2 = duration_cast<nanoseconds>(stop - start);
		cout << "FASTER Resultado: " << result << '\n';
		cout << "Tiempo:" << duration2.count() << '\n';

		if (duration <= duration2) {
			w1++;
		}
		else {
			w2++;
		}

		cout << "FAST: " << w1 << " FASTER:" << w2 << '\n';


		if (result != result2) {
			cout << "Diferencia!!";
			break;
		}
	}

	// ======================================================


	// Stress test.
	// stress_test(10, 100);

	return 0;
}
