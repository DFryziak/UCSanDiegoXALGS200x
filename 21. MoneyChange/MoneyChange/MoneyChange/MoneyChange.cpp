#include <iostream>
#include <vector>

using std::vector;

int get_change(int money) {
	// The minimum number of coins with denominations
	//	1, 3, 4 that changes money.

	int infinite = 1001; // El max valor del argumento es 10^3, por lo tanto puedo usar como valor de infinito a 10^3+1
	vector<int> coins = { 1, 3, 4 };
	vector<int> min_num_coins(money + 1);

	min_num_coins[0] = 0; // Para cambiar 0 dinero se necesitan como maximo 0 monedas. Esto es como el caso base de la recursion.
	// Se calcula el valor optimo de monedas para cambiar todas las cantidades de dinero hasta money.
	// Por cada cantidad de dinero pregunto por el valor optimo de monedas que necesito para
	// cambiar m - coins[i] y me quedo con el minimo de todas las opciones.
	for (int m = 1; m <= money; m++) {
		min_num_coins[m] = infinite;
		for (int i = 0; i < coins.size(); i++) {
			if (m >= coins[i]) {
				if (min_num_coins[m - coins[i]] + 1 < min_num_coins[m]) {
					min_num_coins[m] = min_num_coins[m - coins[i]] + 1;
				}
			}
		}
	}

	return min_num_coins[money];
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
