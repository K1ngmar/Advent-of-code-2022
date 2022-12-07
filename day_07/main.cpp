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

std::string currentPath = "/";
std::map<std::string, size_t> folderSizes;
size_t total_size = 0;

void cd(std::string& args)
{
	if (args == "/") {
		currentPath = "/";
	}
	else if (args == "..") {
		currentPath.pop_back();
		size_t pop_amt = currentPath.length() - currentPath.rfind("/") - 1;
		for (; pop_amt != 0; pop_amt--) {
			currentPath.pop_back();
		}
		if (currentPath == "") {
			currentPath = "/";
		}
	}
	else {
		currentPath += args + '/';
	}
}

void ls(std::vector<std::string>& directoryListing)
{
	for (size_t i = 1; i < directoryListing.size(); i += 2) 
	{
		auto size = directoryListing[i];
		auto name = directoryListing[i + 1];

		if (size == "dir") {
			continue ;
		}

		std::string path = currentPath;
		size_t pos = 0;
		size_t dirSize = std::stoull(size);
		total_size += dirSize;
		do {
			folderSizes[path] += dirSize;

			path.pop_back();
			pos = path.rfind("/");
			if (pos != std::string::npos) {
				path.erase(pos + 1, path.length() - pos - 1);
			}
		} while (path.length() > 0);
	}
}

void parse_input(const std::string& data)
{
	auto commands = santility::split(data, "$ ");

	for (auto& command : commands)
	{
		auto parsed_command = santility::split_set(command, " \n");
		if (parsed_command[0] == "cd") {
			cd(parsed_command[1]);
		}
		else if (parsed_command[0] == "ls") {
			ls(parsed_command);
		}
		else {
			throw std::runtime_error("Unknown command: " + parsed_command[0]);
		}
	}
}

size_t calculate_part1()
{
	size_t answer = 0;

	for (auto [path, size] : folderSizes) {
		if (size <= 100000) {
			answer += size;
		}
	}
	return answer;
}

size_t calculate_part2()
{
	constexpr size_t totalDiskSize = 70000000;
	constexpr size_t updateSize = 30000000;
	size_t currentSpaceFree = totalDiskSize - total_size;
	size_t answer = totalDiskSize;

	for (auto [path, size] : folderSizes) {
		if (size + currentSpaceFree >= updateSize && size < answer) {
			answer = size;
		}
	}
	return answer;
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	parse_input(data);
	std::cout << "part 1: " << calculate_part1() << std::endl;
	std::cout << "part 2: " << calculate_part2() << std::endl;
}
