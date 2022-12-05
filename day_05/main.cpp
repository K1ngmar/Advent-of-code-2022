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
#include <deque>

constexpr size_t total_stacks = 9;

auto create_stacks(const std::string& raw_stacks)
{
	constexpr size_t stack_distance = 4;
	std::vector<std::deque<unsigned char> > parsed_stacks(total_stacks);

	auto stacks = santility::split(raw_stacks, "\n");
	// get rid of line with indexes
	stacks.pop_back();

	for (auto& stack : stacks)
	{
		size_t stackId = 0;
		for (size_t i = 1; i < stack.length(); i += stack_distance, stackId++)
		{
			if (stack[i] != ' ') {
				parsed_stacks[stackId].push_back(stack[i]);
			}
		}
	}
	return parsed_stacks;
}

auto get_top_crates(const std::vector<std::deque<unsigned char> > stacks)
{
	std::string topCrates;
	for (size_t i = 0; i < total_stacks; i++) {
		topCrates.push_back(stacks[i].front());
	}
	return topCrates;
}

auto crate_mover_9000(const std::string& data)
{
	auto split = santility::split(data, "\n\n");
	auto stacks = create_stacks(split[0]);
	auto moves = santility::split(split[1], "\n");

	uint32_t moveAmt;
	uint32_t fromStackId;
	uint32_t toStackId;
	for (auto& move : moves) {
		std::sscanf(move.c_str(), "move %u from %u to %u", &moveAmt, &fromStackId, &toStackId);

		// subtract one because they use 1 based indexing
		fromStackId -= 1;
		toStackId -= 1;

		for (size_t i = 0; i < moveAmt; i++) {
			auto cargo = stacks[fromStackId].front();
			stacks[fromStackId].pop_front();
			stacks[toStackId].push_front(cargo);
		}
	}
	return get_top_crates(stacks);
}

auto crate_mover_9001(const std::string& data)
{
	auto split = santility::split(data, "\n\n");
	auto stacks = create_stacks(split[0]);
	auto moves = santility::split(split[1], "\n");

	uint32_t moveAmt;
	uint32_t fromStackId;
	uint32_t toStackId;
	for (auto& move : moves) {
		std::sscanf(move.c_str(), "move %u from %u to %u", &moveAmt, &fromStackId, &toStackId);

		// subtract one because they use 1 based indexing
		fromStackId -= 1;
		toStackId -= 1;

		for (size_t i = 0; i < moveAmt; i++) {
			auto crate = stacks[fromStackId].begin() + moveAmt - i - 1;
			auto cargo = *crate;
			stacks[fromStackId].erase(crate);
			stacks[toStackId].push_front(cargo);
		}
	}
	return get_top_crates(stacks);
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	auto part1 = crate_mover_9000(data);
	std::cout << "part1: " << part1 << std::endl;
	auto part2 = crate_mover_9001(data);
	std::cout << "part2: " << part2 << std::endl;
}
