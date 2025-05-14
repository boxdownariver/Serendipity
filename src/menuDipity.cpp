/**********************************************************************//**
 * MENU GENERALIZATION
 *_________________________________________________________________________
 * This program generates menu interfaces for the Serendipity project
 * @author Micah Krosby
 * @file menuDipity.cpp
 *_________________________________________________________________________
 *
 *	INPUTS-
 *	    Key input (char) -> Keyboard-based instruction for the program
 *	    Signals (int) -> Signals passed by the system
 *	    mainMenuInfo (char *, char **, char *) -> Menu name,
 *	    					menu options, store name
 *	OUTPUTS-
 *	    mainWindow -> Window containing mainMenu interface
 *************************************************************************/
#define menu_utils
#include <curses.h>
#include <signal.h>
#include "headers/signal.hpp"
#include <menu.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#ifndef string
#include <string.h>
#endif
#include "headers/menuDipity.h"

void createMenu(MENU *&mainMenu, WINDOW *mainWindow,
		const MenuLines &mainMenuInfo, ITEM **&items);
void deleteMenu(MENU *&mainMenu, ITEM **&items, size_t menuLineSize);
void startWindow(WINDOW *&mainWindow);
void endWindow(WINDOW *&mainWindow);
//void handleSignal(const int signal);
void refreshWindow(MENU *&mainMenu, WINDOW *&mainWindow,
		WINDOW *&notification, const MenuLines &mainMenuInfo);

volatile sig_atomic_t stateProvider = 0;

/**
 * makeMenu(MenuLines, string) ->
 * Makes a basic menu interface, using a MenuLines object holding the
 * title of the program, the title of the menu, and the titles of the
 * options, as well as a string holding the information potentially
 * required for initial notification of the user.
 */
int makeMenu(MenuLines &mainMenuInfo, std::string startInfo) {
	ITEM **items;		  //OUTPUT- Menu items
	MENU *mainMenu;		  //OUTPUT- Complete menu
	WINDOW *mainWindow;	  //OUTPUT- Window to hold menu
	WINDOW *notification; //OUTPUT- Notification at bottom of screen
	//struct sigaction sa;  //OUTPUT- Signal action handler
	int breakOut;		  //OUTPUT- Return of menu (for when it breaks out)
	int menuLineSize;     //INPUT-  Size of the list of menu lines
	int userInput;		  //INPUT-  User key input
	char userInputChar;	  //INPUT-  User input (hard- coded as char)
	char userInputArr[2];		//INPUT- User input (String)
	char *currentItemName;//INPUT-  Name of item currently selected
	bool dontExit;		  //INPUT-  Prevent exiting until need is met

	//Init menuLineSize and userInputChar
	userInputChar = '1';
	userInputArr[0] = '1';
	userInputArr[1] = '\0';

	menuLineSize = mainMenuInfo.menuLines.size();

	/*
	//Handle system signals
	sa.sa_flags = 0;
	sa.sa_handler = handleSignal;
	sigaction(SIGWINCH, &sa, NULL);
	*/

	//Init window, items, menu
	startWindow(mainWindow);
	createMenu(mainMenu, mainWindow, mainMenuInfo, items);

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
			"Select [1-%d] or navigate to module...", menuLineSize);
	wrefresh(mainWindow);

	notification = newwin(1, 3 * COLS / 5, 9 * LINES / 10, COLS / 5);
	wprintw(notification, startInfo.c_str());
	wrefresh(notification);

	//Main program loop
	dontExit = 1;
	breakOut = -1;
	do {
		if (stateProvider) {
			refreshWindow(mainMenu, mainWindow, notification,
					mainMenuInfo);
			stateProvider = 0;
		}
		userInput = wgetch(mainWindow);
		userInputChar = userInput - 1;
		//Navigate the menu with input
		switch (userInput) {
		case 10:
			//Activate current user selection
			breakOut = item_index(current_item(mainMenu));
			if (breakOut < menuLineSize && breakOut != -1
					/*&& (mainMenuInfo.menuName == "Main Menu"
							|| (mainMenuInfo.menuName
									== "Inventory Database"
									&& (breakOut <= 3 && breakOut != -1)) || (mainMenuInfo.menuName == "Reports" && (breakOut == 0))
									|| breakOut == menuLineSize - 1)*/
			) {
				dontExit = 0;
			}
			wclear(notification);
			currentItemName = (char*) item_name(current_item(mainMenu));
			wprintw(notification, "Selected %s", currentItemName);
			wrefresh(notification);
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
			if (userInput >= '1' && userInput <= menuLineSize + 48) {
				wclear(notification);
				userInputArr[0] = userInputChar;
				set_current_item(mainMenu, items[atoi(userInputArr)]);
				wrefresh(notification);
			} else {
				wclear(notification);
				wprintw(notification, "Invalid Input");
				wrefresh(notification);
			}
			break;
		}
	} while (dontExit);

	clear();
	if (strcmp(item_name(current_item(mainMenu)), "Exit") == 0) {
		mvwprintw(mainWindow, getmaxy(mainWindow) / 2,
				getmaxx(mainWindow) / 2 - 5, "Goodbye!");
		wrefresh(mainWindow);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	//End program
	wclear(notification);
	delwin(notification);
	deleteMenu(mainMenu, items, mainMenuInfo.menuLines.size());
	endWindow(mainWindow);

	return breakOut;
}

///Create menu & menu items
void createMenu(MENU *&mainMenu, WINDOW *mainWindow,
		const MenuLines &mainMenuInfo, ITEM **&items) {
	size_t menuLineSize, i;		//INPUT- Menu size, iterator
	int cols;			//OUTPUT- Columns of current window

	//Init cols, menuLineSize & items
	cols = getmaxx(mainWindow);
	menuLineSize = mainMenuInfo.menuLines.size();
	items = (ITEM**) calloc(menuLineSize + 1, sizeof(ITEM*));

	//Items must be initialized to menu line items
	for (i = 0; i < menuLineSize; i++) {
		items[i] = new_item(mainMenuInfo.menuLines[i].c_str(),
				mainMenuInfo.menuLines[i].c_str());
	}
	items[menuLineSize] = new_item((char*) NULL, (char*) NULL);

	//Initialize menu, apply settings
	mainMenu = new_menu((ITEM**) items);
	set_menu_win(mainMenu, mainWindow);
	set_menu_sub(mainMenu,
			derwin(mainWindow, menuLineSize,
					mainMenuInfo.longestMenuLength, 4,
					(cols - mainMenuInfo.longestMenuLength) / 2));
	set_menu_mark(mainMenu, ">");
	post_menu(mainMenu);
}


///Create menu & menu items WITH a middle split for printing on the
///right side of the screen.
void createMenuMiddleSplit(MENU *&mainMenu, WINDOW *mainWindow,
		const MenuLines &mainMenuInfo, ITEM **&items) {
	size_t menuLineSize, i;		//INPUT- Menu size, iterator
	int cols;			//OUTPUT- Columns of current window

	//Init cols, menuLineSize & items
	cols = getmaxx(mainWindow);
	menuLineSize = mainMenuInfo.menuLines.size();
	items = (ITEM**) calloc(menuLineSize + 1, sizeof(ITEM*));

	//Items must be initialized to menu line items
	for (i = 0; i < menuLineSize; i++) {
		items[i] = new_item(mainMenuInfo.menuLines[i].c_str(),
				mainMenuInfo.menuLines[i].c_str());
	}
	items[menuLineSize] = new_item((char*) NULL, (char*) NULL);

	//Initialize menu, apply settings
	mainMenu = new_menu((ITEM**) items);
	set_menu_win(mainMenu, mainWindow);
	set_menu_sub(mainMenu,
			derwin(mainWindow, menuLineSize,
					mainMenuInfo.longestMenuLength, 4,
					1));
	set_menu_mark(mainMenu, ">");
	post_menu(mainMenu);
}

///Safely kill menu & menu items
void deleteMenu(MENU *&menu, ITEM **&items, size_t menuLineSize) {
	size_t i;	//PROCESS- Iterator for item deletion

	//Free up and delete menu
	unpost_menu(menu);
	free_menu(menu);

	//Free up menu item memory
	for (i = 0; i < menuLineSize; i++) {
		free_item(items[i]);
	}
	free(items);
}

///Start window with default esettings
void startWindow(WINDOW *&mainWindow) {
	//Initialize screen and add settings
	//initscr();
	raw();
	noecho();
	curs_set(0);

	//Initialize main window and add settings
	mainWindow = newwin((3 * LINES / 5), (3 * COLS / 5), (LINES / 5),
			(COLS / 5));
	keypad(mainWindow, TRUE);
	clear();
}

///Safely kill the window
void endWindow(WINDOW *&mainWindow) {
	//Delete main window, refresh, and delete screen
	clear();
	delwin(mainWindow);
	refresh();
	endwin();
	//exit_curses(0);
}

///Recalculate the window, but keep the menu the same.
void refreshWindow(MENU *&mainMenu, WINDOW *&mainWindow,
		WINDOW *&notification, const MenuLines &mainMenuInfo) {
	size_t menuLineSize;		//INPUT- Size of menu lines for alignment
	size_t cols;			//INPUT- Column count of inner window

	//Initialize menuLineSize
	menuLineSize = mainMenuInfo.menuLines.size();

	//Get rid of the window before restarting it
	unpost_menu(mainMenu);
	endWindow(mainWindow);
	wclear(notification);
	delwin(notification);
	refresh();			//Load bearing refresh

	//Start a new window: put the menu in it, draw old data to it
	notification = newwin(1, 3 * COLS / 5, 9 * LINES / 10, COLS / 5);
	startWindow(mainWindow);
	cols = getmaxx(mainWindow);
	set_menu_win(mainMenu, mainWindow);
	set_menu_sub(mainMenu,
			derwin(mainWindow, menuLineSize,
					mainMenuInfo.longestMenuLength, 4,
					(cols - mainMenuInfo.longestMenuLength) / 2));
	box(mainWindow, 0, 0);
	mvwprintw(mainWindow, 1,
			((getmaxx(mainWindow) - mainMenuInfo.storeName.length()) / 2),
			mainMenuInfo.storeName.c_str());
	mvwprintw(mainWindow, 2,
			((getmaxx(mainWindow) - mainMenuInfo.menuName.length()) / 2),
			mainMenuInfo.menuName.c_str());
	post_menu(mainMenu);
	mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
			(getmaxx(mainWindow) - 38) / 2,
			"Select [1-%d] or navigate to module...", menuLineSize);
}


///Recalculate the window WITH a middle split, but keep the menu the same.
///Refer to refreshWindow for original implementation
void refreshWindowMiddleSplit(MENU *&mainMenu, WINDOW *&mainWindow,
		WINDOW *&notification, const MenuLines &mainMenuInfo) {
	size_t menuLineSize;		//INPUT- Size of menu lines for alignment
	size_t cols;			//INPUT- Column count of inner window

	//Initialize menuLineSize
	menuLineSize = mainMenuInfo.menuLines.size();

	//Get rid of the window before restarting it
	unpost_menu(mainMenu);
	endWindow(mainWindow);
	wclear(notification);
	delwin(notification);
	refresh();			//Load bearing refresh

	//Start a new window: put the menu in it, draw old data to it
	notification = newwin(1, 3 * COLS / 5, 9 * LINES / 10, COLS / 5);
	startWindow(mainWindow);
	box(mainWindow, 0, 0);
	cols = getmaxx(mainWindow);
	set_menu_win(mainMenu, mainWindow);
	set_menu_sub(mainMenu,
			derwin(mainWindow, menuLineSize,
					mainMenuInfo.longestMenuLength, 4,
					1));
	mvwprintw(mainWindow, 1,
			((getmaxx(mainWindow) - mainMenuInfo.storeName.length()) / 2),
			mainMenuInfo.storeName.c_str());
	mvwprintw(mainWindow, 2,
			((getmaxx(mainWindow) - mainMenuInfo.menuName.length()) / 2),
			mainMenuInfo.menuName.c_str());
	post_menu(mainMenu);
	mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
			(getmaxx(mainWindow) - 38) / 2,
			"Select [1-%d] or navigate to module...", menuLineSize);
}

///This passes signals to the state provider; normally means recalculating the interface.
void handleSignal(const int signal) {
	stateProvider = signal;
	return;
}
