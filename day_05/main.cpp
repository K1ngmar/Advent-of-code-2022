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

template <class StackList>
struct ICrateMover
{
	virtual void move_crate (StackList& stackList, uint32_t moveAmt, uint32_t fromStackId, uint32_t toStackId) = 0;
};

template <class StackList>
struct CrateMover_9000 : public ICrateMover<StackList>
{
	virtual void move_crate (StackList& stackList, uint32_t moveAmt, uint32_t fromStackId, uint32_t toStackId)
	{
		for (size_t i = 0; i < moveAmt; i++)
		{
			auto cargo = stackList[fromStackId].front();
			stackList[fromStackId].pop_front();
			stackList[toStackId].push_front(cargo);
		}
	}
};

template <class StackList>
struct CrateMover_9001 : public ICrateMover<StackList>
{
	virtual void move_crate (StackList& stackList, uint32_t moveAmt, uint32_t fromStackId, uint32_t toStackId)
	{
		for (size_t i = 0; i < moveAmt; i++)
		{
			auto crate = stackList[fromStackId].begin() + moveAmt - i - 1;
			auto cargo = *crate;
			stackList[fromStackId].erase(crate);
			stackList[toStackId].push_front(cargo);
		}
	}
};

using stacklist_t = std::vector<std::deque<unsigned char> >;
auto create_stack_list(const std::string& raw_stacks)
{
	constexpr size_t stack_distance = 4;
	stacklist_t parsed_stacks(total_stacks);

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

auto move_stacks(const std::string& data, ICrateMover<stacklist_t>* crateMover)
{
	auto split = santility::split(data, "\n\n");
	auto stackList = create_stack_list(split[0]);
	auto moves = santility::split(split[1], "\n");

	uint32_t moveAmt;
	uint32_t fromStackId;
	uint32_t toStackId;
	for (auto& move : moves)
	{
	
		std::sscanf(move.c_str(), "move %u from %u to %u", &moveAmt, &fromStackId, &toStackId);

		// subtract one because they use 1 based indexing
		fromStackId -= 1;
		toStackId -= 1;
		crateMover->move_crate(stackList, moveAmt, fromStackId, toStackId);
	}
	return get_top_crates(stackList);
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	CrateMover_9000<stacklist_t> crateMover9000;
	auto part1 = move_stacks(data, &crateMover9000);
	std::cout << "part1: " << part1 << std::endl;

	CrateMover_9001<stacklist_t> crateMover9001;
	auto part2 = move_stacks(data, &crateMover9001);
	std::cout << "part2: " << part2 << std::endl;
}
