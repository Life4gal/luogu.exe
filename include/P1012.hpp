#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

bool numeric_compare_greater(const std::string& str1, const std::string& str2)
{
	auto length1 = str1.length();
	auto length2 = str2.length();
	if(length1 == length2) return str1 > str2;

	bool longer = length1 > length2;
	auto length = longer ? length2 : length1;
	if(auto r = std::equal(str1.begin(), str1.begin() + length, str2.begin()); !r)
	{
		return str1 > str2;
	}
	if(longer)
	{
		return str1[length] < str2[0];
	}
	else
	{
		return str2[length] < str1[0];
	}
}

int P1012()
{
	int n;
	std::cin >> n;
	std::vector<std::string> vec;
	vec.resize(n);
	for(auto& s : vec)
	{
		std::cin >> s;
	}

	std::sort(vec.begin(), vec.end(), numeric_compare_greater);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout));
	return 0;
}
