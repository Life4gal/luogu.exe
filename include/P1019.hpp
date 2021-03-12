#include <functional>
#include <vector>

int P1019() {
	int n;
	std::cin >> n;

	struct node
	{
		std::string str;
		int used;
	};

	std::vector<node> data;
	data.reserve(n + 1);

	for (int i = 0; i <= n; ++i) {
		std::string t;
		std::cin >> t;
		data.push_back({std::move(t), 0});
	}

	auto collide_checker = [](std::string_view str1, std::string_view str2) -> int {
		const auto l1 = str1.length();
		const auto l2 = str2.length();

		// traverse the shorter str from the back
		for (auto i = 1; i < std::min(l1, l2); ++i) {
			// try to find a same sub-string
			bool found = true;
			for (auto j = 0; j < i; ++j) {
				// traverse str1 from the back, str2 from the front
				if (str1[l1 - i + j] != str2[j]) {
					found = false;
					break;
				}
			}
			if(found)
			{
				return i;
			}
		}
		return 0;
	};

	// we need recursive call this function, so it can not be a lambda but a wrapped function
	std::function<void(std::string_view, int)> dfs_search;

	int max_length = 0;
	dfs_search = [&dfs_search, &data, &collide_checker, &max_length](std::string_view str, int curr_length)
	{
		max_length = std::max(max_length, curr_length);
		for(auto& [s, used] : data)
		{
			if(used >= 2) continue;
			if(auto collided = collide_checker(str, s); collided > 0)
			{
				++used;
				dfs_search(s, curr_length + s.length() - collided);
				--used;
			}
		}
	};

	// collide_checker start check from str[length - 1], so the first single character always return 0
	dfs_search(' ' + data[n].str, 1);

	std::cout << max_length << std::endl;

	return 0;
}
