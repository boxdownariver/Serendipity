//Micah Krosby                      CS1B                        Serendipity
/**************************************************************************
 * INVMENU
 *_________________________________________________________________________
 * This program generates an inventory menu interface for the Serendipity 
 * project
 *_________________________________________________________________________
 *	INPUTS-
 *	    Key input (char) -> Keyboard-based instruction for the program
 *	    Signals (int) -> Signals passed by the system
 *	    mainMenuInfo (char *, char **, char *) -> Menu name, 
 *	    					menu options, store name
 *	OUTPUTS-
 *	    mainWindow -> Window containing mainMenu interface
 *************************************************************************/

#include <curses.h>
#include <signal.h>
#include <menu.h>
#include <chrono>
#include <thread>
#include <cstdlib>

struct MenuLines {
	char menuName[19];
	char menuLines[5][24];
	char storeName[24] = "Serendipity Booksellers";
};

void createMenu(MENU *&mainMenu, WINDOW *mainWindow,
		const MenuLines &mainMenuInfo, ITEM **&items);
void deleteMenu(MENU *&mainMenu, ITEM **&items, size_t menuLineSize);
void startWindow(WINDOW *&mainWindow);
void endWindow(WINDOW *&mainWindow);
void handleSignal(const int signal);
void refreshWindow(MENU *&mainMenu, WINDOW *&mainWindow,
		MenuLines mainMenuInfo);

volatile sig_atomic_t stateProvider = 0;

int main() {
	struct sigaction sa;	 	 //OUTPUT- Signal action handler
	ITEM **items;			 //OUTPUT- Menu items
	MENU *mainMenu;			 //OUTPUT- Complete menu
	WINDOW *mainWindow;		 //OUTPUT- Window to hold menu
	MenuLines mainMenuInfo = 	 //INPUT- Information struct for main menu
			{ "Inventory Database", { "Look Up a Book", "Add a Book",
					"Edit a Book's Record", "Delete a Book", "Return to the Main Menu" } };
	bool dontExit;			 //INPUT- Prevent exiting until need is met

	//Handle system signals
	sa.sa_flags = 0;
	sa.sa_handler = handleSignal;
	sigaction(SIGWINCH, &sa, NULL);

	//Init window, items, menu
	startWindow(mainWindow);
	createMenu(mainMenu, mainWindow, mainMenuInfo, items);

	//Print menu dialog
	box(mainWindow, 0, 0);
	mvwprintw(mainWindow, 1,
			(getmaxx(mainWindow)
				- sizeof(mainMenuInfo.storeName) / sizeof(char)) / 2,
			mainMenuInfo.storeName);
	mvwprintw(mainWindow, 2,
			(getmaxx(mainWindow)
				- sizeof(mainMenuInfo.menuName) / sizeof(char)) / 2,
			mainMenuInfo.menuName);
	post_menu(mainMenu);
	mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
			(getmaxx(mainWindow) - 38) / 2,
			"Select [1-5] or navigate to choice...");
	wrefresh(mainWindow);

	//Main program loop
	dontExit = 1;
	do {
		if (stateProvider) {
			refreshWindow(mainMenu, mainWindow, mainMenuInfo);
			stateProvider = 0;
		}
		//Navigate the menu with 1, 2, 3 or 4
		switch (wgetch(mainWindow)) {
		case '1':
			menu_driver(mainMenu, REQ_FIRST_ITEM);
			break;
		case '2':
			menu_driver(mainMenu, REQ_FIRST_ITEM);
			menu_driver(mainMenu, REQ_NEXT_ITEM);
			break;
		case '3':
			menu_driver(mainMenu, REQ_FIRST_ITEM);
			menu_driver(mainMenu, REQ_NEXT_ITEM);
			menu_driver(mainMenu, REQ_NEXT_ITEM);
			break;
		case '4':
			menu_driver(mainMenu, REQ_LAST_ITEM);
			menu_driver(mainMenu, REQ_PREV_ITEM);
			break;
		case '5':
			menu_driver(mainMenu, REQ_LAST_ITEM);
			break;
		case 10:
			//Activate current user selection
			switch (item_index(current_item(mainMenu))) {
			case 4:
				dontExit = 0;
				break;
			default:
				break;
			}
			break;
		case KEY_UP:
			menu_driver(mainMenu, REQ_PREV_ITEM);
			break;
		case KEY_DOWN:
			menu_driver(mainMenu, REQ_NEXT_ITEM);
			break;
		default:
			break;
		}
	} while (dontExit);
	//End program
	deleteMenu(mainMenu, items,
			sizeof(mainMenuInfo.menuLines)
				/ sizeof(mainMenuInfo.menuLines[0]) + 1);
	clear();
	mvwprintw(mainWindow, getmaxy(mainWindow) / 2,
			getmaxx(mainWindow) / 2 - 5, "Goodbye!");
	wrefresh(mainWindow);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	endWindow(mainWindow);

	return 0;
}

//Create menu & menu items
void createMenu(MENU *&mainMenu, WINDOW *mainWindow,
		const MenuLines &mainMenuInfo, ITEM **&items) {
	size_t menuLineSize, i;		//INPUT- Menu size, iterator
	int cols;			//OUTPUT- Columns of current window

	//Init cols, menuLineSize & items
	cols = getmaxx(mainWindow);
	menuLineSize = sizeof(mainMenuInfo.menuLines)
			/ sizeof(mainMenuInfo.menuLines[0]);
	items = (ITEM**) calloc(menuLineSize + 1, sizeof(ITEM*));

	//Items must be initialized to menu line items
	for (i = 0; i < menuLineSize; i++) {
		items[i] = new_item(mainMenuInfo.menuLines[i],
				mainMenuInfo.menuLines[i]);
	}
	items[menuLineSize] = new_item((char*) NULL, (char*) NULL);

	//Initialize menu, apply settings
	mainMenu = new_menu((ITEM**) items);
	set_menu_win(mainMenu, mainWindow);
	set_menu_sub(mainMenu,
			derwin(mainWindow, menuLineSize,
				sizeof(mainMenuInfo.menuLines[0]), 4,
				(cols - sizeof(mainMenuInfo.menuLines[0])) / 2));
	set_menu_mark(mainMenu, ">");
	post_menu(mainMenu);
}

//Safely kill menu & menu items
void deleteMenu(MENU *&menu, ITEM **&items, size_t menuLineSize) {
	size_t i;	//PROCESS- Iterator for item deletion

	//Free up and delete menu
	unpost_menu(menu);
	free_menu(menu);

	//Free up menu item memory
	for (i = 0; i < menuLineSize; i++) {
		free_item(items[i]);
	}
}

//Start window with settings
void startWindow(WINDOW *&mainWindow) {
	//Initialize screen and add settings
	initscr();
	raw();
	noecho();
	curs_set(0);

	//Initialize main window and add settings
	mainWindow = newwin((3 * LINES / 5), (3 * COLS / 5), (1 * LINES / 5),
			(1 * COLS / 5));
	keypad(mainWindow, TRUE);
	clear();
}

//Safely kill the window
void endWindow(WINDOW *&mainWindow) {
	//Delete main window, refresh, and delete screen
	clear();
	delwin(mainWindow);
	refresh();
	endwin();
}

//Recalculate the window, but keep the menu the same.
void refreshWindow(MENU *&mainMenu, WINDOW *&mainWindow,
		MenuLines mainMenuInfo) {
	size_t menuLineSize;		//INPUT- Size of menu lines for alignment
	size_t cols;			//INPUT- Column count of inner window

	//Initialize menuLineSize
	menuLineSize = sizeof(mainMenuInfo.menuLines)
			/ sizeof(mainMenuInfo.menuLines[0]);

	//Get rid of the window before restarting it
	unpost_menu(mainMenu);
	endWindow(mainWindow);
	refresh();			//Load bearing refresh

	//Start a new window: put the menu in it, draw old data to it
	startWindow(mainWindow);
	cols = getmaxx(mainWindow);
	set_menu_win(mainMenu, mainWindow);
	set_menu_sub(mainMenu,
			derwin(mainWindow, menuLineSize,
				sizeof(mainMenuInfo.menuLines[0]), 4,
				(cols - sizeof(mainMenuInfo.menuLines[0])) / 2));
	box(mainWindow, 0, 0);
	mvwprintw(mainWindow, 1,
			(getmaxx(mainWindow)
				- sizeof(mainMenuInfo.storeName) / sizeof(char)) / 2,
			mainMenuInfo.storeName);
	mvwprintw(mainWindow, 2,
			(getmaxx(mainWindow)
				- sizeof(mainMenuInfo.menuName) / sizeof(char)) / 2,
			mainMenuInfo.menuName);
	post_menu(mainMenu);
	mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
			(getmaxx(mainWindow) - 38) / 2,
			"Select [1-5] or navigate to choice...");
}

//This passes the signal to a state provider: unsafe, but the best we have
void handleSignal(const int signal) {
	stateProvider = signal;
}
