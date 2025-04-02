/**********************************************************************//**
 * MAIN MENU IMPLEMENTATION
 * ________________________________________________________________________
 * This program generates a menu interface for branching into all
 * subprograms in the project.
 * @author Micah Krosby
 * @file mainmenu.cpp
 * ________________________________________________________________________
 *
 *	PROCESS-
 * 		BookType[20] books, int bookCount -> Book list with size for use
 * 			in the inventory interface.
 * 		int menuResult -> User menu decision for branching into
 * 			subprograms.
 *************************************************************************/
#define menu_utils
#include "headers/menuDipity.h"
#include "headers/reports.h"
#include "headers/invmenu.h"
#include "headers/cashier.h"
#include "headers/lookUp.h"

/**
 * main() ->
 * Generates main menu interface, allowing for branching into all
 * subprograms in the program.
 */
int main() {
	MenuLines mainMenuInfo;
	std::vector<std::string> menuListing = { "Cashier Module",
			"Inventory Database Module", "Report Module", "Exit" };
	std::string menuName = "Main Menu";
	BookType *books[20];
	int menuResult;
	bool continueMenu;

	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Database Module")
			/ sizeof(char);

	system("clear");
	do {
		continueMenu = 1;
		menuResult = makeMenu(mainMenuInfo, "");

		switch (menuResult) {
		case 0:
			mainCashier(books);
			system("clear");
			break;
		case 1:
			main_invmenu(books);
			break;
		case 2:
			main_reports(books);
			break;
		default:
			continueMenu = 0;
			break;
		}
	} while (continueMenu);

	if (BookType::getBookCount()) {
		for (int i = 0; i < BookType::getBookCount(); i++) {
			delete books[i];
		}
	}
	return 0;
}
