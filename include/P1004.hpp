#include <iostream>
#include <support.hpp>

int P1004() {
	int field[12][12]{};
	int step[12][12][12][12]{};

	int n;
	std::cin >> n;
	while (true) {
		int x;
		int y;
		int value;
		std::cin >> x >> y >> value;
		if (x == 0 && y == 0) {
			break;
		}
		field[x][y] = value;
	}
	for (auto p1_x = 1; p1_x <= n; ++p1_x) {
		for (auto p1_y = 1; p1_y <= n; ++p1_y) {
			for (auto p2_x = 1; p2_x <= n; ++p2_x) {
				for (auto p2_y = 1; p2_y <= n; ++p2_y) {
					step[p1_x][p1_y][p2_x][p2_y] = max(
							step[p1_x - 1][p1_y][p2_x - 1][p2_y],
							step[p1_x - 1][p1_y][p2_x][p2_y - 1],
							step[p1_x][p1_y - 1][p2_x - 1][p2_y],
							step[p1_x][p1_y - 1][p2_x][p2_y - 1]);

					auto value = field[p1_x][p1_y] + field[p2_x][p2_y];
					if (p1_x == p2_x && p1_y == p2_y) {
						step[p1_x][p1_y][p2_x][p2_y] += value / 2;
					} else {
						step[p1_x][p1_y][p2_x][p2_y] += value;
					}
				}
			}
		}
	}
	std::cout << step[n][n][n][n];

	return 0;
}