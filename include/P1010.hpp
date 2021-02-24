#include <iostream>
#include <string>

std::string calc_times(int digit, int times = {}, std::string str = {})
{
	if(digit == 0) return "0";
	do {
		if(digit & 1)
		{
			// store current str
			auto curr = std::move(str);

			// get a new str
			if(times == 1)
			{
				str = '2';
			}
			else
			{
				str = "2(" + calc_times(times) + ')';
			}

			// if current str is not empty, append a '+'
			if(!curr.empty())
			{
				str.push_back('+');
			}
			// append current str to new str
			str.append(curr);
		}
	}
	while(++times, digit>>=1);
	return str;
}

int P1010()
{
	int n;
	std::cin >> n;
	std::cout << calc_times(n) << std::endl;

	return 0;
}
