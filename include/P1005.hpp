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

	std::vector<std::vector<AnsType>> field;
	field.reserve(extent_size);
	for(int i = 0; i < extent_size; ++i)
	{
		std::vector<AnsType> v;
		v.reserve(extent_size);
		for(int j = 0; j < extent_size; ++j)
		{
			v.push_back(0);
		}
		field.push_back(std::move(v));
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

// copy from https://stackoverflow.com/questions/25114597/how-to-print-int128-in-g
std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
	std::ostream::sentry s( dest );
	if ( s ) {
		__uint128_t tmp = value < 0 ? -value : value;
		char buffer[ 128 ];
		char* d = std::end( buffer );
		do
		{
			-- d;
			*d = "0123456789"[ tmp % 10 ];
			tmp /= 10;
		} while ( tmp != 0 );
		if ( value < 0 ) {
			-- d;
			*d = '-';
		}
		int len = std::end( buffer ) - d;
		if ( dest.rdbuf()->sputn( d, len ) != len ) {
			dest.setstate( std::ios_base::badbit );
		}
	}
	return dest;
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
