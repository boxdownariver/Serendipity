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
 *	PROCESS-
 * 		MenuLines mainMenuInfo -> Menu information to display
 *************************************************************************/
#define menu_utils
#include "headers/bookfile.h"
#include "headers/menuDipity.h"
#include "headers/reports.h"
#include "headers/bookType.h"
#include "headers/invmenu.h"
#include <iostream>
#ifndef REPLISTING_H
#include "headers/repListing.h"
#endif

///Generates reports menu interface
int main_reports(LinkedListType<BookType *>& bookList) {
	std::string menuName = "Reports";
	std::vector<std::string> menuListing = { "Inventory Listing", "Inventory Wholesale Value",
					"Inventory Retail Value", "Listing by Quantity",
					"Listing by Cost", "Listing by Age",
					"Return to Main Menu"};
	MenuLines mainMenuInfo;
	std::string startNotif;

	int choice;
	bool keepGoing;

	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Wholesale Value") / sizeof(char);

	keepGoing = 1;
		do {
		startNotif = "";
		system("clear");
		choice = makeMenu(mainMenuInfo, startNotif);
		switch (choice) {

		// Main
		case 0:
		BookType::setFlag(0);
		mainRepListing(bookList);
		break;

		// Wholesale Price
		case 1:
		mainCalculations (bookList, 'W');
		break;

		// Retail Price
		case 2:
		mainCalculations (bookList, 'R');
		break;

		// Sort By Quantity
		case 3:	
		BookType::setFlag(6);
		mainSorting(bookList);
		break;

		// Sort By Retail Cost
		case 4:
		BookType::setFlag(8);
		mainSorting(bookList);
		break;

		// Sort By Age or Date Added
		case 5:
		BookType::setFlag(5);
		mainSorting(bookList);
		break;

		case 6:
			keepGoing = 0;
			break;
		default:
			break;
		}
	} while (keepGoing);

	return 0;
}
