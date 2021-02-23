#include <iostream>
#include <vector>
#include <support.hpp>

using AnsType = __int128;

auto calc_sum(std::vector<int>&& vec)
{
	int size = vec.size();
	int extent_size = size + 2;
	vec.insert(vec.begin(), 0);
	vec.push_back(0);

	std::vector<std::vector<AnsType>> field{static_cast<size_t>(extent_size)};
	for(auto& v : field)
	{
		v.resize(extent_size);
	}

	for(int i = 0; i <= size; ++i)
	{
		for(int j = 1; j + i <= size; ++j)
		{
			field[j][j + i] = max(2 * field[j+1][j+i] + 2 * vec[j], 2 * field[j][j + i - 1] + 2 * vec[j + i]);
		}
	}
	return field[1][size];
}

int P1005()
{
	int n;
	int m;
	std::cin >> n >> m;
	std::vector<int> vec;
	AnsType max = 0;
	for(auto i = 0; i < n; ++i)
	{
		for(auto j = 0; j < m; ++j)
		{
			int v;
			std::cin >> v;
			vec.push_back(v);
		}
		max += calc_sum(std::move(vec));
		vec.clear();
	}

	std::cout << max << std::endl;

	return 0;
}
