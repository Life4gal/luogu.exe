#include <iostream>
#include <cmath>

int P1014()
{

	int n;
	std::cin >> n;

	/*
	 * 1/1 1/2 1/3 1/4 1/5 1/6
	 * 2/1 2/2 2/3 2/4 2/5
	 * 3/1 3/2 3/3 3/4
	 * 4/1 4/2 4/3
	 * 5/1 5/2
	 * 6/1
	 *
	 * 1/1
	 * 1/2 -> 2/1
	 * 3/1 -> 2/2 -> 1/3
	 * 1/4 -> 2/3 -> 3/2 -> 4/1
	 * 5/1 -> 4/2 -> 3/3 -> 2/4 -> 1/5
	 * 1/6 -> 2/5 -> 3/4 -> 4/3 -> 5/2 -> 6/1
	 *
	 * arithmetic sequence(line 1 has 1 element, line 2 has 2 elements...):
	 *  Sn = n * (An + A1) / 2
	 *  A1 = 1 and An = n --> S = n * (n + 1) / 2
	 *
	 *  it means a given num K in line line,
	 *  line * (line-1) / 2 < K <= line * (line + 1) / 2
	 *
	 *  let `line ~= line
	 *  `line^2 = 2K -> `line = (2K)^(1/2)
	 *  if `line <= `line * (`line + 1) / 2 - K, means K in line `line - 1 (or floor(line))
	 *  else K in line `line (or ceil(line))
	 */

	// need use ceil, because cast double to int normally use floor
	int line = std::ceil(std::sqrt(2 * n));
	if(line <= line * (line + 1) / 2 - n)
	{
		--line;
	}

	// then we calc the position (x, y)
	int x;
	int y;
	if(line & 1)
	{
		// odd line
		y = line * (line + 1) / 2 - n + 1;
	}
	else
	{
		// even line
		y = line - (line * (line + 1) / 2 - n);
	}
	x = line - y + 1;

	std::cout << y << '/' << x << std::endl;

	return 0;
}
