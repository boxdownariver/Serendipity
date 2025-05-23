/**********************************************************************//**
 * EDIT BOOK INTERFACE IMPLEMENTATION
 * ________________________________________________________________________
 * This program displays a menu to edit books, as well as a stub preview of
 * the book in question. This program does not work with 0 available books.
 * @author Micah Krosby
 * @file editbook.cpp
 * ________________________________________________________________________
 *
 *	INPUTS-
 * 		BookType[20] bookList, int currentSize -> Book list with current
 * 			quantity of available book types.
 *	OUTPUTS-
 * 		WINDOW * mainWindow -> Window containing all sub-interfaces
 * 		WINDOW * notification -> Window containing notifications for the
 * 			user; also contains form for filling in book members.
 * 		WINDOW * bookDisplayWindow -> Window containing stub preview of
 * 			book members.
 *************************************************************************/
#ifndef FORM_H
#include <form.h>
#endif
#ifndef __NCURSES_H
#include <curses.h>
#endif
#ifndef ETI_MENU
#include <menu.h>
#endif
#ifndef EDITBOOK_HPP
#include "headers/editbook.hpp"
#endif
#ifndef menu_driver_h
#include "headers/menuDipity.h"
#endif
#ifndef _SIGNAL_H
#include <signal.h>
#endif
#ifndef GLIBCXX_CSTRING
#include <cstring>
#endif
#ifndef GLIBCXX_DEQUE
#include <deque>
#endif
#ifndef lookUp
#include "headers/lookUp.h"
#endif
#include <iostream>
#include "headers/signal.hpp"

///Signal handler for window size change
//void bhandleSignal(const int signal);

//volatile sig_atomic_t bstateProvider = 0;

/**
 * mainEditBook(BookType, int) ->
 * Generates menu for book editing, following a quick search for the book
 * in question.
 */
void mainEditBook(LinkedListType<BookType *>& bookList) {
	std::string searchTerm;
	int bookIndex;

	if (BookType::getBookCount()) {
		std::cout << "╔══════════════════════════════╗" << std::endl;
		std::cout << "║Please enter a book to edit...║" << std::endl;
		std::cout << "╚══════════════════════════════╝" << std::endl;
		std::getline(std::cin, searchTerm);

		bookIndex = findString(searchTerm, bookList, BookType::getBookCount());
		if (bookIndex > -1) {
			editBook(bookList, bookIndex);
		} else {
			std::cout << "Press enter to continue..." << std::endl;
			std::getline(std::cin, searchTerm);
		}
	} else {
		std::cout << "╔════════════════════════════════════════════╗" << std::endl;
		std::cout << "║No books to edit! Press enter to continue...║"
				<< std::endl;
		std::cout << "╚════════════════════════════════════════════╝" << std::endl;
		std::getline(std::cin, searchTerm);
	}
}

/**
 * atrim(string, WINDOW *) ->
 * Trims string to appropriate size depending on whitespaces and window
 * size.
 */
const char* atrim(const std::string operandString, WINDOW * window) {
	static std::string returnString;
	size_t iter;
	int maxSize;

	returnString = std::string(operandString);
	for (iter = 0;
			iter < returnString.length()
					&& returnString.c_str()[iter] == ' '; iter++)
		;
	returnString.erase(0, iter);
	returnString.shrink_to_fit();

	maxSize =  (getmaxx(window) - sizeof("Title            : ") - 2);
	//maxSize = 15;
	if ((int)returnString.length() > maxSize) {
		returnString.erase(maxSize - 3, returnString.length());
		returnString.append("...");
	}
	returnString.shrink_to_fit();
	return returnString.c_str();
}

/**
 * editBook(BookType, int) ->
 * The meat and potatoes of the edit interface. Creates the menu with an
 * associated display, and allows the user to select members of a book to
 * mutate. Then offers the option to overwrite the current book in-place,
 * and an option to exit. Warns before writing or exiting without writing.
 */
void editBook(LinkedListType<BookType *>& bookList, int bookIndex) {
	WINDOW *mainWindow;
	WINDOW *bookDisplayWindow;
	WINDOW *notification;
	ITEM **items;
	MENU *mainMenu;
	FIELD *userInputField;
	FORM *userInputForm;
	MenuLines mainMenuInfo;
	BookType bookBuffer;
	std::deque<int> fieldQueue;
//	struct sigaction sa;
	size_t input;
	int choice;
	int formch;
	char inputChar;
	char inputArr[2];
	char *fieldBuffer;
	bool continueMenu;
	int exitChar;
	int queueSize;
	bool bookWritten;

	std::vector<std::string> menuListing = { "Enter Book Title",
			"Enter ISBN", "Enter Author", "Enter Publisher",
			"Enter Date Added (mm/dd/yyyy)", "Enter Quantity on Hand",
			"Enter Wholesale Value", "Enter Retail Price",
			"Save Book to Database", "Exit" };

	mainMenuInfo.menuName = "Edit a Book";
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength =
			sizeof("Enter Date Added (mm/dd/yyyy)") / sizeof(char);
/*
	sa.sa_flags = 0;
	sa.sa_handler = bhandleSignal;
	sigaction(SIGWINCH, &sa, NULL);
*/
	startWindow(mainWindow);
	createMenuMiddleSplit(mainMenu, mainWindow, mainMenuInfo, items);

	inputChar = '1';
	inputArr[0] = '1';
	inputArr[1] = '\0';
	input = 0;
	continueMenu = 1;
	choice = -1;

	//Print menu dialog
	box(mainWindow, 0, 0);
	mvwprintw(mainWindow, 1,
			(getmaxx(mainWindow) - (int)mainMenuInfo.storeName.length()) / 2,
			mainMenuInfo.storeName.c_str());
	mvwprintw(mainWindow, 2,
			(getmaxx(mainWindow) - (int)mainMenuInfo.menuName.length()) / 2,
			mainMenuInfo.menuName.c_str());
	post_menu(mainMenu);
	mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
			(getmaxx(mainWindow) - 38) / 2,
			"Select [0-%d] or navigate to choice...",
			(int)menuListing.size() - 1);
	wrefresh(mainWindow);

	notification = newwin(3, 3 * COLS / 5, 9 * LINES / 10, COLS / 5);
	keypad(notification, true);
	bookDisplayWindow = derwin(mainWindow, menuListing.size(),
			getmaxx(mainWindow) / 2 - 1, 3, getmaxx(mainWindow) / 2);
	box(bookDisplayWindow, 0, 0);
	wrefresh(bookDisplayWindow);

	userInputField = new_field(1, getmaxx(notification) - 1, 0, 1, 0, 0);
	set_field_back(userInputField, A_UNDERLINE);
	field_opts_off(userInputField, O_AUTOSKIP);

	FIELD *fields[2] { userInputField, nullptr };
	userInputForm = new_form(fields);
	set_form_win(userInputForm, notification);
	set_form_sub(userInputForm,
			derwin(notification, getmaxy(notification),
					getmaxx(notification), 0, 0));

	bookBuffer = *bookList[bookIndex];

	bookWritten = 1;

	//Main program loop
	while (continueMenu) {
		if (stateProvider) {
			delwin(bookDisplayWindow);
			refreshWindowMiddleSplit(mainMenu, mainWindow, notification,
					mainMenuInfo);
			mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
					(getmaxx(mainWindow) - 38) / 2,
					"Select [0-%d] or navigate to choice...",
					(int)menuListing.size() - 1);
			bookDisplayWindow = derwin(mainWindow, menuListing.size(),
					getmaxx(mainWindow) / 2 - 1, 3,
					getmaxx(mainWindow) / 2);
			box(bookDisplayWindow, 0, 0);
			mvwprintw(bookDisplayWindow, 1, 1, atrim(bookBuffer.getTitle(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 2, 1, atrim(bookBuffer.getISBN(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 3, 1, atrim(bookBuffer.getAuthor(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 4, 1, atrim(bookBuffer.getPub(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 5, 1, atrim(bookBuffer.getDateAdded(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 6, 1, "%d", bookBuffer.getQtyOnHand());
			mvwprintw(bookDisplayWindow, 7, 1, "%.2f",
					bookBuffer.getWholesale());
			mvwprintw(bookDisplayWindow, 8, 1, "%.2f", bookBuffer.getRetail());
			wrefresh(bookDisplayWindow);
			mvwprintw(notification, 2, 1, "Currently editing index %d",
					bookIndex);
			set_form_win(userInputForm, notification);
			set_form_sub(userInputForm,
					derwin(notification, getmaxy(notification),
							getmaxx(notification), 0, 0));
			wrefresh(notification);

			stateProvider = 0;
		}

		mvwprintw(notification, 2, 1, "Currently editing index %d",
				bookIndex);
		wrefresh(notification);
		wclear(bookDisplayWindow);
		box(bookDisplayWindow, 0, 0);
		mvwprintw(bookDisplayWindow, 1, 1, "Title            : %s",
				atrim(bookBuffer.getTitle(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 2, 1, "ISBN             : %s",
				atrim(bookBuffer.getISBN(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 3, 1, "Author           : %s",
				atrim(bookBuffer.getAuthor(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 4, 1, "Publisher        : %s",
				atrim(bookBuffer.getPub(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 5, 1, "Date Added       : %s",
				atrim(bookBuffer.getDateAdded(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 6, 1, "QoH              : %d",
				bookBuffer.getQtyOnHand());
		mvwprintw(bookDisplayWindow, 7, 1, "Wholesale Value  : %.2f",
				bookBuffer.getWholesale());
		mvwprintw(bookDisplayWindow, 8, 1, "Retail Value     : %.2f",
				bookBuffer.getRetail());
		wrefresh(bookDisplayWindow);

		input = wgetch(mainWindow);
		inputChar = ((input == '0') ? '9' : input - 1);

		switch (input) {
		case 10:
			choice = item_index(current_item(mainMenu));
			if (choice < (int)menuListing.size() && choice != -1) {
				if (choice < 8) {
					if (choice > 4) {
						set_field_type(userInputField, TYPE_NUMERIC);
					} else {
						set_field_type(userInputField, NULL);
					}
					post_form(userInputForm);
					wrefresh(notification);

					while ((formch = wgetch(notification)) != 10) {
						switch (formch) {
						case KEY_LEFT:
							form_driver(userInputForm, REQ_PREV_CHAR);
							break;
						case KEY_RIGHT:
							form_driver(userInputForm, REQ_NEXT_CHAR);
							break;
						case KEY_BACKSPACE:
							form_driver(userInputForm, REQ_PREV_CHAR);
							form_driver(userInputForm, REQ_DEL_CHAR);
							fieldQueue.pop_back();
							break;
						default:
							if ((formch >= '!' && formch <= '~')
									|| formch == ' ') {
								form_driver(userInputForm, formch);
								fieldQueue.push_back(formch);
							}
							break;
						}
						wrefresh(notification);
					}
					queueSize = fieldQueue.size();
					fieldBuffer = new char[queueSize + 1];
					for (int i = 0; i < queueSize; i++) {
						fieldBuffer[i] = fieldQueue.at(i);
					}
					fieldQueue.clear();
					fieldBuffer[queueSize] = '\0';
					switch (choice) {
					case 0:
						//Get book title
						bookBuffer.setTitle(fieldBuffer);
						//bookBuffer.bookTitle.resize(queueSize);
						break;
					case 1:
						//Get isbn
						bookBuffer.setISBN(fieldBuffer);
						//bookBuffer.isbn.resize(queueSize);
						break;
					case 2:
						//Get author
						bookBuffer.setAuthor(fieldBuffer);
						//bookBuffer.author.resize(queueSize);
						break;
					case 3:
						//Get publisher
						bookBuffer.setPub(fieldBuffer);
						//bookBuffer.publisher.resize(queueSize);
						break;
					case 4:
						//Get date added
						bookBuffer.setDateAdded(fieldBuffer);
						//bookBuffer.dateAdded.resize(queueSize);
						break;
					case 5:
						//Get quantity on hand
						bookBuffer.setQtyOnHand(atoi(fieldBuffer));
						break;
					case 6:
						//Get wholesale value
						bookBuffer.setWholesale(atof(fieldBuffer));
						break;
					case 7:
						//Get retail value
						bookBuffer.setRetail(atof(fieldBuffer));
						break;
					default:

						break;
					}
					unpost_form(userInputForm);
					wrefresh(notification);
					delete[] fieldBuffer;
				}
				if (choice == 8) {
					mvwprintw(notification, 2, 1,
							"Are you sure you want to write to book? [Y/N]");
					exitChar = wgetch(notification);
					if (tolower(exitChar) == 'y') {
						*bookList[bookIndex] = bookBuffer;
						bookWritten = 1;
					}
					wclear(notification);
				} else if (choice == 9) {
					if (bookWritten == 1) {
						bookWritten = 0;
						continueMenu = 0;
					} else {
						mvwprintw(notification, 2, 1,
								"Book not saved. Really leave? [Y/N]");
						exitChar = wgetch(notification);
						if (tolower(exitChar) == 'y')
							continueMenu = 0;
						wclear(notification);
					}
				} else
					bookWritten = 0;

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
				inputArr[0] = inputChar;
				set_current_item(mainMenu, items[atoi(inputArr)]);
				wrefresh(notification);
			} else {
				wclear(notification);
				wprintw(notification, "Invalid Input");
				wrefresh(notification);
			}
			break;
		}
	}
	free_form(userInputForm);
	free_field(userInputField);
	wclear(notification);
	delwin(notification);
	delwin(bookDisplayWindow);
	deleteMenu(mainMenu, items, menuListing.size());
	endWindow(mainWindow);
	return;
}
