#include <iostream>
#include <string>
#include <iomanip>     // To format in decimal places;
#include <cstring>     // To get the length
#include <cstdlib>     // To clear the screen
#include <cctype>      // To check for user choice effectively
#include <limits>      // To handle garbage input well
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <limits>
#include <curses.h>
#include <signal.h>
#include "headers/setColour.h"
#include "headers/invmenu.h"
#include "headers/repListing.h"
#include "headers/reports.h"

void makeWindow(WINDOW *&repWindow);
void delWindow(WINDOW *&repWindow);
void refWindow(WINDOW *&repWindow);
string trimToSize(string origin, size_t size);

int mainRepListing (BookType *books[])
{
	WINDOW * repWindow = NULL;
	struct sigaction sa;
	int userInput;
	char userInputChar;
	bool dontExit;

//	cout << "Inside Reports Listing\n";
//
//	cout << "Press Enter to Continue..\n";
//	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	makeWindow(repWindow);
	dontExit = 1;

	//Rendering loop
	while (dontExit) {
		/**
		 * Sample output.
		 *
		 * mvwprintw => move in window, print to window.
		 *
		 * repWindow is the inner window with the screen. There is a window
		 * that holds this, but it should not be needed for printing.
		 *
		 * 16, 16 is for 16 lines down, 16 columns in.
		 *
		 * trimToSize trims your string to whatever size you might need,
		 * however this function only accepts cstrings, so convert the
		 * result using the c_str() method.
		 */
		mvwprintw(repWindow, 16, 16, trimToSize("Hello World", 5).c_str());

		/**
		 * This portion gets the user input and matches it to certain keys.
		 * If you need to match to a letter, just use "case '[your char]':"
		 * inside the switch statement. If the key is not a letter or a
		 * number, look for the name of the key in
		 * https://linux.die.net/man/3/getch.
		 */
		userInput = wgetch(repWindow);
		userInputChar = static_cast<char>(userInput);

		//KEY_UP will go straight to KEY_LEFT. KEY_DOWN will go straight
		//to KEY_RIGHT. Any logic you need for either can go in the
		//KEY_LEFT or KEY_RIGHT blocks respectively.
		switch (userInput) {
		case KEY_UP: ;
		case KEY_LEFT: break;
		case KEY_DOWN: ;
		case KEY_RIGHT: break;
		case 27: ;    //This is ESCAPE key. It's glitchy, I don't know why.
		case 10: dontExit = 0; //This is ENTER key.
		}
	}

	//This has to be called at the end for memory and to pass back to the
	//window preceding it.
	delWindow(repWindow);
	system("clear");
	cout << endl;

	return 0;
}

/**
 * Makes a window for print job
 */
void makeWindow(WINDOW *&repWindow) {
	//Init screen
	initscr();
	raw();
	noecho();
	curs_set(0);

	//Init window in screen, allow arrow keys, box window
	repWindow = newwin(max(LINES - 6, 0), max(COLS - 6, 0), 3, 3);
	keypad(repWindow, true);
	clear();
	box(repWindow, 0, 0);
	wrefresh(repWindow);
}

/**
 * Deletes window
 */
void delWindow(WINDOW *&repWindow) {
	clear();
	delwin(repWindow);
	refresh();
	endwin();
}

/**
 * Refreshes window when needed
 */
void refWindow(WINDOW *&repWindow) {
	delWindow(repWindow);
	makeWindow(repWindow);
}

string trimToSize(string origin, size_t size) {
	return (size > 0 && size < origin.size())? origin.substr(0, size):origin;
}
