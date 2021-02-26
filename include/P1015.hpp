#include <iostream>
#include <string>

constexpr bool is_palindrome_number(const std::string_view& str)
{
	const auto half = str.length() / 2;
	return lexicographical_equal(str.cbegin(), str.cbegin() + half, str.crbegin(), str.crbegin() + half);
}

int P1015()
{
	int base;
	std::cin >> base;

	std::string num;
	std::cin >> num;

	for(int i = 0; i < 30; ++i)
	{
		if(is_palindrome_number(num[0] == '0' ? num.data() + 1 : num.data()))
		{
			std::cout << "STEP=" << i << std::endl;
			return 0;
		}

		decltype(num) t;
		if(num[0] != '0')
		{
			t = {num.begin(), num.begin() + num.length()};
			num.insert(0, "0");
		}
		else
		{
			t = {num.begin() + 1, num.begin() + num.length()};
		}
		add(base, num.rbegin(), t.begin(), t.end());
	}

	std::cout << "Impossible!" << std::endl;

	return 0;
}
