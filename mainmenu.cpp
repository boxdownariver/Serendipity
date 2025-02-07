#include <iostream>
#include <thread>
#include <chrono>
#include "menuDipity.h"
int main() {
	//MenuLines mainMenuInfo = 	 //INPUT- Information struct for main menu
	std::string menuName = "Main Menu";
	std::vector<std::string> menuListing = { "Cashier Module", "Inventory Database Module",
			"Report Module", "Exit" };
	MenuLines mainMenuInfo;
	int menuResult;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Database Module") / sizeof(char);
	menuResult = makeMenu(mainMenuInfo);

	return 0;
}
