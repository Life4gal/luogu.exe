#include <iostream>
#include <functional>

int P1017()
{
	/*
	 * calc result from back to front
	 * if the base is negative number, the remainder maybe less than 0
	 * | remainder | (<-- it is abs(remainder)) must less than | base | (<-- it is abs(base))
	 * so (remainder - base) must be greater than 0
	 *
	 * n = -15, base = -2:
	 *      n % base --> -15 % -2 = -1 --> remainder
	 *      n / base --> -15 / -2 = 7  --> quotient
	 *      base * quotient + remainder --> 7 * -2 + -1 = -15 = n
	 *
	 *      (quotient + 1) * base + (remainder - base)
	 *      --> quotient * base + base + remainder - base
	 *      --> quotient * base + remainder
	 *      --> n
	 */

	int n;
	int base;

	std::cin >> n >> base;

	// we need recursive call this function, so it can not be a lambda but a wrapped function
	std::function<void(int, int)> calc;

	calc = [&calc](int n, int base) -> void
	{
		if(n == 0) return;

		auto remainder = n % base;
		// remainder should greater than 0
		if(remainder < 0)
		{
			remainder -= base;
			n += base;
		}

		if(remainder >= 10)
		{
			remainder = remainder - 10 + 'A';
		}
		else
		{
			remainder += '0';
		}

		// from back to front
		calc(n / base, base);

		std::cout.put(remainder);
	};

	std::cout << n << '=';
	calc(n, base);

	std::cout << "(base" << base << ')' << std::endl;

	return 0;
}
