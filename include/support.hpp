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

#endif
