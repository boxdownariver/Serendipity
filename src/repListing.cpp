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
#include "headers/cashier.h"
#include "headers/signal.hpp"

//volatile sig_atomic_t sigHandler = 0;

//void handleSig(int sig);

void makeWindow(WINDOW *&repWindow);
void delWindow(WINDOW *&repWindow);
void refWindow(WINDOW *&repWindow);
string trimToSize(string origin, size_t size);

/**
 * @brief Sorts and displays a copy of the book list using selection sort.
 *
 * This function creates a shallow copy of the original linked list of books,
 * sorts the copied list using the selection sort algorithm, and then passes 
 * the sorted list to the mainRepListing function to be displayed. 
 * After displaying, it nullifies the data in the copied list to free memory.
 *
 * @param books A reference to a pointer to a LinkedListType containing BookType pointers.
 */
void mainSorting(LinkedListType<BookType *>& books)
{
	// First make a copy of existing books
		LinkedListType<BookType *> sortedList = books.shallowCopy();

	// Now sort them
		sortedList.selectionSort();

	// Pass to display books
		mainRepListing(sortedList);

	// Nullify it
		sortedList.nullifyData();
}

/**
 * @brief Calculates and displays the total wholesale or retail cost of all books.
 *
 * This function iterates through the linked list of books and calculates either:
 * - The total wholesale cost (`W` indicator), or
 * - The total retail cost (`R` indicator),
 * depending on the character `indicator` provided.
 *
 * The calculated total is passed to the `mainCostListing()` function for display.
 *
 * @param books A reference to a pointer to the linked list containing BookType objects.
 * @param indicator A character ('W' or 'R') that determines which total to calculate:
 *        - 'W' for wholesale
 *        - 'R' for retail
 */
void mainCalculations(LinkedListType<BookType *>& books, char indicator)
{
	LinkedListIterator<BookType *> iterator(books);
	int startIndex=0;
	iterator.indexOf(startIndex);
	double totalR = 0.0;
	double totalW = 0.0 ;

	for (startIndex = 0; startIndex < BookType::getBookCount(); startIndex++ )
	{
		totalW += iterator.get()->getQtyOnHand() * iterator.get()->getWholesale();
		totalR += iterator.get()->getQtyOnHand() * iterator.get()->getRetail();
		++iterator;

	}

	if (indicator == 'W'){
		mainCostListing (books, "Wholesale", totalW);
	}

	if (indicator == 'R'){
		mainCostListing (books, "Retail", totalR);
	}

}

/**
 * @brief Displays a paginated report of all books in the inventory using ncurses windows.
 *
 * This function creates a report window using ncurses to display detailed information
 * about each book in a paginated format (10 books per page). It uses a custom iterator
 * to traverse the linked list of BookType objects and prints the following fields:
 * Title, ISBN, Author, Publisher, Date Added, Quantity On Hand, Wholesale Price, and Retail Price.
 *
 * Features:
 * - Displays custom report headings depending on sorting flags.
 * - Supports navigation using arrow keys: `<` (KEY_LEFT) and `>` (KEY_RIGHT).
 * - Allows exiting using the ENTER key (10) or ESC (27).
 * - Uses alternating color pairs for row highlighting.
 *
 * @param books A reference to the linked list of BookType pointers to be displayed.
 * @return Returns 0 after the user exits the report view.
 */
int mainRepListing (LinkedListType<BookType *>& books)
{

	LinkedListIterator<BookType *> iterator(books);
	WINDOW * repWindow = NULL;
	int userInput;
	char userInputChar;
	bool dontExit;

	if (BookType::getBookCount() == 0)
	{
		// immediately exit program
		system ("clear");
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
		cout << "║ " << setw (98) << left << "The book list is empty. No books available for reports listing." << " ║ \n" ;
	   	cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 0;
	}

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

		if (BookType::getFlag() == 5){
			mvwprintw(repWindow, 2, 44, "REPORTS SORTED BY AGE / DATE ADDED");
		}

		else if (BookType::getFlag() == 6){
			mvwprintw(repWindow, 2, 45, "REPORTS SORTED BY QUANTITY ON HAND");
		}

		else if (BookType::getFlag() == 8){
			mvwprintw(repWindow, 2, 47, "REPORTS SORTED BY RETAIL PRICE");
		}

		else {
				mvwprintw(repWindow, 2, 53, "REPORTS LISTING");
		}
		// Print book details for the current page
		wattron(repWindow, COLOR_PAIR(2)); // Green color
		mvwprintw(repWindow, 4, 10, "DATE : %s", generateDate().c_str());
		wattroff(repWindow, COLOR_PAIR(2)); // Green turned off
		
		wattron(repWindow, COLOR_PAIR(5)); // Cyan color
		mvwprintw(repWindow, 4, 30, "PAGE : %d", (startIndex / PAGE_SIZE) + 1);
		mvwprintw(repWindow, 4, 39, " of");
		mvwprintw(repWindow, 4, 43, " %d",(BookType::getBookCount() + PAGE_SIZE - 1) / PAGE_SIZE);
		wattroff(repWindow, COLOR_PAIR(5)); // Cyan turned off

		wattron(repWindow, COLOR_PAIR(2)); // Green color
		// mvwprintw(repWindow, 4, 50, "DATABASE SIZE : %d", 20);
		mvwprintw(repWindow, 4, 85, "CURRENT BOOK COUNT : %d", BookType::getBookCount());
		wattroff(repWindow, COLOR_PAIR(2)); // Green turned off


		mvwprintw(repWindow, 6, 2, "TITLE");
		mvwprintw(repWindow, 6, 31, "ISBN");
		mvwprintw(repWindow, 6, 45, "AUTHOR");
		mvwprintw(repWindow, 6, 61, "PUBLISHER");
		mvwprintw(repWindow, 6, 75, "DATE ADDED");
		mvwprintw(repWindow, 6, 87, "QTY ON");
		mvwprintw(repWindow, 6, 95, "WHOLESALE");
		mvwprintw(repWindow, 6, 109, "RETAIL");

		mvwprintw(repWindow, 7, 89, "HAND");
		mvwprintw(repWindow, 7, 100, "COST");
		mvwprintw(repWindow, 7, 110, "PRICE");
		mvwprintw(repWindow, 8, 2, "***************************");
		mvwprintw(repWindow, 8, 31, "*************");
		mvwprintw(repWindow, 8, 45, "**************");
		mvwprintw(repWindow, 8, 61, "***********");
		mvwprintw(repWindow, 8, 75, "**********");
		mvwprintw(repWindow, 8, 87, "******");
		mvwprintw(repWindow, 8, 96, "********");
		mvwprintw(repWindow, 8, 107, "********");

		int row = 9;
		char quantity[10];
		char wholesale[20];
		char retail[20];
		int colorPair;
		iterator.indexOf(startIndex);
		for (int i = startIndex; i < startIndex + PAGE_SIZE && i < BookType::getBookCount(); ++i) {
				if (i % 3 == 0)	{colorPair = 2;}
				else if (i % 3 == 1) {colorPair = 5; }
				else {colorPair = 3;}

				wattron(repWindow, COLOR_PAIR(colorPair));
				mvwprintw(repWindow, row, 2, trimToSize(iterator.get()->getTitle(), 27).c_str());
				mvwprintw(repWindow, row, 31, "%s", iterator.get()->getISBN().c_str());
				mvwprintw(repWindow, row, 45, trimToSize(iterator.get()->getAuthor(), 14).c_str());
				mvwprintw(repWindow, row, 61, trimToSize(iterator.get()->getPub(), 11).c_str());
				mvwprintw(repWindow, row, 75, trimToSize(iterator.get()->getDateAdded(), 10).c_str());
				sprintf(quantity, "%2d", iterator.get()->getQtyOnHand());  // Format `int` as string
				mvwprintw(repWindow, row, 91, "%s", quantity);

				// Wholesale Price
				mvwprintw(repWindow, row, 96, "$");
				sprintf(wholesale, "%*.*f", 7, 2, iterator.get()->getWholesale());
				mvwprintw(repWindow, row, 97, "%s", wholesale);

				// Retail price
				mvwprintw(repWindow, row, 107, "$");
				sprintf(retail, "%*.*f", 7, 2, iterator.get()->getRetail());
				mvwprintw(repWindow, row, 108, "%s", retail);
				wattroff(repWindow, COLOR_PAIR(colorPair));
				row ++;
				++iterator;
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

		mvwprintw(repWindow, 22 , 40, "Press < > to navigate. Press ENTER to exit");
		userInput = wgetch(repWindow);
		userInputChar = static_cast<char>(userInput);

		//KEY_UP will go straight to KEY_LEFT. KEY_DOWN will go straight
		//to KEY_RIGHT. Any logic you need for either can go in the
		//KEY_LEFT or KEY_RIGHT blocks respectively.

		if (userInput != KEY_LEFT && userInput != KEY_RIGHT && userInput != 27 && userInput != 10)
		{
			mvwprintw(repWindow,24 , 30, "Other keys are invalid. Only Press < > to navigate. Press ENTER to exit");
			userInput = wgetch(repWindow);
			userInputChar = static_cast<char>(userInput);
		}

		switch (userInput) {
		case KEY_LEFT:
		if (startIndex - PAGE_SIZE >= 0) {
     	startIndex -= PAGE_SIZE;  // Move backward
      }

		else {
		startIndex = ((BookType::getBookCount() -1 )/ PAGE_SIZE) * PAGE_SIZE; // goes to the last page
		}
		break;

		case KEY_RIGHT:
		if (startIndex + PAGE_SIZE < BookType::getBookCount()) {
     	startIndex += PAGE_SIZE;   //Move forward
		}

		else {
		startIndex = 0; // Back to first page
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
 * @brief Displays a paginated cost report (wholesale or retail) of all books.
 *
 * This function generates a ncurses window report listing either the **wholesale**
 * or **retail** cost of books in inventory. It displays 10 books per page and allows
 * navigation between pages using the left and right arrow keys (`KEY_LEFT`, `KEY_RIGHT`).
 *
 * Each book entry shows:
 * - Title
 * - ISBN
 * - Quantity on Hand
 * - Wholesale or Retail Price (depending on `header`)
 *
 * The total cost for all displayed books is calculated outside and shown at the bottom.
 *
 * @param books A reference to the linked list of `BookType*` to be displayed.
 * @param header A string label indicating the cost type: "Wholesale" or "Retail".
 * @param totalPrice The pre-computed total cost to be displayed at the bottom.
 *
 * @return Returns 0 after exiting the report screen.
 */
int mainCostListing (LinkedListType<BookType *>& books, string header, double totalPrice)
{

	LinkedListIterator<BookType *> iterator(books);
	WINDOW * repWindow = NULL;
	int userInput;
	char userInputChar;
	bool dontExit;

	if (BookType::getBookCount() == 0)
	{
		// immediately exit program
		system ("clear");
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
		cout << "║ " << setw (98) << left << "The book list is empty. No books available for reports listing." << " ║ \n" ;
	   	cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 0;
	}

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
		//mvwprintw(repWindow, 2, 53, "REPORTS LISTING");
		mvwprintw(repWindow, 2, 53, "%s", header.c_str());
		mvwprintw(repWindow, 2, 63, "Listing");
		
		// Print book details for the current page
		wattron(repWindow, COLOR_PAIR(2)); // Green color
		mvwprintw(repWindow, 4, 10, "DATE : %s", generateDate().c_str());
		wattroff(repWindow, COLOR_PAIR(2)); // Green turned off
		
		wattron(repWindow, COLOR_PAIR(5)); // Cyan color
		mvwprintw(repWindow, 4, 30, "PAGE : %d", (startIndex / PAGE_SIZE) + 1);
		mvwprintw(repWindow, 4, 39, " of");
		mvwprintw(repWindow, 4, 43, " %d",(BookType::getBookCount() + PAGE_SIZE - 1) / PAGE_SIZE);
		wattroff(repWindow, COLOR_PAIR(5)); // Cyan turned off

		wattron(repWindow, COLOR_PAIR(2)); // Green color
		// mvwprintw(repWindow, 4, 50, "DATABASE SIZE : %d", 20);
		mvwprintw(repWindow, 4, 85, "CURRENT BOOK COUNT : %d", BookType::getBookCount());
		wattroff(repWindow, COLOR_PAIR(2)); // Green turned off


		mvwprintw(repWindow, 6, 22, "TITLE");
		mvwprintw(repWindow, 6, 61, "ISBN");
		mvwprintw(repWindow, 6, 82, "QTY ON");

		if (header == "Wholesale"){
		mvwprintw(repWindow, 6, 95, "WHOLESALE");
		}

		if (header == "Retail"){
		mvwprintw(repWindow, 6, 98, "RETAIL");
		}


		mvwprintw(repWindow, 7, 84, "HAND");
		mvwprintw(repWindow, 7, 100, "COST");
		
		mvwprintw(repWindow, 8, 22, "***************************");
		mvwprintw(repWindow, 8, 61, "*************");
		mvwprintw(repWindow, 8, 82, "******");
		mvwprintw(repWindow, 8, 96, "********");
		
		int row = 9;
		char quantity[10];
		char wholesale[20];
		char retail[20];
		char totalCost[20];
 
		int colorPair;
		iterator.indexOf(startIndex);
		for (int i = startIndex; i < startIndex + PAGE_SIZE && i < BookType::getBookCount(); ++i) {
				if (i % 3 == 0)	{colorPair = 2;}
				else if (i % 3 == 1) {colorPair = 5; }
				else {colorPair = 3;}

				wattron(repWindow, COLOR_PAIR(colorPair));
				mvwprintw(repWindow, row, 22, trimToSize(iterator.get()->getTitle(), 27).c_str());
				mvwprintw(repWindow, row, 61, "%s", iterator.get()->getISBN().c_str());
				sprintf(quantity, "%2d", iterator.get()->getQtyOnHand());  // Format `int` as string
				mvwprintw(repWindow, row, 86, "%s", quantity);

				if (header == "Wholesale"){
				mvwprintw(repWindow, row, 96, "$");
				sprintf(wholesale, "%*.*f", 7, 2, iterator.get()->getWholesale());
				mvwprintw(repWindow, row, 97, "%s", wholesale);
				}

				if (header == "Retail"){
				// Retail price
				mvwprintw(repWindow, row, 96, "$");
				sprintf(retail, "%*.*f", 7, 2, iterator.get()->getRetail());
				mvwprintw(repWindow, row, 97, "%s", retail);
				}

				wattroff(repWindow, COLOR_PAIR(colorPair));
				row ++;
				++iterator;
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
		mvwprintw(repWindow, 20, 45, "Total %s", header.c_str());
		mvwprintw(repWindow, 20, 65, "$");
		
		sprintf(totalCost, "%*.*f", 7, 2, totalPrice);
		mvwprintw(repWindow, 20, 70, "%s", totalCost);

		mvwprintw(repWindow, 22 , 40, "Press < > to navigate. Press ENTER to exit");
		userInput = wgetch(repWindow);
		userInputChar = static_cast<char>(userInput);

		//KEY_UP will go straight to KEY_LEFT. KEY_DOWN will go straight
		//to KEY_RIGHT. Any logic you need for either can go in the
		//KEY_LEFT or KEY_RIGHT blocks respectively.

		if (userInput != KEY_LEFT && userInput != KEY_RIGHT && userInput != 27 && userInput != 10)
		{
			mvwprintw(repWindow,24 , 30, "Other keys are invalid. Only Press < > to navigate. Press ENTER to exit");
			userInput = wgetch(repWindow);
			userInputChar = static_cast<char>(userInput);
		}

		switch (userInput) {
		case KEY_LEFT:
		if (startIndex - PAGE_SIZE >= 0) {
     	startIndex -= PAGE_SIZE;  // Move backward
      }

		else {
		startIndex = ((BookType::getBookCount() -1 )/ PAGE_SIZE) * PAGE_SIZE; // goes to the last page
		}
		break;

		case KEY_RIGHT:
		if (startIndex + PAGE_SIZE < BookType::getBookCount()) {
     	startIndex += PAGE_SIZE;   //Move forward
		}

		else {
		startIndex = 0; // Back to first page
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
	//initscr();
	raw();
	noecho();
	curs_set(0);

	// Enable color mode
    if (has_colors()) {
        start_color();
        use_default_colors(); // Allows transparency with terminal's background
        
        // Define color pairs (Foreground, Background)
        init_pair(1, COLOR_RED, -1);        // Red text
        init_pair(2, COLOR_GREEN, -1);      // Green text
        init_pair(3, COLOR_YELLOW, -1);     // Yellow text
        init_pair(4, COLOR_BLUE, -1);       // Blue text
        init_pair(5, COLOR_CYAN, -1);       // Cyan text
        init_pair(6, COLOR_WHITE, -1);      // Default White text
    }


	//Init window in screen, allow arrow keys, box window
	repWindow = newwin(max(LINES - 6, 0), max(COLS - 6, 0), 3, 3);
	keypad(repWindow, true);
	clear();
	box(repWindow, 0, 0);
	wrefresh(repWindow);
	return;
}

/**
 * Deletes window
 */
void delWindow(WINDOW *&repWindow) {
	clear();
	delwin(repWindow);
	refresh();
	endwin();
	return;
}

/**
 * Refreshes window when needed
 */
void refWindow(WINDOW *&repWindow) {
	delWindow(repWindow);
	makeWindow(repWindow);
	return;
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
/*
void handleSig(int sig) {
	sigHandler = sig;
	return;
}*/
