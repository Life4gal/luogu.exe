#include <charconv>
#include <functional>

int P1018() {
	int n;
	int k;

	std::cin >> n >> k;

	std::vector<int> input;
	input.reserve(n);

	for (int i = 0; i < n; ++i) {
		char c;
		std::cin >> c;
		input.push_back(c - '0');
	}

	using ResultType = __int128;

	auto accumulate = [&input](auto begin, auto end) -> ResultType {
		ResultType ret = 0;
		for (; begin < end; ++begin) {
			ret += input[begin];
			ret *= 10;
		}
		ret += input[end];
		return ret;
	};

	// we need recursive call this function, so it can not be a lambda but a wrapped function
	std::function<ResultType(int, int)> dfs_search;

	dfs_search = [&dfs_search, &accumulate](int x, int remainder) -> ResultType {
		if (remainder == 0) return accumulate(0, x - 1);

		ResultType max = 0;
		for (auto i = x - 1; i >= remainder - 1; --i) {
			auto multi = dfs_search(i, remainder - 1);
			auto curr = accumulate(i, x - 1);
			if (auto r = multi * curr; r > max) {
				max = r;
			}
		}
		return max;
	};

	std::cout << dfs_search(n, k) << std::endl;

	return 0;
}
