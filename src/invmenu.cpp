#define menu_utils
#include "headers/menuDipity.h"
#include "headers/lookUp.h"
#include "headers/bookfile.h"
#ifndef invmenu
#include "headers/invmenu.h"
#endif
#ifndef addbook
#include "headers/addbook.h"
#endif
#include <iostream>

int main_invmenu() {
	std::string menuName = "Inventory Database";
	std::vector<std::string> menuListing = { "Look Up a Book", "Add a Book",
			"Edit a Book's Record", "Delete a Book", "Return to the Main Menu" };
	MenuLines mainMenuInfo;
	BookType bookList[20];
	int currentBookCount;
	int choice;
	bool keepGoing;

	currentBookCount = 0;
	readFile(bookList, currentBookCount);

	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Return to the Main Menu") / sizeof(char);

	keepGoing = 1;
	do {
		system("clear");
		choice = makeMenu(mainMenuInfo);
		switch (choice) {
		case 0:
			 mainLookUp(bookList, currentBookCount);
			 break;
		case 1:
			 addBook(bookList, currentBookCount);
			 break;
		case 4:
			keepGoing = 0;
			break;
		default:
			break;
		}
	} while (keepGoing);

	return 0;
}
