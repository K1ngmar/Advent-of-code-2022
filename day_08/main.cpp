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

static inline auto gradeTree(const std::vector<std::string>& grid, const size_t row, const size_t col)
{
	if (row == 0 || row == grid.size() - 1 || col == 0 || col == grid[row].length() - 1) {
		return std::tuple<bool, size_t>(true, 0);
	}

	bool	isVisible = false;
	size_t	multUp = 0,
			multDown = 0,
			multLeft = 0,
			multRight = 0;

	// check up
	for (int rowModifier = row - 1; rowModifier >= 0; rowModifier--) {
		multUp++;
		if (grid[rowModifier][col] >= grid[row][col]) {
			break ;
		}
		if (rowModifier == 0) {
			isVisible = true;
		}
	}
	
	// check down
	for (int rowModifier = row + 1; rowModifier < (int)grid.size(); rowModifier++) {
		multDown++;
		if (grid[rowModifier][col] >= grid[row][col]) {
			break ;
		}
		if (rowModifier == (int)grid.size() - 1) {
			isVisible = true;
		}
	}

	// check left
	for (int colModifier = col - 1; colModifier >= 0; colModifier--) {
		multLeft++;
		if (grid[row][colModifier] >= grid[row][col]) {
			break ;
		}
		if (colModifier == 0) {
			isVisible = true;
		}
	}

	// check right
	for (int colModifier = col + 1; colModifier < (int)grid[row].length(); colModifier++) {
		multRight++;
		if (grid[row][colModifier] >= grid[row][col]) {
			break ;
		}
		if (colModifier == (int)grid[row].length() - 1) {
			isVisible = true;
		}
	}

	return std::tuple<bool, size_t>(isVisible, multUp * multDown * multLeft * multRight);
}

auto calculate_result(const std::string& data)
{
	auto grid = santility::split(data, "\n");

	size_t visibleTrees = 0;
	size_t highestScenicScore = 0;
	for (size_t row = 0; row < grid.size(); row++) {
		for (size_t col = 0; col < grid[row].length(); col++)
		{
			auto [isVisible, scenicScore] = gradeTree(grid, row, col);
			visibleTrees += isVisible;
			if (scenicScore > highestScenicScore) {
				highestScenicScore = scenicScore;
			}
		}
	}	
	return std::tuple<size_t, size_t>(visibleTrees, highestScenicScore);
}

int main(int argc, char** argv)
{
	std::string fileName = "input";
	if (argc > 1) {
		fileName = argv[1];
	}
	const std::string data = santility::read_file(fileName);

	auto [part1, part2] = calculate_result(data);
	std::cout << "part1: " << part1 << std::endl;
	std::cout << "part2: " << part2 << std::endl;
}
