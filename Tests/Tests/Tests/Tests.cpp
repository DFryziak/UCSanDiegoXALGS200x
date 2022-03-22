// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int multiply(int x, int y) {

	if (y == 0) return 0;

	int z = multiply(x, int(y / 2));

	if (y % 2 == 0) {
		return 2 * z;
	}
	else {
		return x + 2 * z;
	}

}


int main()
{
	int x, y;
	std::cin >> x;
	std::cin >> y;


	std::cout << multiply(x, y);
}

