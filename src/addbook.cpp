/**********************************************************************//**
 * ADDBOOK MENU IMPLEMENTATION
 * ________________________________________________________________________
 * This program allows the user to add a book to the book list,
 * initializing members as-needed. Offers the ability to write the new book
 * and to exit.
 * @author Micah Krosby
 * @file addbook.cpp
 * ________________________________________________________________________
 *
 *	INPUTS-
 * 		BookType[20] bookList, int currentBookCount -> Current list of book
 * 			objects initialized, and current list size.
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
#ifndef ADDBOOK_H
#include "headers/addbook.h"
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
#ifndef _LIBCPP_IOSTREAM
#include <iostream>
#endif

///Signal handler for window change
void ahandleSignal(const int signal);

volatile sig_atomic_t astateProvider = 0;

/**
 * trim(string, WINDOW *) ->
 * Trims string to appropriate size depending on whitespaces and window
 * size.
 */
const char* trim(const std::string operandString, WINDOW *window) {
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

	maxSize =  (getmaxx(window) - (int)sizeof("Title            : ") - 2);
	//maxSize = 15;
	if (returnString.length()
			> maxSize) {
		returnString.erase(
				returnString.begin() + maxSize - 3,
			returnString.end());
		returnString.append("...");
	}
	returnString.shrink_to_fit();
	return returnString.c_str();
}

/**
 * addBook(BookType[20], int) -> Generates menu interface for adding books.
 * Displays stub view of book members, and allows saving and leaving with
 * confirmation.
 */
void addBook(BookType bookList[20]) {
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
	struct sigaction sa;
	std::string dummyString;
	int input;
	int choice;
	int formch;
	char inputChar;
	char *fieldBuffer;
	bool continueMenu;
	int exitChar;
	int QueueSize;
	bool bookWritten;

	std::vector<std::string> menuListing = { "Enter Book Title",
			"Enter ISBN", "Enter Author", "Enter Publisher",
			"Enter Date Added (mm/dd/yyyy)", "Enter Quantity on Hand",
			"Enter Wholesale Value", "Enter Retail Price",
			"Save Book to Database", "Exit" };

	mainMenuInfo.menuName = "Add a Book";
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength =
			sizeof("Enter Date Added (mm/dd/yyyy)") / sizeof(char);

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

	//Replaced with Constructor
	/*bookBuffer.bookTitle = "UNSET";
	bookBuffer.isbn = "UNSET";
	bookBuffer.author = "UNSET";
	bookBuffer.publisher = "UNSET";
	bookBuffer.dateAdded = "UNSET";
	bookBuffer.qtyOnHand = 0;
	bookBuffer.wholesale = 0;
	bookBuffer.retail = 0;*/
	bookWritten = 1;

	//Main program loop
	while (BookType::getBookCount() < 20 && continueMenu) {
		if (astateProvider) {
			delwin(bookDisplayWindow);
			refreshWindowMiddleSplit(mainMenu, mainWindow, notification,
					mainMenuInfo);
			mvwprintw(mainWindow, getmaxy(mainWindow) - 2,
					(getmaxx(mainWindow) - 38) / 2,
					"Select [0-%d] or navigate to choice...",
					menuListing.size() - 1);
			bookDisplayWindow = derwin(mainWindow, menuListing.size(),
					getmaxx(mainWindow) / 2 - 1, 3,
					getmaxx(mainWindow) / 2);
			box(bookDisplayWindow, 0, 0);
			mvwprintw(bookDisplayWindow, 1, 1,
					trim(bookBuffer.getTitle(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 2, 1,
					trim(bookBuffer.getISBN(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 3, 1,
					trim(bookBuffer.getAuthor(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 4, 1,
					trim(bookBuffer.getPub(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 5, 1,
					trim(bookBuffer.getDateAdded(), bookDisplayWindow));
			mvwprintw(bookDisplayWindow, 6, 1, "%d", bookBuffer.getQtyOnHand());
			mvwprintw(bookDisplayWindow, 7, 1, "%.2f",
					bookBuffer.getWholesale());
			mvwprintw(bookDisplayWindow, 8, 1, "%.2f", bookBuffer.getRetail());
			wrefresh(bookDisplayWindow);
			mvwprintw(notification, 2, 1,
					"%d books used out of 20 available", BookType::getBookCount());
			set_form_win(userInputForm, notification);
			set_form_sub(userInputForm,
					derwin(notification, getmaxy(notification),
							getmaxx(notification), 0, 0));
			wrefresh(notification);

			astateProvider = 0;
		}

		mvwprintw(notification, 2, 1, "%d books used out of 20 available",
				BookType::getBookCount());
		wrefresh(notification);
		wclear(bookDisplayWindow);
		box(bookDisplayWindow, 0, 0);
		mvwprintw(bookDisplayWindow, 1, 1, "Title            : %s",
				trim(bookBuffer.getTitle(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 2, 1, "ISBN             : %s",
				trim(bookBuffer.getISBN(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 3, 1, "Author           : %s",
				trim(bookBuffer.getAuthor(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 4, 1, "Publisher        : %s",
				trim(bookBuffer.getPub(), bookDisplayWindow));
		mvwprintw(bookDisplayWindow, 5, 1, "Date Added       : %s",
				trim(bookBuffer.getDateAdded(), bookDisplayWindow));
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
			if (choice < menuListing.size() && choice != -1) {
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
					QueueSize = fieldQueue.size();
					fieldBuffer = new char[QueueSize + 1];
					for (int i = 0; i < QueueSize; i++) {
						fieldBuffer[i] = fieldQueue.at(i);
					}
					fieldQueue.clear();
					fieldBuffer[QueueSize] = '\0';
					switch (choice) {
					case 0:
						//Get book title
						bookBuffer.setTitle(fieldBuffer);
						//bookBuffer.bookTitle.resize(QueueSize);
						break;
					case 1:
						//Get isbn
						bookBuffer.setISBN(fieldBuffer);
						//bookBuffer.isbn.resize(QueueSize);
						break;
					case 2:
						//Get author
						bookBuffer.setAuthor(fieldBuffer);
						//bookBuffer.author.resize(QueueSize);
						break;
					case 3:
						//Get publisher
						bookBuffer.setPub(fieldBuffer);
						//bookBuffer.publisher.resize(QueueSize);
						break;
					case 4:
						//Get date added
						bookBuffer.setDateAdded(fieldBuffer);
						//bookBuffer.dateAdded.resize(QueueSize);
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
							"Are you sure you want to write to book list? [Y/N]");
					exitChar = wgetch(notification);
					if (tolower(exitChar) == 'y') {
						bookList[BookType::getBookCount()] = bookBuffer;
						BookType::incBookCount();
						bookBuffer.setTitle("UNSET");
						bookBuffer.setISBN("UNSET");
						bookBuffer.setAuthor("UNSET");
						bookBuffer.setPub("UNSET");
						bookBuffer.setDateAdded("UNSET");
						bookBuffer.setQtyOnHand(0);
						bookBuffer.setWholesale(0);
						bookBuffer.setRetail(0);
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
	free_form(userInputForm);
	free_field(userInputField);
	wclear(notification);
	delwin(notification);
	delwin(bookDisplayWindow);
	deleteMenu(mainMenu, items, menuListing.size());
	endWindow(mainWindow);

	if (BookType::getBookCount() >= 20) {
		std::cout << "╔══════════════════════════════════════════╗" <<
		std::endl;
		std::cout << "║Book list full! Cannot add any more books.║" <<
		std::endl << "╚══════════════════════════════════════════╝" <<
	    std::endl << "Press enter to continue..." << std::endl;
		getline(std::cin, dummyString);
	}
	return;
}

void ahandleSignal(const int signal) {
	astateProvider = signal;
	return;
}
