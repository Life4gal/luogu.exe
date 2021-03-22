#include <cmath>
#include <iostream>
#include <map>

int P1023() {
	/*
	 * known conditions: max_cost, min_cost, quantity_when_max_cost
	 *
	 * let x is subsidy
	 * for i, Ni = curr_cost, Qi = curr_quantity
	 * the expression
	 *      (max_cost - min_cost + x) * quantity_when_max_cost >= (Ni - min_cost + x) * Qi
	 * should always be true
	 *
	 * -->
	 *      when max_cost > Ni >= min_cost
	 *      x <= ((Ni - min_cost) * Qi - (max_cost - min_cost) * quantity_when_max_cost) / (quantity_when_max_cost - Qi)
	 *
	 *      when Ni > max_cost
	 *      X >= ((Qi - min_cost) * Qi - (max_cost - min_cost) * quantity_when_max_cost) / (quantity_when_max_cost - Qi)
	 *
	 *      and (max_cost - min_cost) * quantity_when_max_cost is constant -> basic_profit = (max_cost - min_cost) * quantity_when_max_cost
	 */

	std::ostream::sync_with_stdio(false);

	int max_cost;
	std::cin >> max_cost;

	int min_cost;
	int min_quantity;
	std::cin >> min_cost >> min_quantity;

	std::map<int, int> map;
	map[min_cost] = min_quantity;

	int last_cost = min_cost;
	while (true) {
		int curr_cost;
		int curr_quantity;
		std::cin >> curr_cost >> curr_quantity;
		if (curr_cost == -1) break;

		map[curr_cost] = curr_quantity;

		// Calculate the value not given in the interval
		for (auto i = last_cost + 1, quantity = curr_quantity - map[last_cost], cost = curr_cost - last_cost; i < curr_cost; ++i) {
			map[i] = map[i - 1] + quantity / cost;
		}

		last_cost = curr_cost;
	}

	int coefficient;
	std::cin >> coefficient;

	while (map[last_cost] > coefficient) {
		map[last_cost + 1] = map[last_cost] - coefficient;
		++last_cost;
	}

	// extract max_cost's quantity and did not insert it, it equal to max_quantity = map[max_cost], map.erase(max_cost) and no resource leak
	auto max_quantity = map.extract(max_cost).mapped();

	double taxes = 1e9;
	double subsidy = -1e9;
	for (auto curr_cost = min_cost, basic_profit = max_quantity * (max_cost - min_cost); curr_cost <= last_cost; ++curr_cost) {
		auto x = static_cast<double>((curr_cost - min_cost) * map[curr_cost] - basic_profit) / (max_quantity - map[curr_cost]);

		if (curr_cost < max_cost) {
			taxes = std::min(taxes, x);
		} else {
			subsidy = std::max(subsidy, x);
		}
	}

	if (subsidy > 0) {
		std::cout << std::ceil(subsidy) << std::endl;
	} else if (taxes < 0) {
		std::cout << std::floor(taxes) << std::endl;
	} else {
		std::cout << "NO SOLUTION" << std::endl;
	}

	return 0;
}
