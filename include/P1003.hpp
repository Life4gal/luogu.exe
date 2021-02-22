#include <iostream>
#include <vector>

struct carpet
{
	struct point
	{
		int x;
		int y;
	};
	int id;
	point begin;
	int width;
	int height;

	[[nodiscard]] bool in_area(const point& p) const
	{
		return
				p.x >= begin.x && p.x <= begin.x + width &&
				p.y >= begin.y && p.y <= begin.y + height;
	}
};

int P1003()
{
	std::vector<carpet> field;
	int n;
	std::cin >> n;
	for(int i = 0; i < n; ++i)
	{
		carpet tmp{};
		std::cin >> tmp.begin.x >> tmp.begin.y >> tmp.width >> tmp.height;
		tmp.id = i + 1;
		field.push_back(tmp);
	}
	carpet::point p{};
	std::cin >> p.x >> p.y;
	for(auto it = field.crbegin(); it != field.crend(); ++it)
	{
		if(it->in_area(p))
		{
			std::cout << it->id;
			return 0;
		}
	}

	std::cout << -1;
	return 0;
}