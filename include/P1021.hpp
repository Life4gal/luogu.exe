#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>

int P1021() {
	int n;
	int k;
	std::cin >> n >> k;

	std::function<void(int)> dfs_search;

	auto max = 0;
	std::array<int, 45> candidate{0, 1};

	std::vector<int> selected;
	selected.resize(k);

	dfs_search = [&dfs_search, n, k, &max, &candidate, &selected](int curr) -> void {
		// size maybe not enough, but... it is enough for this
		constexpr auto max_size = 500;
		constexpr auto INF = 1e7;

		std::array<int, max_size> arr{};
		std::fill(arr.begin() + 1, arr.end(), INF);

		int curr_max = 1;
		for (;; ++curr_max) {
			auto& v = arr[curr_max];
			for (auto i = 1; i < curr && candidate[i] <= curr_max; ++i) {
				v = std::min(v, arr[curr_max - candidate[i]] + 1);
			}
			if (v > n) break;
		}
		--curr_max;

		if (curr_max > max) {
			max = curr_max;
			std::copy_n(candidate.begin() + 1, k, selected.begin());
		}
		if (curr == k + 1) return;

		for (auto i = candidate[curr - 1] + 1; i <= curr_max + 1; ++i) {
			candidate[curr] = i;
			dfs_search(curr + 1);
		}
	};

	dfs_search(2);
	for (auto i: selected) {
		std::cout << i << ' ';
	}
	std::cout << "\nMAX=" << max << std::endl;

	return 0;
}
