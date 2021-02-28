#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

struct gas_station {
	float distance_from_start;
	float price;
	float distance_from_next;
};

struct traveler {
	int current_station;
	float remaining_fuel;
	float total_spend;
};

int P1016() {
	float total_distance;
	float fuel_capacity;
	float distance_per_liter;
	float start_fuel_price;
	int total_gas_stations;

	std::cin >> total_distance >> fuel_capacity >> distance_per_liter >> start_fuel_price >> total_gas_stations;

	// we will store the 'start point'
	total_gas_stations += 1;

	const auto max_drive_distance = fuel_capacity * distance_per_liter;

	// init with the 'start point'
	std::vector<gas_station> stations{{0, start_fuel_price, 0}};

	stations.reserve(total_gas_stations);
	// skip the 'start point'
	for (auto i = 1; i < total_gas_stations; ++i) {
		float d;
		float p;
		std::cin >> d >> p;
		auto dfn = d - stations[i-1].distance_from_start;
		if (dfn > max_drive_distance) {
			std::cout << "No Solution" << std::endl;
			return 0;
		}
		// we need know next station's distance to set this station's 'distance_from_next'
		stations[i - 1].distance_from_next = dfn;
		stations.push_back({d, p, 0});
	}

	// set the last gas station's distance from 'end point'
	auto& [dfs, _, dfn] = stations.back();
	dfn = total_distance - dfs;

	auto total_spend = std::numeric_limits<float>::infinity();
	auto found_it = false;

	// we need recursive call this function, so it can not be a lambda but a wrapped function
	std::function<void(traveler)> dfs_traver;

	dfs_traver = [&dfs_traver, fuel_capacity, distance_per_liter, total_gas_stations, max_drive_distance, &stations, &total_spend, &found_it](traveler traveler) -> void {
		if (traveler.current_station == total_gas_stations) {
			if(traveler.total_spend < total_spend)
			{
				total_spend = traveler.total_spend;
			}
			found_it = true;
			return;
		}

		// this should be unnecessary
//		if(stations[traveler.current_station].distance_from_next > max_drive_distance)
//		{
//			return;
//		}

		decltype(distance_per_liter) sum_distance = 0;
		for (auto i = traveler.current_station; i < total_gas_stations; ++i) {
			sum_distance += stations[i].distance_from_next;
			if (sum_distance > max_drive_distance) break;

			/*
			 * refuel to full
			 *
			 * next traver
			 * remaining fuel(total - used)
			 * total spend(last_spend + refuel_to_full's_price)
			 */
			dfs_traver(
					{i + 1,
					 fuel_capacity - sum_distance / distance_per_liter,
					 traveler.total_spend + stations[traveler.current_station].price * (fuel_capacity - traveler.remaining_fuel)});

			/*
			 * use all fuel
			 *
			 * next traver
			 * 0
			 * if remaining_fuel is enough(stations[i].distance_from_next / distance_per_liter < remaining_fuel), this spend is 0, otherwise, increase the spend
			 */
			dfs_traver(
					{i + 1,
					 0,
					 traveler.total_spend + max(static_cast<decltype(traveler.total_spend)>(0), stations[traveler.current_station].price * (sum_distance / distance_per_liter) - stations[traveler.current_station].price * traveler.remaining_fuel)});
		}
	};


	dfs_traver({0, 0, 0});

	if (found_it) {
		std::cout << std::fixed << std::setprecision(2) << total_spend << std::endl;
	} else {
		std::cout << "No Solution" << std::endl;
	}

	return 0;
}
