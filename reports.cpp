#include <iostream>
#include "menuDipity.h"
int main() {
	//MenuLines mainMenuInfo = 	 //INPUT- Information struct for main menu
	std::string menuName = "Reports";
	std::vector<std::string> menuListing = { "Inventory Listing", "Inventory Wholesale Value",
					"Inventory Retail Value", "Listing by Quantity",
					"Listing by Cost", "Listing by Age",
					"Return to Main Menu"};
	MenuLines mainMenuInfo;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Wholesale Value") / sizeof(char);
	std::cout << makeMenu(mainMenuInfo) << std::endl;

	return 0;
}
