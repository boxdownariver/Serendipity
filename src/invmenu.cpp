/**********************************************************************//**
 * BRANCHING INVENTORY MENU IMPLEMENTATION
 * ________________________________________________________________________
 * This program displays the inventory menu and manages user choices.
 * Displays a notice for full book list.
 * @author Micah Krosby
 * @file invmenu.cpp
 * ________________________________________________________________________
 *
 *	PROCESS-
 * 		BookType[20] bookList -> List of all books currently available
 * 		int currentBookCount -> Count of books currently indexed
 *		int choice -> Menu branching option
 *************************************************************************/
#define menu_utils
#include "headers/menuDipity.h"
#include "headers/lookUp.h"
#include "headers/bookfile.h"
#include "headers/invmenu.h"
#include "headers/bookType.h"
#ifndef addbook
#include "headers/addbook.h"
#endif
#include <iostream>
#ifndef EDITBOOK_HPP
#include "headers/editbook.hpp"
#endif
#ifndef DELETEBOOK_HPP
#include "headers/deleteBook.hpp"
#endif


/**
 * main_invmenu(BookType, int) ->
 * Runs inventory menu interface, then either branches into next menu or
 * moves backward into the previous menu.
 */
int main_invmenu(LinkedListType<BookType *>& bookList) {
	std::string menuName = "Inventory Database";
	std::vector<std::string> menuListing = { "Look Up a Book", "Add a Book",
			"Edit a Book's Record", "Delete a Book", "Enter books from database", "Return to the Main Menu" };
	MenuLines mainMenuInfo;
	std::string startNotif;
	int choice;
	bool keepGoing;
	static bool alreadyAdded = 0;

	mainMenuInfo.menuName = menuName;
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = sizeof("Return to the Main Menu  ") / sizeof(char);

	keepGoing = 1;
	startNotif = "";
	do {
		system("clear");
		choice = makeMenu(mainMenuInfo, startNotif);
		startNotif = "";
		switch (choice) {
		case 0:
			 mainLookUp(bookList);
			 break;
		case 1:
			 addBook(bookList);
			 break;
		case 2:
			mainEditBook(bookList);
			break;
		case 3:
			mainDelete (bookList);
			break;
		case 4:
			if (!alreadyAdded) {
				readFile(bookList);
				startNotif = "--NOTICE-- Books added from database!";
				alreadyAdded = 1;
			} else startNotif = "--NOTICE-- Books already added! Will not re-add books.";
			break;
		case 5:
			keepGoing = 0;
			break;
		default:
			break;
		}
	} while (keepGoing);

	return 0;
}
