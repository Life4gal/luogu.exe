#include <iostream>
#include <bitset>

struct size
{
	int min;
	int max;
};

int P1008()
{
	constexpr size size3 = {576, 987};

	// not include 0
	std::bitset<9> bs;
	auto check_exist = [&bs](int digit) -> bool
	{
		auto a = digit / 100;
		if(bs.test(a - 1)) return true;
		bs[a - 1] = true;

		auto b = (digit - a * 100) / 10;
		if(b == 0 || bs.test(b - 1)) return true;
		bs[b - 1] = true;

		auto c = digit - a * 100 - b * 10;
		if(c == 0 || bs.test(c - 1)) return true;
		bs[c - 1] = true;

		return false;
	};

	for(int i = size3.min; i <= size3.max; i += 3)
	{
		if(int j = i / 3; !check_exist(i) && !check_exist(j) && !check_exist(j * 2))
		{
			std::cout << j << ' ' << 2 * j << ' ' << i << '\n';
		}
		bs &= 0;
	}

	return 0;
}
