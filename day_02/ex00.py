# **************************************************************************** #
#                                                                              #
#                                      .-(_)                                   #
#                                     / _/                                     #
#                                  .-'   \                                     #
#                                 /       '.                                   #
#                               ,-~--~-~-~-~-,                                 #
#                              {__.._...__..._}             ,888,              #
#              ,888,          /\##"  6  6  "##/\          ,88' `88,            #
#            ,88' '88,__     |(\`    (__)    `/)|     __,88'     `88           #
#           ,88'   .8(_ \_____\_    '----'    _/_____/ _)8.       8'           #
#           88    (___)\ \      '-.__    __.-'      / /(___)                   #
#           88    (___)88 |          '--'          | 88(___)                   #
#           8'      (__)88,___/                \___,88(__)                     #
#                     __`88,_/__________________\_,88`__                       #
#                    /    `88,       |88|       ,88'    \                      #
#                   /        `88,    |88|    ,88'        \                     #
#                  /____________`88,_\88/_,88`____________\                    #
#                 /88888888888888888;8888;88888888888888888\                   #
#                /^^^^^^^^^^^^^^^^^^`/88\\^^^^^^^^^^^^^^^^^^\                  #
#               /                    |88| \============,     \                 #
#              /_  __  __  __   _ __ |88|_|^  MERRY    | _ ___\                #
#              |;:.                  |88| | CHRISTMAS! |      |                #
#              |;;:.                 |88| '============'      |                #
#              |;;:.                 |88|                     |                #
#              |::.                  |88|                     |                #
#              |;;:'                 |88|                     |                #
#              |:;,                  |88|                     |                #
#              '---------------------""""---------------------'                #
#                                                                              #
#                    Kingmar  |  https://github.com/K1ngmar                    #
#                                                                              #
# **************************************************************************** #

score_lookup = {
	'X': 1, 
	'Y': 2,
	'Z': 3
	}
# x, a = rock
# y, b = paper
# z, c = scissors
win_lookup = {
	'X': 'C',
	'Y': 'A',
	'Z': 'B'
	}
draw_lookup = {
	'X': 'A',
	'Y': 'B',
	'Z':'C'
	}

score = 0
for match in open("input").read().splitlines():
	opponent_move, my_move = match.split()
	score += score_lookup.get(my_move)
	if win_lookup.get(my_move) == opponent_move:
		score += 6
	elif draw_lookup.get(my_move) == opponent_move:
		score += 3

print("ex00", score)