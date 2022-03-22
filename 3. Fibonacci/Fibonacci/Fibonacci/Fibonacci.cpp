

#include <iostream>
#include <vector>
#include "FiboStarter.h"
#include "FiboLastDigitStarter.h"
using namespace std;

int64_t fib_list(int n)
{
	if (n <= 1)
		return n;

	vector<int64_t> v(n + 1);

	v[0] = 0;
	v[1] = 1;
	for (size_t i = 2; i < v.size(); i++) {
		v[i] = v[i - 1] + v[i - 2];
	}

	return v[n];
}

int fib_recurs(int n)
{
	if (n <= 1) {
		return n;
	}

	return fib_recurs(n - 1) + fib_recurs(n - 2);
}

int main()
{
	// Recursive
	//for (size_t i = 100; i < 101; i++) {
	//	cout << i << ": " << fib_recurs(i) << '\n';
	//}

	// Iterative
	//int n = 100;
	//cout << n << ": " << fib_list(n) << '\n';
	//for (size_t i = 0; i < 50; i++) {
	//	cout << i << ": " << fib_list(i) << '\n';
	//}

	// FiboStarter::main();
	FiboLastDigitStarter::main();
}


