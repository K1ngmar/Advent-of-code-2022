elveInventories = open("input").read().split("\n\n")

calorie_list = []

for inventory in elveInventories:
	elve_calories = 0
	for calories in inventory.split():
		elve_calories += int(calories)
	calorie_list.append(elve_calories)

calorie_list.sort()

top3 = 0
for inventory in calorie_list[len(calorie_list) - 3:]:
	top3 += inventory

print("exo1:", calorie_list[len(calorie_list) - 1])
print("ex02:", top3)

