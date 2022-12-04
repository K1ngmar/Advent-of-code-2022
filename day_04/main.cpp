/* ************************************************************************** */
/*                                                                            */
/*                                     .-(_)                                  */
/*                                    / _/                                    */
/*                                 .-'   \                                    */
/*                                /       '.                                  */
/*                              ,-~--~-~-~-~-,                                */
/*                             {__.._...__..._}             ,888,             */
/*             ,888,          /\##"  6  6  "##/\          ,88' `88,           */
/*           ,88' '88,__     |(\`    (__)    `/)|     __,88'     `88          */
/*          ,88'   .8(_ \_____\_    '----'    _/_____/ _)8.       8'          */
/*          88    (___)\ \      '-.__    __.-'      / /(___)                  */
/*          88    (___)88 |          '--'          | 88(___)                  */
/*          8'      (__)88,___/                \___,88(__)                    */
/*                    __`88,_/__________________\_,88`__                      */
/*                   /    `88,       |88|       ,88'    \                     */
/*                  /        `88,    |88|    ,88'        \                    */
/*                 /____________`88,_\88/_,88`____________\                   */
/*                /88888888888888888;8888;88888888888888888\                  */
/*               /^^^^^^^^^^^^^^^^^^`/88\\^^^^^^^^^^^^^^^^^^\                 */
/*              /                    |88| \============,     \                */
/*             /_  __  __  __   _ __ |88|_|^  MERRY    | _ ___\               */
/*             |;:.                  |88| | CHRISTMAS! |      |               */
/*             |;;:.                 |88| '============'      |               */
/*             |;;:.                 |88|                     |               */
/*             |::.                  |88|                     |               */
/*             |;;:'                 |88|                     |               */
/*             |:;,                  |88|                     |               */
/*             '---------------------""""---------------------'               */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#include <santility.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <optional>

#define IsBetween(value, left_bound, right_bound) (value >= left_bound && value <= right_bound)

auto calculate_answer(const std::string& data)
{
	auto pairs = santility::split(data, "\n");

	size_t p1 = 0;
	size_t p2 = 0;
	for (auto& pair : pairs)
	{
		auto elvePair = santility::split(pair, ",");
		auto plot_0 = santility::split(elvePair[0], "-");
		auto plot_1 = santility::split(elvePair[1], "-");
		
		auto elve_0_lower = std::stoi(plot_0[0]); 
		auto elve_0_upper = std::stoi(plot_0[1]); 
		auto elve_1_lower = std::stoi(plot_1[0]); 
		auto elve_1_upper = std::stoi(plot_1[1]);

		if (elve_0_lower <= elve_1_lower && elve_0_upper >= elve_1_upper) {
			p1++;
		}
		else if (elve_1_lower <= elve_0_lower && elve_1_upper >= elve_0_upper) {
			p1++;
		}
		else if (IsBetween(elve_0_lower, elve_1_lower, elve_1_upper) ||
				 IsBetween(elve_0_upper, elve_1_lower, elve_1_upper)) {
			p2++;
		}
	}
	
	return std::tuple<size_t, size_t>(p1, p1 + p2);
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	auto [p1, p2] = calculate_answer(data);
	std::cout << "part1: " << p1 << std::endl;
	std::cout << "part2: " << p2 << std::endl;
}
