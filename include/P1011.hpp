#include <iostream>
#include <vector>

int P1011()
{
	/*
	 * let increment = x
	 * [0: 0a + 0x]
	 * 1: 1a + 0x
	 * 2: x -> x --> 1a + 0x(+0)
	 * 3: a + x -> x --> 2a + 0x(+a)
	 * 4: a + 2x -> a + x --> 2a + 1x(+x)
	 * 5: 2a + 3x -> a + 2x --> 3a + 2x(+a+x)
	 * 6: 3a + 5x -> 2a + 3x --> 4a + 4x(+a+2x)
	 * 7: 5a + 8x -> 3a + 5x --> 6a + 7x(+2a+3x)
	 * 8: 8a + 13x -> 5a + 8x --> 9a + 12x(+3a+5x)
	 * ...
	 *
	 * n: 0 -> m --> 0
	 *
	 * -> station (1)'s a + station (n-1)'s k = m
	 * -> station (n-1)'s k = m - a
	 *
	 * [n = 0 -> 0a + 0x]
	 * n = 1 -> 1a + 0x
	 * n = 2 -> 1a + 0x
	 * n = 3 -> 2a + 0x
	 * n = 4 -> 2a + 1x
	 * n = 5 -> 3a + 2x
	 * n = 6 -> 4a + 4x;
	 * n = 7 -> 6a + 7x
	 * n = 8 -> 9a + 12x
	 * ...
	 * like fibonacci?
	 */

	int a;
	int n;
	int m;

	int which;

	std::cin >> a >> n >> m >> which;

	std::vector<int> coefficient_a = {0, 1, 1, 2, 2};
	std::vector<int> coefficient_x = {0, 0, 0, 0, 1};
	coefficient_a.resize(n);
	coefficient_x.resize(n);
	for(int i = 5; i < n; ++i)
	{
		coefficient_a[i] = coefficient_a[i-1] + coefficient_a[i-2] - 1;
		coefficient_x[i] = coefficient_x[i-1] + coefficient_x[i-2] + 1;
	}

	// station (n-1)'s k = m - a
	auto x = (m - a * coefficient_a[n-1]) / coefficient_x[n-1];
	std::cout << a * coefficient_a[which] + x * coefficient_x[which] << std::endl;

	return 0;
}
