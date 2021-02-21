#include <iostream>

struct point {
	int x;
	int y;
	void operator++(int i) {
		x += i;
		y += i;
	}
};

int P1002() {
	point bound{};
	point horse{};
	std::cin >> bound.x >> bound.y >> horse.x >> horse.y;

	constexpr auto size = 21;
	long path[size][size] = {};
	bool danger[size][size] = {};

	constexpr int danger_x[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
	constexpr int danger_y[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};

	bound.operator++(1);
	horse.operator++(1);
	path[0][1] = 1;

	for (int i = 0; i < 9; ++i) {
		danger[horse.x + danger_x[i]][horse.y + danger_y[i]] = true;
	}
	for (int i = 1; i <= bound.x; ++i) {
		for (int j = 1; j <= bound.y; ++j) {
			path[i][j] = (path[i - 1][j] + path[i][j - 1]) * (!danger[i][j]);
		}
	}

//	for (int i = 0; i < size; ++i) {
//		for(int j = 0; j < size; ++j)
//		std::cout << "[" << i << "][" << j << "] : " << path[i][j] << std::endl;
//	}

	// why check-point 1 Runtime-Error ?
	std::cout << path[bound.x][bound.y] << std::endl;

	return 0;
}
