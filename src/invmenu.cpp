#define menu_utils
#include "headers/menuDipity.h"
#include "headers/lookUp.h"

int main_invmenu() {
	std::string menuName = "Inventory Database";
	std::vector<std::string> menuListing = { "Look Up a Book", "Add a Book",
			"Edit a Book's Record", "Delete a Book", "Return to the Main Menu" };
	MenuLines mainMenuInfo;
	int choice;
	bool keepGoing;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Return to the Main Menu") / sizeof(char);

	keepGoing = 1;
	do {
		choice = makeMenu(mainMenuInfo);
		switch (choice) {
		case 0:
			 mainLookUp();
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
