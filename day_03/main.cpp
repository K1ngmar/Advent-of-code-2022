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
#include <tuple>

std::tuple<std::string_view, std::string_view> split_compartments(const std::string backpack)
{
	auto len = (backpack.size() / 2);
	return {std::string_view(backpack.c_str(), len), std::string_view(backpack.c_str() + len)};
}

size_t calculate_score(const std::string faultyInventories)
{
	size_t score = 0;
	for (auto c : faultyInventories) {
		if (islower(c) == true) {
			score += c - 'a' + 1;
		}
		else {
			if (isupper(c) == false) {
				throw std::runtime_error("hoe dan: " + std::to_string((int)c));
			}
			score += c - 'A' + 27;
		}
	}
	return score;
}

auto calculate_part1(const std::string& data)
{
	std::string faultyInventories;
	auto backpackList = santility::split(data, "\n");

	faultyInventories.reserve(backpackList.size());
	for (auto& backpack : backpackList)
	{
		auto [compartment_1, compartment_2] = split_compartments(backpack);
		for (auto c : compartment_1)
		{
			if (compartment_2.find(c) != std::string::npos) {
				faultyInventories.push_back(c);
				break ;
			}
		}
	}
	return calculate_score(faultyInventories);
}

auto calculate_part2(const std::string& data)
{
	std::string badges;
	auto backpackList = santility::split(data, "\n");

	badges.reserve(backpackList.size() / 3);
	for (size_t i = 2; i < backpackList.size(); i += 3)
	{
		for (auto c : backpackList[i])
		{
			if (backpackList[i - 1].find(c) != std::string::npos && backpackList[i - 2].find(c) != std::string::npos) {
				badges.push_back(c);
				break ;
			}
		}
	}
	return calculate_score(badges);
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	std::cout << "part1: " << calculate_part1(data) << std::endl;
	std::cout << "part2: " << calculate_part2(data) << std::endl;
}
