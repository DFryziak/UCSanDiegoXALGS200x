#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
	int start, end;
};

bool intersect(Segment a, Segment b) {
	return a.start <= b.end && a.end >= b.start;
}

Segment intersection(Segment a, Segment b) {
	int start = std::max(a.start, b.start);
	int end = std::min(a.end, b.end);
	Segment s = { start,end };
	return s;
}

// Hay un test que no pasa pero no tengo mas informacion sobre el test.
vector<int> optimal_points2(vector<Segment> &segments) {
	vector<int> points;
	//write your code here
	vector<int> visited(segments.size());
	for (size_t i = 0; i < segments.size(); ++i) {
		if (visited[i]) continue;
		Segment inters = segments[i];
		for (size_t j = i + 1; j < segments.size(); j++) {
			if (visited[j]) continue;
			if (intersect(inters, segments[j])) {
				inters = intersection(inters, segments[j]);
				visited[j] = 1;
			}
		}

		points.push_back(inters.start);
		visited[i] = 1;
	}

	return points;
}

int selectMinRight(vector<Segment> segments) {

	int minRight = 0;
	for (size_t i = 1; i < segments.size(); i++) {
		if (segments[i].end < segments[minRight].end) {
			minRight = i;
		}
	}

	return minRight;
}

void swap(vector<Segment> &segments, int i, int j) {

	Segment aux = segments[i];
	segments[i] = segments[j];
	segments[j] = aux;
}

bool includes(Segment segment, int point) {

	return point >= segment.start && point <= segment.end;
}

vector<int> optimal_points(vector<Segment> &segments) {
	vector<int> points;
	
	//write your code here
	while (segments.size() > 0) {
		
		vector<int> visited;
		int minR = selectMinRight(segments); // elijo el mejor candidato;
		
		for (size_t i = 0; i < segments.size(); i++) {
			if (includes(segments[i], segments[minR].end)) {
				visited.push_back(i);
			}
		}

		points.push_back(segments[minR].end);

		std::sort(visited.rbegin(), visited.rend());
		for (size_t i = 0; i < visited.size(); i++) {
			swap(segments, visited[i], segments.size() - 1);
			segments.pop_back();
		}
	}

	return points;
}

int main() {
	int n;
	std::cin >> n;
	vector<Segment> segments(n);
	for (size_t i = 0; i < segments.size(); ++i) {
		std::cin >> segments[i].start >> segments[i].end;
	}
	vector<int> points = optimal_points(segments);
	std::cout << points.size() << "\n";
	for (size_t i = 0; i < points.size(); ++i) {
		std::cout << points[i] << " ";
	}
}
