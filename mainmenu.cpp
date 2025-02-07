#include "menuDipity.h"
#include "reports.h"
#include "invmenu.h"

int main() {
	//MenuLines mainMenuInfo = 	 //INPUT- Information struct for main menu
	std::string menuName = "Main Menu";
	std::vector<std::string> menuListing = { "Cashier Module",
			"Inventory Database Module", "Report Module", "Exit" };
	MenuLines mainMenuInfo;
	int menuResult;
	bool continueMenu;
	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Database Module")
			/ sizeof(char);

	do {
		continueMenu = 1;
		menuResult = makeMenu(mainMenuInfo);

		switch (menuResult) {
		case 1:
			main_invmenu();
			break;
		case 2:
			main_reports();
			break;
		default:
			continueMenu = 0;
			break;
		}
	} while (continueMenu);

	return 0;
}
