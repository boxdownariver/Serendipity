/**********************************************************************//**
 * REPORTS MENU INTERFACE IMPLEMENTATION
 * ________________________________________________________________________
 * This program creates a menu interface with options for branching into
 * sub-menus. None of the sub-menus are currently implemented, however the
 * ability to exit this menu is implemented as of current.
 * @author Micah Krosby
 * @file reports.cpp
 * ________________________________________________________________________
 *
 * PROCESS-
 * 		MenuLines mainMenuInfo -> Menu information to display
 *************************************************************************/
#define menu_utils
#include "headers/menuDipity.h"

///Generates reports menu interface
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
	makeMenu(mainMenuInfo, "");

	return 0;
}
