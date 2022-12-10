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
#include <array>

auto calculate_result(const std::string& data)
{
	auto instructions = santility::split(data, "\n");
	
	size_t instructionIdx = 0;
	size_t cycle = 1;
	size_t prevInstructionIdx = 1;
	int64_t res = 0;
	int64_t reg = 1;
	std::array<std::string, 6> screen;

	while (instructionIdx < instructions.size())
	{
		if (instructions[instructionIdx] == "noop") {
			instructionIdx++;
		}
		else {
			if (prevInstructionIdx == instructionIdx) {
				int32_t val;
				std::sscanf(instructions[instructionIdx].c_str(), "addx %d", &val);
				reg += val;
				prevInstructionIdx = instructionIdx;
				instructionIdx++;
			}
			else {
				prevInstructionIdx = instructionIdx;
			}
		}
		auto& row = screen[(cycle - 1) / 40];
		row.push_back(abs((int64_t)row.size() + 1 - reg) < 2 ? '#' : '.');
		cycle++;
		if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
			res += reg * cycle;
		}
	};

	for (auto& line : screen) {
		std::cout << line << std::endl;
	}
	
	return res;
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	auto result = calculate_result(data);
	std::cout << "result: " << result << std::endl;
}
