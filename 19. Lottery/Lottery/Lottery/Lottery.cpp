#include <iostream>
#include <vector>

using std::vector;
using std::swap;

// Basado en el problema de la bandera de Holanda de Dijkstra. Tengo un pdf en la carpeta del curso.
vector<long long> partition_dutch_flag(vector<long long> &a, long long l, long long r)
{
	vector<long long> m(2);

	long long pivot = a[l];

	long long h = l + 1;
	long long k = l + 1;
	long long t = r + 1;

	while (k < t) {
		if (a[k] < pivot) {
			swap(a[h], a[k]);
			h++;
			k++;
		}
		else if (a[k] == pivot) {
			k++;
		}
		else {
			t--;
			swap(a[k], a[t]);
		}
	}

	h--;
	swap(a[l], a[h]);

	m[0] = h;
	m[1] = t - 1;

	return m;
}


void randomized_quick_sort(vector<long long> &a, long long l, long long r) {
	if (l >= r) {
		return;
	}

	long long k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	// vector<long long> m = partition3(a, l, r);
	vector<long long> m = partition_dutch_flag(a, l, r);

	randomized_quick_sort(a, l, m[0] - 1);
	randomized_quick_sort(a, m[1] + 1, r);
}

long long binary_search(const vector<long long> &a, long long left, long long right, long long x) {

	//write your code here
	while (left <= right) {

		long long mid = (long long)((left + right) * .5);

		if (x == a[mid]) {
			return mid;
		}
		else if (x < a[mid]) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	return left - 1;
}


//vector<long long> fast_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points) {
//
//	vector<long long> cnt(points.size());
//
//	vector<long long> startCopy(starts.size());
//	for (long long i = 0; i < starts.size(); i++) {
//		startCopy[i] = starts[i];
//	}
//
//	vector<long long> endsCopy(starts.size());
//	for (long long i = 0; i < ends.size(); i++) {
//		endsCopy[i] = ends[i];
//	}
//
//	randomized_quick_sort(starts, endsCopy, 0, starts.size() - 1);
//	randomized_quick_sort(ends, startCopy, 0, starts.size() - 1);
//
//	for (long long i = 0; i < points.size(); i++) {
//		long long  h = binary_search(starts, 0, starts.size() - 1, points[i]);
//		long long t = binary_search(ends, 0, ends.size() - 1, points[i]);
//
//		if (h < starts.size() - t) {
//			if (h >= 0) {
//				for (long long j = 0; j <= h; j++) {
//					if (ends[j] >= points[i]) {
//						cnt[i]++;
//					}
//				}
//			}
//		}
//		else {
//			if (t + 1 < starts.size()) {
//				for (long long j = t + 1; j < starts.size(); j++) {
//					if (starts[j] <= points[i]) {
//						cnt[i]++;
//					}
//				}
//			}
//		}
//	}
//
//	return cnt;
//}

vector<long long> fast_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points) {

	vector<long long> cnt(points.size());

	// Ordeno.
	randomized_quick_sort(starts, 0, starts.size() - 1);
	randomized_quick_sort(ends, 0, ends.size() - 1);

	for (long long i = 0; i < points.size(); i++) {
		long long t = 0;

		long long h = binary_search(starts, 0, starts.size() - 1, points[i]);

		if (h == -1) {
			// Todos los segmentos comienzan luego del valor buscado, por lo tanto
			// el valor no es contenido por ningun segmento.
			continue;
		}

		while (h + 1 < starts.size() && starts[h + 1] == points[i]) {
			h++;
		}

		if (h < starts.size()) {
			// Sumo los segmentos que comienzan luego del valor.
			t += starts.size() - (h + 1);
		}

		long long l = binary_search(ends, 0, ends.size() - 1, points[i]);

		// Si es -1 no hay nada que descartar pq todos terminan despues.
		if (l != -1) {
			while (l >= 0 && ends[l] == points[i]) {
				l--;
			}

			t += l + 1;
		}

		cnt[i] = starts.size() - t;
	}

	return cnt;
}


vector<long long> naive_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points) {
	vector<long long> cnt(points.size());
	for (long long i = 0; i < points.size(); i++) {
		for (long long j = 0; j < starts.size(); j++) {
			cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
		}
	}
	return cnt;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	vector<long long> starts(n), ends(n);
	for (long long i = 0; i < starts.size(); i++) {
		std::cin >> starts[i] >> ends[i];
	}
	vector<long long> points(m);
	for (long long i = 0; i < points.size(); i++) {
		std::cin >> points[i];
	}
	// use fast_count_segments
	// vector<long long> cnt = naive_count_segments(starts, ends, points);
	vector<long long> cnt = fast_count_segments(starts, ends, points);
	for (long long i = 0; i < cnt.size(); i++) {
		std::cout << cnt[i] << ' ';
	}
}
