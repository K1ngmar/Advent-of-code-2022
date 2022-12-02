#!usr/bin/env bash
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

if [ $# -eq 0 ]; then
    echo "HOHOHO, looks like you forgot to add what day you would like to create buddy <3"
	exit 42
fi

DIR=`printf "day_%.2d" $1`

if [ -d "$DIR" ]; then
	echo "WHOA, you already finished this day, you absolute legend"
else
	echo "Setting up for a successfull day $1!"
	
	echo "Creating directories..."
	mkdir $DIR
	mkdir $DIR/make_settings
	
	echo "Copying files..."
	cp ./.setup_template/Makefile ./$DIR/
	cp ./.setup_template/make_settings/* ./$DIR/make_settings/
	cp ./.setup_template/main.cpp ./$DIR/main.cpp

	echo "Replacing placeholders..."
	sed -i '' "s/__NAME__/$1/g" ./$DIR/make_settings/settings.mk

	echo "Getting puzzle input..."
	COOKIE=`cat .cookiemonster`
	curl "https://adventofcode.com/2022/day/$1/input" --cookie "session=$COOKIE" > ./$DIR/input

	echo ""
	echo "Setup successfull, HAPPY CODING!"
fi
