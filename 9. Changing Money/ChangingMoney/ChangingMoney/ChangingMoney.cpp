#include <iostream>

int get_change1(int m) {
	//write your code here

	int n = 0;
	int r = 0;

	n += m / 10;
	
	r = m % 10;

	n += r / 5;

	r = r % 5;

	n += r;

	return n;
}

int get_change2(int m) {
	//write your code here

	int n = 0;

	while (m > 0) {
		if (m >= 10) {
			m -= 10;
			n++;
		}
		else if (m >= 5) {
			m -= 5;
			n++;
		}
		else {
			n += m;
			m = 0;
		}
	}

	return n;
}

int get_change(int m) {
	return std::floor(m / 10) + std::floor((m % 10) / 5) + std::floor(m % 5);
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
