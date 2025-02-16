#define menu_utils
#include "headers/menuDipity.h"
#include "headers/lookUp.h"

int main_invmenu() {
	std::string menuName = "Inventory Database";
	std::vector<std::string> menuListing = { "Look Up a Book", "Add a Book",
			"Edit a Book's Record", "Delete a Book", "Return to the Main Menu" };
	MenuLines mainMenuInfo;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Return to the Main Menu") / sizeof(char);
	makeMenu(mainMenuInfo);

	return 0;
}
