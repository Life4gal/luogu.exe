#include <algorithm>
#include <vector>

int P1020() {

	std::vector<int> data;

	// work for me buf not work for https://godbolt.org/ (Program returned: 137)
//	std::cin >> std::noskipws;
//	while (true) {
//		int t;
//		std::cin >> t;
//		data.push_back(t);
//		if(std::cin.get() == '\n') break;
//	}

	// work on https://godbolt.org/ but not work for me (endless scan)
	{
		int t;
		while (scanf("%d", &t) != EOF)
		{
			data.push_back(t);
		}
	}

	decltype(data) not_ascending;
	decltype(data) ascending;

	not_ascending.resize(data.size());
	ascending.resize(data.size());

	not_ascending.front() = data.front();
	ascending.front() = data.front();

	int max = 0;
	int total = 0;
	for (auto i = 1; i < data.size(); ++i) {
		const auto& curr = data[i];
		if (not_ascending[max] >= curr) {
			not_ascending[++max] = curr;
		} else {
			auto pos = std::upper_bound(not_ascending.begin(), not_ascending.begin() + max, curr, std::greater<>{}) - not_ascending.begin();
			not_ascending[pos] = curr;
		}

		if (ascending[total] < curr) {
			ascending[++total] = curr;
		} else {
			auto pos = std::lower_bound(ascending.begin(), ascending.begin() + total, curr) - ascending.begin();
			ascending[pos] = curr;
		}
	}

	std::cout << ++max << '\n'
			  << ++total << std::endl;

	return 0;
}
