#include <iostream>
#include <functional>

int P1017()
{
	/*
	 * calc result from back to front
	 * if the base is negative number, the remainder maybe less than 0
	 *
	 * n = -15, base = -2:
	 *      n % base --> -15 % -2 = -1 --> remainder
	 *      n / base --> -15 / -2 = 7  --> quotient
	 *      base * quotient + remainder --> 7 * -2 + -1 = -15 = n
	 *
	 * | remainder | (<-- it is abs(remainder)) must less than | base | (<-- it is abs(base))
	 * so (remainder - base) must be greater than 0
	 *
	 *      base * quotient + remainder
	 *      --> (base * quotient + base) + (remainder - base)
	 */

	int n;
	int base;

	std::cin >> n >> base;

	// we need recursive call this function, so it can not be a lambda but a wrapped function
	std::function<void(int)> calc;

	calc = [&calc, base](int n) -> void
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
			remainder += -10 + 'A';
		}
		else
		{
			remainder += '0';
		}

		// from back to front
		calc(n / base);

		std::cout.put(remainder);
	};

	std::cout << n << '=';
	calc(n);

	std::cout << "(base" << base << ')' << std::endl;

	return 0;
}
