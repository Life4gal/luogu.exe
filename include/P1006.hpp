#include <iostream>
#include <vector>
#include <support.hpp>

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

				if (k - i < 0 || k - j < 0) continue;

				step[k][i][j] = max(
						step[k - 1][i][j],
						step[k - 1][i - 1][j - 1],
						step[k - 1][i][j - 1],
						step[k - 1][i - 1][j]);

				auto value = field[i][k - i + 1] + field[j][k - j + 1];
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
