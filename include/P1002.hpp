#include <iostream>

struct point {
	int x;
	int y;
	constexpr void operator++(int i) {
		x += i;
		y += i;
	}
};

int P1002() {
	constexpr int danger_point_count = 9;
	constexpr point danger_point[danger_point_count] =
			{
					{0, 0},
					{-2, 1},
					{-1, 2},
					{1, 2},
					{2, 1},
					{2, -1},
					{1, -2},
					{-1, -2},
					{-2, -1}};


	point bound{};
	point horse{};
	std::cin >> bound.x >> bound.y >> horse.x >> horse.y;

	constexpr auto size = 22;
	long path[size][size] = {};
	bool danger[size][size] = {};

	bound.operator++(1);
	horse.operator++(1);

	for (const auto& [x, y]: danger_point) {
		danger[horse.x + x][horse.y + y] = true;
	}

	path[0][1] = 1;
	// or path[1][0] = 1; just let p[1][1] is not 0 (let it is 1)
	for (auto i = 1; i <= bound.x; ++i) {
		for (int j = 1; j <= bound.y; ++j) {
			path[i][j] = (path[i - 1][j] + path[i][j - 1]) * (!danger[i][j]);
		}
	}

	std::cout << path[bound.x][bound.y] << std::endl;

	return 0;
}
