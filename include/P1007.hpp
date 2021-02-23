#include <iostream>

int P1007() {
	int l;
	int n;
	std::cin >> l >> n;

	int max_time = 0;
	int min_time = 0;
	for (int i = 0; i < n; ++i) {
		int curr;
		std::cin >> curr;
		// if everyone's speed is constant,
		// then it doesn't matter whether someone collides with others or not.
		// or in other words, even if they collide and change direction,
		// we can regard the reversed BA as passing through the other side's AB
		if (
				auto left = curr,
				right = l + 1 - curr,
				m = left > right ? left : right;
				m > max_time) {
			max_time = m;
		}
		if (
				auto left = curr,
				right = l + 1 - curr,
				m = right > left ? left : right;
				m > min_time) {
			min_time = m;
		}
	}

	std::cout << min_time << ' ' << max_time << std::endl;

	return 0;
}