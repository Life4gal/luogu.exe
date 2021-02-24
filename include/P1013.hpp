#include <iostream>
#include <string>
#include <vector>
#include <map>

int P1013()
{
	/*
	 * L K V E
	 *
	 * 1: there must be two digits(must has carry)
	 *  prove:
	 *  let the max one digit is X, base is Z
	 *  if there are no two digits, then X < Z/2(else X + X will carry)
	 *  but if this is the case, there will be a larger maximum X+X(X+X will not carry)
	 *
	 * 2: the base should equal n-1(n is how many letter we have)
	 *  prove:
	 *      because we have carry, the letter '1' must be given
	 *      then '2' must be given, then '3', '4', '5'...'0'
	 *      util 'n-2'(because we only have n-1 letters, 0~n-2)
	 *      if 'n-1' if not equal the base, n-2 + 1 = n - 1 should not be exist
	 *
	 * 3: above two is bullshit
	 *  a one digit X
	 *  X = 0 + X = 1 + (X - 1) = 2 + (X - 2) = ... = (X - 2) + 2 = (X - 1) + 1 = X + 0
	 *  it means if N is how many times X appear in the table, the number X is N - 1
	 *
	 */

	int n;
	std::cin >> n;
	const int base = n - 1;

	std::vector<std::vector<std::string>> table;
	std::map<char, int> count;
	table.resize(n);
	for(auto& v : table)
	{
		v.resize(n);
	}

	// wo store the entire table
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			std::cin >> table[i][j];
			if(i != 0 && j != 0)
			{
				if(auto s = table[i][j]; s.length() == 1)
				{
					// only count single character
					++count[s[0]];
				}
			}
		}
	}

	// real number is time - 1
	for(auto& [first, second] : count)
	{
		--second;
	}

	// for the real table
	for(int i = 1; i < n; ++i)
	{
		for(int j = 1; j < n; ++j)
		{
			// current pos given value
			int value = 0;
			for(auto c : table[i][j])
			{
				value = value * base + count[c];
			}

			// the value it should be
			int x = count[table[i][0][0]];
			int y = count[table[0][j][0]];
			if(x + y != value)
			{
				std::cout << "ERROR!" << std::endl;
				return 0;
			}
		}
	}

	for(int i = 1; i < n; ++i)
	{
		auto c = table[0][i][0];
		std::cout << c << '=' << count[c] << ' ';
	}
	std::cout << '\n' << base << std::endl;

	return 0;
}
