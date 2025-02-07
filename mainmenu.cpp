#include <iostream>
#include "menuDipity.h"
int main() {
	//MenuLines mainMenuInfo = 	 //INPUT- Information struct for main menu
	std::string menuName = "Main Menu";
	std::vector<std::string> menuListing = { "Cashier Module", "Inventory Database Module",
			"Report Module", "Exit" };
	MenuLines mainMenuInfo;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Database Module") / sizeof(char);
	std::cout << makeMenu(mainMenuInfo) << std::endl;

	return 0;
}
