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

#endif
