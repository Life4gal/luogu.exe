#ifndef SUPPORT_HPP
#define SUPPORT_HPP

template<typename T, typename U, typename... More>
constexpr auto max(T&& t, U&& u, More&&... more) {
	if constexpr (sizeof...(more) == 0) {
		return t > u ? t : u;
	} else {
		return max(max(t, u), more...);
	}
}

template<typename T, typename U, typename... More>
constexpr auto min(T&& t, U&& u, More&&... more) {
	if constexpr (sizeof...(more) == 0) {
		return u > t ? t : u;
	} else {
		return min(min(t, u), more...);
	}
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

template<typename InputIterator1, typename InputIterator2>
constexpr bool lexicographical_equal(InputIterator1 begin1, InputIterator1 end1, InputIterator2 begin2, InputIterator2 end2)
{
	for(; (begin1 != end1) && (begin2 != end2); ++begin1, ++begin2)
	{
		if(*begin1 != *begin2) return false;
	}

	return (begin1 == end1) && (begin2 == end2);
}

template<typename DestInputIterator, typename SourceInputIterator>
constexpr void add(int base, DestInputIterator dest, SourceInputIterator begin, SourceInputIterator end)
{
	constexpr auto c2d = [](char c)
	{
		if(c >= '0' && c <= '9') return c - '0';
		else if(c >= 'a' && c <= 'z') return c - 'a' + 10;
		else if(c >= 'A' && c <= 'Z') return c - 'A' + 10;
		return 0;
	};

	constexpr auto d2c = [](int d)
	{
		if(d >= 0 && d <= 9) return d + '0';
		else if(d >= 10 && d <= 16) return d - 10 + 'A';
		else return 0;
	};

	for(int total_carry = 0, times = 0; ; ++times, ++begin, ++dest)
	{
		int dest_num = c2d(*dest);
		dest_num += ((begin != end) ? c2d(*begin) : 0) + total_carry;
		total_carry = dest_num / base;
		dest_num %= base;
		*dest = d2c(dest_num);

		if(total_carry == 0 && begin == end) return;
	}
}

#endif
