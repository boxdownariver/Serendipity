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

	dontExit = 1;
	int startIndex=0;
	int PAGE_SIZE = 10;

	//Rendering loop
	do {
		makeWindow(repWindow);
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
		mvwprintw(repWindow, 1, 50, "SERENDIPITY BOOKSELLERS");
		mvwprintw(repWindow, 2, 53, "REPORTS LISTING");
		
		// Print book details for the current page
		mvwprintw(repWindow, 3, 30, "PAGE : %d", (startIndex / PAGE_SIZE) + 1);
		mvwprintw(repWindow, 3, 39, " of");
		mvwprintw(repWindow, 3, 43, " %d", (20 + PAGE_SIZE - 1) / PAGE_SIZE);
		int row = 5;
		for (int i = startIndex; i < startIndex + PAGE_SIZE && i < 20; ++i) {
				
            mvwprintw(repWindow, row + 3, 3, "BookNumber %d", i + 1);
				row++;
        }
		//You can also use this like printf!
		// mvwprintw(repWindow, 17, 16, "%sThis string puts spaces in!",trimToSize(hello, 15).c_str());

		/**
		 * This portion gets the user input and matches it to certain keys.
		 * If you need to match to a letter, just use "case '[your char]':"
		 * inside the switch statement. If the key is not a letter or a
		 * number, look for the name of the key in
		 * https://linux.die.net/man/3/getch.
		 */

		mvwprintw(repWindow, 20, 53, "Press < > to navigate. Press ENTER to exit");
		userInput = wgetch(repWindow);
		userInputChar = static_cast<char>(userInput);

		//KEY_UP will go straight to KEY_LEFT. KEY_DOWN will go straight
		//to KEY_RIGHT. Any logic you need for either can go in the
		//KEY_LEFT or KEY_RIGHT blocks respectively.

		if (userInput != KEY_LEFT && userInput != KEY_RIGHT && userInput != 27 && userInput != 10)
		{
			mvwprintw(repWindow, 22, 30, "Other keys are invalid. Only Press < > to navigate. Press ENTER to exit");
			userInput = wgetch(repWindow);
			userInputChar = static_cast<char>(userInput);
		}

		switch (userInput) {
		case KEY_LEFT:
		if (startIndex - PAGE_SIZE >= 0) {
     	startIndex -= PAGE_SIZE;  // Move backward
      }
		break;

		case KEY_RIGHT:
		if (startIndex + PAGE_SIZE < 20) {
     	startIndex += PAGE_SIZE;
		}
		break;
		case 27: ;    //This is ESCAPE key. It's glitchy, I don't know why.
		case 10: dontExit = 0; //This is ENTER key.
		}

	refresh();
	}

	while (dontExit != 0);

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

/**
 * Trims a string to proper size if the size is between 0 and the origin
 * string's size.
 */
string trimToSize(string origin, size_t size) {
	origin.resize(size, ' ');
	origin.shrink_to_fit();
	return origin;
}
