#include <iostream>
#include <vector>
#include <string>
bool check;
const int sum_location = 4;
bool present;
bool use_com;
int r;
std::string tr;
std::string variations[3]{"stone","scissors","paper"};
std::string matrix[3][3]{{"draw","win","lose"},{"lose","draw","win"},{"win","lose","draw"}};
std::string item;
struct location {
	std::string name;
	std::string description;
	int num;
	std::vector<int> door;
	std::vector<std::string> items;
};
struct hero {
	int current_location;
	int hp;
	std::vector<std::string> inventory;
};
std::string path;
location locations[sum_location]{
	{ "hall","center of home",0,{1},{} },
	{ "hallway","connect room",1,{0},{"key to kitchen"}},
	{ "kitchen", "eat room", 2, {1,3},{"hp poizon"}},
	{ "bathroom", "wash room", 3,{2},{} } };
hero man{ 0,10,{} };
std::string commands[5] = { "List","Trunk","Pick","Drop","Use" };
int main()
{
	std::cout << "exiting locations: \n";
	for (int i = 0; i <= sum_location - 1; i++) {
		std::cout << locations[i].name << "\n";
	}
	std::cout << "\nexiting commands: \n";
	for (std::string command : commands) {
		std::cout << command << "\n";
	}
	while (true) {
		if (man.hp <= 0) {
			break;
		}
		use_com = false;
		for (int i = 0; i <= sum_location - 1; i++) {
			if (man.current_location == locations[i].num) {
				std::cout << "\n" << "description of the current location : " << locations[i].description << "\n";
			}
		}

		std::cout << "send next location name / command name \n";
		std::cin >> path;
		for (std::string command : commands) {
			if (command == path) {
				use_com = true;
				break;
			}
		}
		if (use_com) {
			if (path == "List") {
				if ((locations[man.current_location].items).size() > 0) {
					std::cout << "items on this location: \n";
					for (std::string el : locations[man.current_location].items) {
						std::cout << el << "\n";
					}
				}
				else {
					std::cout << "No such items in this location \n";
				}
			}
			if (path == "Trunk") {
				if (man.inventory.size() > 0) {
					std::cout << "items on the inventory :\n";
					for (std::string el : man.inventory) {
						std::cout << el << "\n";
					}
				}
				else {
					std::cout << "No such items on the inventory \n";
				}
			}
			if (path == "Pick") {
				std::cout << "send item name \n";
				std::cin.ignore(); 
				std::getline(std::cin, item);

				auto& loc_items = locations[man.current_location].items;
				auto it = std::find(loc_items.begin(), loc_items.end(), item);

				if (it != loc_items.end()) {
					std::cout << item << " added to inventory \n";
					man.inventory.push_back(item);
					loc_items.erase(it);
				}
				else {
					std::cout << item << " not found here \n";
				}
			}
			if (path == "Drop") {
				std::cout << "send item name \n";
				std::cin.ignore();
				std::getline(std::cin, item);
				auto& inventory_items = man.inventory;
				auto it = std::find(inventory_items.begin(), inventory_items.end(), item);
				if (it != inventory_items.end()) {
					std::cout << item << " Dropped \n";
					man.inventory.erase(it);
					locations[man.current_location].items.push_back(item);
				}
				else {
					std::cout << item << " not found here \n";
				}
			}
			if (path == "Use") {
				std::cout << "send item name \n";
				std::cin.ignore();
				std::getline(std::cin, item);
				auto& inventory_items = man.inventory;
				auto it = std::find(inventory_items.begin(), inventory_items.end(), item);
				if (it != inventory_items.end()) {
					if (item == "key to kitchen") {
						if (man.current_location == 1) {
							std::cout << "door to kitchen opened";
							locations[1].door.push_back(2);
							man.inventory.erase(it);
						}
						else {
							std::cout << "You are in the wrong location. \n";
						}
					}
					else if (item == "hp poizon") {
						std::cout << "poizon used, hero hp +5";
						man.hp += 5;
						man.inventory.erase(it);
					}
				}
				else {
					std::cout << item << " not found here \n";
				}
			}
		}
		else {
			check = false;
			present = false;
			for (int i = 0; i <= sum_location - 1; i++) {
				if (path == locations[i].name) {
					check = true;
					if (locations[i].num == man.current_location) {
						std::cout << "You are already in this location \n \n";
						break;
					}
					for (int element : locations[man.current_location].door) {
						if (element == locations[i].num) {
							present = true;
							break;
						}
					}
					if (present) {
						man.current_location = locations[i].num;
						srand(time(0));
						r = 0 + rand() % 3;
						if (r == 0) {
							std::cout << "enemy has been atack \n";
							while (man.hp > 0) {
								srand(time(0));
								r = 0 + rand() % 2;
								std::cout << "change stone/scissors/paper \n";
								std::cin >> tr;
								if (tr == variations[0]) {
									std::string answer = matrix[0][r];
									std::cout << answer << '\n';
									if (answer == "win") {
										std::cout << "congratulations! \n";
										break;
									}
									else if (answer == "lose") {
										std::cout << "Have you been injured! \n";
										man.hp -= 5;
									}
									else {

									}
								}
								else if (tr == variations[1]) {
									std::string answer = matrix[1][r];
									std::cout << answer << '\n';
									if (answer == "win") {
										std::cout << "congratulations! \n";
										break;
									}
									else if (answer == "lose") {
										std::cout << "Have you been injured! \n";
										man.hp -= 5;
									}
									else {

									}
								}
								else if (tr == variations[2]) {
									std::string answer = matrix[2][r];
									std::cout << answer << "\n";
									if (answer == "win") {
										std::cout << "congratulations! \n";
										break;
									}
									else if (answer == "lose") {
										std::cout << "Have you been injured! \n";
										man.hp -= 5;
									}
									else {

									}
								}
								else {
									std::cout << "wrong \n";
								}
								
							}
							if (man.hp <= 0) {
								std::cout << "you're dead \n";
								break;
							}
						}
					}
					else {
						std::cout << "it is impossible to get in from the current room \n \n";
					}
				}
				else if (i == sum_location - 1 and not check) {
					std::cout << "There is no such room \n \n";
				}
			}
		}

	}
}


