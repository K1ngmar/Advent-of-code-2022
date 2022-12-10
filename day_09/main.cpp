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

struct Position {
	int32_t x;
	int32_t y;

	bool operator < (const Position& pos) const {
		return (this->x < pos.x || this->y < pos.y);
	}

	bool operator == (const Position& pos) const {
		return (this->x == pos.x && this->y == pos.y);
	}
	
	bool hasToMove(const Position& pos) {
		return (abs(this->x - pos.x) > 1 || abs(this->y - pos.y) > 1);
	}

};

size_t terribleHotfixBecauseMyCodeSucks(const std::set<Position>& visitedPositions) {
	size_t kutzooi = 0;
	for (auto a = visitedPositions.begin(); a != --visitedPositions.end(); a++) {
		auto jemoeder = a;
		for (auto b = ++jemoeder; b != visitedPositions.end(); b++) {
			if (*a == *b) {
				kutzooi++;
				break ;
			}
		}
	}
	return kutzooi;
}

auto calculate_result(const std::string& data)
{
	auto moves = santility::split(data, "\n");
	
	char		dir;
	size_t		stepSize;
	std::set<Position> visitedPositionsTailFront;
	std::set<Position> visitedPositionsTailBack;
	Position head = {0, 0};
	constexpr size_t tailLength = 9;
	std::array<Position, tailLength> tail;

	tail[0] = {0, 0};
	for (auto& move : moves) {
		std::sscanf(move.c_str(), "%c %zu", &dir, &stepSize);

		// std::cout << "moving: " << dir << " with " << stepSize << std::endl;
		for (size_t i = 0; i < stepSize; i++)
		{
			auto prev_tail = tail[0];
			switch (dir)
			{
				case 'U': {
					head.y++;
					if (tail[0].hasToMove(head)) {
						tail[0] = {head.x, head.y - 1};
					}
					break ;
				}
				case 'D': {
					head.y--;
					if (tail[0].hasToMove(head)) {
						tail[0] = {head.x, head.y + 1};
					}
					break ;
				}
				case 'L': {
					head.x--;
					if (tail[0].hasToMove(head)) {
						tail[0] = {head.x + 1, head.y};
					}
					break ;
				}
				case 'R': {
					head.x++;
					if (tail[0].hasToMove(head)) {
						tail[0] = {head.x - 1, head.y};
					}
					break ;
				}
				default:
					throw std::runtime_error("unknown direction: " + std::to_string((int)dir));
			};

			// std::cout << tail.x << ", " << tail.y << std::endl;
			visitedPositionsTailFront.insert(tail[0]);
			visitedPositionsTailBack.insert(tail[tailLength - 1]);

			if (!(tail[0] == prev_tail)) {
				for (size_t i = 1; i < tailLength; i++) {
					tail[tailLength - i] = tail[tailLength - i - 1];
				}
			}
		}
	}

	return std::tuple<size_t, size_t>(
		visitedPositionsTailFront.size() - terribleHotfixBecauseMyCodeSucks(visitedPositionsTailFront),
		visitedPositionsTailBack.size() - terribleHotfixBecauseMyCodeSucks(visitedPositionsTailBack)
	);
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
