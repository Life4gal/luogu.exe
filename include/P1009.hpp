#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int P1009() {
	int n;
	std::cin >> n;

	constexpr auto length = 64;
	std::vector<int> sum;
	sum.resize(length);

	std::vector<int> str;
	str.resize(length);
	str.back() = 1;

	auto multi = [&str](int n) {
		int carry = 0;
		for (auto it = str.rbegin(); it != str.rend(); ++it) {
			*it = *it * n + carry;
			carry = *it / 10;
			*it %= 10;
			// this overhead will be reasonable if there is a huge data
			// generally speaking, the carry will not be more than 1,
			// if the distance between the current iterator and the last significant digit is less than 1,
			// then subsequent operations will not affect the result
			if(carry == 0 && std::distance(it, static_cast<decltype(str)::reverse_iterator>(std::find_if(str.begin(), str.end(), [](auto i){return i != 0;}))) <= 1)
			{
				return;
			}
		}
	};

	auto plus = [&sum, &str]() {
		int carry = 0;
		for (auto str_it = str.rbegin(), sum_it = sum.rbegin(); str_it != str.rend() && sum_it != sum.rend(); ++str_it, ++sum_it) {
			*sum_it += *str_it + carry;
			carry = *sum_it / 10;
			*sum_it %= 10;
			// this overhead will be reasonable if there is a huge data
			// generally speaking, the carry will not be more than 1,
			// if the distance between the current iterator and the last significant digit is less than 1,
			// then subsequent operations will not affect the result
			if(carry == 0 && std::distance(str_it, static_cast<decltype(str)::reverse_iterator>(std::find_if(str.begin(), str.end(), [](auto i){return i != 0;}))) <= 1)
			{
				return;
			}
		}
	};

	for (int i = 1; i <= n; ++i) {
		multi(i);
		plus();
	}

	std::copy(
			std::find_if(sum.begin(), sum.end(), [](auto i) { return i != 0; }),
			sum.end(),
			std::ostream_iterator<int>(std::cout));
	std::cout << std::endl;

	return 0;
}
