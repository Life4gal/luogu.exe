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

	constexpr auto size = 23;
	long path[size][size]{};
	bool danger[size][size]{};

	bound.operator++(2);
	horse.operator++(2);

	for (const auto& [x, y]: danger_point) {
		danger[horse.x + x][horse.y + y] = true;
	}

	// the same as path[2][1] = 1; it just let path[2][2] = 1
	path[1][2] = 1;
	for (auto i = 2; i < bound.x + 1; ++i) {
		for (auto j = 2; j < bound.y + 1; ++j) {
			path[i][j] = (path[i - 1][j] + path[i][j - 1]) * (!danger[i][j]);
		}
	}

	std::cout << path[bound.x][bound.y] << std::endl;

	return 0;
}
