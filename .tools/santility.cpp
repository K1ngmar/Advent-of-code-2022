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

#include <fstream>
#include <sstream>

std::string santility::read_file(const std::string& fileName)
{
	std::ifstream file(fileName);
	std::stringstream buffer;

	buffer << file.rdbuf();
	return buffer.str();
}

std::vector<std::string> santility::split(const std::string& str, const std::string& seperator)
{
	if (str.length() == 0 || str.find(seperator) == std::string::npos)
		return {};

	std::vector<std::string> subStrings;
	size_t currentPos = 0;
	size_t nextPos = 0;

	// issa magic number, believe me its true
	subStrings.reserve(santility::magic);
	while (currentPos != std::string::npos) {
		nextPos = str.find(seperator, currentPos + seperator.length());
		subStrings.emplace_back(str.substr(currentPos, nextPos - currentPos));
		currentPos = nextPos;
	}
	return subStrings;
}
