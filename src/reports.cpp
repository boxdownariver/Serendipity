#include "headers/menuDipity.h"
int main_reports() {
	std::string menuName = "Reports";
	std::vector<std::string> menuListing = { "Inventory Listing", "Inventory Wholesale Value",
					"Inventory Retail Value", "Listing by Quantity",
					"Listing by Cost", "Listing by Age",
					"Return to Main Menu"};
	MenuLines mainMenuInfo;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Wholesale Value") / sizeof(char);
	makeMenu(mainMenuInfo);

	return 0;
}
