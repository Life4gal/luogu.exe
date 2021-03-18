#include <iomanip>
#include <iostream>
#include <string>

int P1022() {
	constexpr auto is_equal = [](char c) constexpr->bool {
		return c == '=';
	};
	constexpr auto is_letter = [](char c) constexpr->bool {
		return c >= 'a';
	};

	std::string str;
	std::cin >> str;

	double total = 0;
	double coefficient = 0;
	bool pass_equal = false;
	char x;

	const char* p = str.c_str();
	for (size_t index = 0; p[index];) {
		char* end;
		auto curr = std::strtod(p, &end);

		if (p == end) {
			if (is_letter(*end)) {
				x = *end;

				// a '+' in begin (or nothing in front of x)
				coefficient += pass_equal ? -1 : 1;

				// skip this letter
				++end;
			} else {
				if (!is_equal(*end)) {
					// a '-' in begin
					coefficient += pass_equal ? 1 : -1;

					// skip this '-' and the letter behind
					end += 2;
				}
				else
				{
					pass_equal = true;

					// skip this '='
					++end;
				}
			}
		} else if (is_letter(*end)) {
			// todo: duplicate code
			x = *end;
			// let letter in left
			coefficient += pass_equal ? -curr : curr;

			// skip this letter
			++end;
		} else {
			// let digit in right
			total += pass_equal ? curr : -curr;
			// todo: duplicate code
			if (!pass_equal && is_equal(*end)) {
				pass_equal = true;

				// skip this '='
				++end;
			}
		}
		p = end;
	}

	if (total == 0) {
		std::cout << x << "=0.000" << std::endl;
	} else {
		std::cout << x << '=' << std::fixed << std::setprecision(3) << total / coefficient << std::endl;
	}

	return 0;
}
