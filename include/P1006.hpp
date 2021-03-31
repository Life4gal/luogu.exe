#include <iostream>
#include <support.hpp>
#include <vector>

int P1006() {
	int n;
	int m;
	std::cin >> n >> m;
	const auto extent_n = n + 1;
	const auto extent_m = m + 1;
	const auto extent_size = m + n;

	std::vector<std::vector<int>> field{static_cast<size_t>(extent_n)};
	for (auto& v: field) {
		v.resize(extent_m);
	}

	// two people start from the upper left corner at the same time, taking disjoint routes
	// (their coordinates must be on the same oblique line, and the sum of the horizontal and vertical coordinates is the same)
	// top-level size means the sum of a point's coordinate (x + y) (or means how many steps are currently moved)
	// then the nested-level size and the nested-nested-level size means person1 and person2's horizontal coordinate (use vertical also ok)
	std::vector<std::vector<std::vector<int>>> step{static_cast<size_t>(extent_size)};
	for (auto& v1: step) {
		v1.resize(extent_n);
		for (auto& v2: v1) {
			v2.resize(extent_n);
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			std::cin >> field[i][j];
		}
	}

	for (int k = 1; k < extent_size; ++k) {
		for (int i = 1; i < extent_n; ++i) {
			for (int j = 1; j < extent_n; ++j) {
				// if((k + 1) - i < 1 || (k + 1) - j < 1)
				// is current vertical coordinate valid ?
				if (k - i < 0 || k - j < 0) continue;

				// this step
				step[k][i][j] = max(
						// move down from last step (horizontal coordinate not changed)
						step[k - 1][i][j],
						// move right from last step
						step[k - 1][i - 1][j - 1],
						// p1 move down, p2 move right
						step[k - 1][i][j - 1],
						// p1 move right, p2 move down
						step[k - 1][i - 1][j]);

				// the value of their location
				auto value = field[i][k + 1 - i] + field[j][k + 1 - j];
				// if is the same location, just get the value once
				if (i == j) {
					step[k][i][j] += value / 2;
				} else {
					step[k][i][j] += value;
				}
			}
		}
	}

	std::cout << step[extent_size - 1][extent_n - 1][extent_n - 1] << std::endl;

	return 0;
}
