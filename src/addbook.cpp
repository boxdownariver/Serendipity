#include "headers/addbook.h"
#include "headers/menuDipity.h"
#ifndef signal
#include <signal.h>
#endif

void ahandleSignal(const int signal);

volatile sig_atomic_t astateProvider = 0;

/*int main() {
	BookType bookList[20];
	int currentBookCount = 0;
	addBook(bookList, currentBookCount);
	return 0;
}*/

void addBook(BookType bookList[20], int &currentBookCount) {
	WINDOW * mainWindow;
	WINDOW * bookDisplayWindow;
	WINDOW * notification;
	ITEM ** items;
	MENU * mainMenu;
	MenuLines mainMenuInfo;
	BookType bookBuffer;
	struct sigaction sa;
	int input;
	int choice;
	char inputChar;
	bool continueMenu;

	std::vector<std::string> menuListing = {"Set Title", "Set ISBN", "Set Author", 
		"Set Publisher", "Set Date Added", "Set Quantity on Hand", "Set Wholesale Value", 
		"Set Retail Value", "Write to Book List", "Exit"};

	mainMenuInfo.menuName = "Add a Book";
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = 20;

	sa.sa_flags = 0;
	sa.sa_handler = ahandleSignal;
	sigaction(SIGWINCH, &sa, NULL);

	startWindow(mainWindow);
	createMenuMiddleSplit(mainMenu, mainWindow, mainMenuInfo, items);

	inputChar = '1';
	input = 0;
	continueMenu = 1;
	choice = -1;

	//Print menu dialog
	box(mainWindow, 0, 0);
	mvwprintw(mainWindow, 1,
			(getmaxx(mainWindow) - mainMenuInfo.storeName.length()) / 2,
			mainMenuInfo.storeName.c_str());
	mvwprintw(mainWindow, 2,
			(getmaxx(mainWindow) - mainMenuInfo.menuName.length()) / 2,
			mainMenuInfo.menuName.c_str());
	post_menu(mainMenu);
	mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
			(getmaxx(mainWindow) - 38) / 2,
			"Select [0-%d] or navigate to module...", menuListing.size() - 1);
	wrefresh(mainWindow);

	notification = newwin(1, 3 * COLS / 5, 9 * LINES / 10, COLS / 5);

	//Main program loop
	while (currentBookCount < 20 && continueMenu) {
		if (astateProvider) {
			refreshWindowMiddleSplit(mainMenu, mainWindow, notification, mainMenuInfo);
			astateProvider = 0;
		}
		input = wgetch(mainWindow);
		inputChar = ((input == '0') ? '9' : input - 1);

		switch (input) {
		case 10:
			choice = item_index(current_item(mainMenu));
			if (choice < menuListing.size() && choice != -1) {
				switch (choice) {
					case 0:
						//Get book title
						break;
					case 1:
						//Get isbn
						break;
					case 2:
						//Get author
						break;
					case 3:
						//Get publisher
						break;
					case 4:
						//Get date added
						break;
					case 5:
						//Get quantity on hand
						break;
					case 6:
						//Get wholesale value
						break;
					case 7:
						//Get retail value
						break;
					case 8:
						bookList[currentBookCount] = bookBuffer;
						currentBookCount++;
						break;
					default:
						continueMenu = 0;
						break;
				}
			}
			break;
		case KEY_UP:
			wclear(notification);
			wrefresh(notification);
			menu_driver(mainMenu, REQ_PREV_ITEM);
			break;
		case KEY_DOWN:
			wclear(notification);
			wrefresh(notification);
			menu_driver(mainMenu, REQ_NEXT_ITEM);
			break;
		default:
			if (input >= '0' && input <= menuListing.size() + 47) {
				wclear(notification);
				set_current_item(mainMenu, items[atoi(&inputChar)]);
				wrefresh(notification);
			} else {
				wclear(notification);
				wprintw(notification, "Invalid Input");
				wrefresh(notification);
			}
			break;
		}
	}
	wclear(notification);
	delwin(notification);
	//delwin(bookDisplayWindow);
	deleteMenu(mainMenu, items, menuListing.size());
	endWindow(mainWindow);
	return;
}

void ahandleSignal(const int signal) {
	astateProvider = signal;
	return;
}
