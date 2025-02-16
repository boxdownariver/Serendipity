#define menu_utils
#include "headers/menuDipity.h"
#include "headers/reports.h"
#include "headers/invmenu.h"
#include "headers/cashier.h"
#include "headers/lookUp.h"

int main() {
	MenuLines mainMenuInfo;
	std::vector<std::string> menuListing = { "Cashier Module",
			"Inventory Database Module", "Report Module", "Exit" };
	std::string menuName = "Main Menu";
	int menuResult;
	bool continueMenu;

	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Inventory Database Module")
			/ sizeof(char);

	system("clear");
	do {
		continueMenu = 1;
		menuResult = makeMenu(mainMenuInfo);

		switch (menuResult) {
		case 0:
			mainCashier();
			system("clear");
			break;
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
