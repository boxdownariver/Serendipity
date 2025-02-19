#include <form.h>
#include "headers/addbook.h"
#include "headers/menuDipity.h"
#ifndef signal
#include <signal.h>
#endif
#include <cstring>

void ahandleSignal(const int signal);

volatile sig_atomic_t astateProvider = 0;

const char * trim(const std::string operandString) {
	std::string returnString;
	bool keepTrimming;
	int iter;

	keepTrimming = 1;
	returnString = operandString;
	for (iter = 0; iter < returnString.length() && returnString.c_str()[iter] == ' '; iter++) {

	}
	returnString.erase(0, iter);

	return returnString.c_str();
}

void addBook(BookType bookList[20], int &currentBookCount) {
	WINDOW *mainWindow;
	WINDOW *bookDisplayWindow;
	WINDOW *notification;
	ITEM **items;
	MENU *mainMenu;
	FIELD *userInputField;
	FORM *userInputForm;
	MenuLines mainMenuInfo;
	BookType bookBuffer;
	struct sigaction sa;
	int input;
	int choice;
	int formch;
	char inputChar;
	char *fieldBuffer;
	bool continueMenu;

	std::vector<std::string> menuListing = { "Set Title", "Set ISBN",
			"Set Author", "Set Publisher", "Set Date Added",
			"Set Quantity on Hand", "Set Wholesale Value",
			"Set Retail Value", "Write to Book List", "Exit" };

	mainMenuInfo.menuName = "Add a Book";
	mainMenuInfo.menuLines = menuListing;
	mainMenuInfo.longestMenuLength = 21;

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
			menuListing.size() - 1);
	wrefresh(mainWindow);

	notification = newwin(1, 3 * COLS / 5, 9 * LINES / 10, COLS / 5);
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

	bookBuffer.bookTitle = "Oof";

	//Main program loop
	while (currentBookCount < 20 && continueMenu) {
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
			wrefresh(bookDisplayWindow);

			astateProvider = 0;
		}

		mvwprintw(bookDisplayWindow, 1, 1, trim(bookBuffer.bookTitle));
		wrefresh(bookDisplayWindow);

		input = wgetch(mainWindow);
		inputChar = ((input == '0') ? '9' : input - 1);

		switch (input) {
		case 10:
			choice = item_index(current_item(mainMenu));
			if (choice < menuListing.size() && choice != -1) {
				if (choice < 8) {
					//Note to self for tomorrow: JUST DO A CHARACTER STREAM WHAT ARE YOU DOING

					//form_driver(userInputForm, REQ_CLR_FIELD);
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
							break;
						default:
							form_driver(userInputForm, formch);
							break;
						}
						//wprintw(notification, "|");
						wrefresh(notification);
					}
					/*form_driver(userInputForm, REQ_NEXT_FIELD);
					form_driver(userInputForm, REQ_PREV_FIELD);
					form_driver(userInputForm, REQ_VALIDATION);
					fieldBuffer = new char[getmaxx(notification)];
					memcpy(fieldBuffer, field_buffer(userInputField, 0),
							getmaxx(notification) - 1);
					switch (choice) {
					case 0:
						//Get book title
						bookBuffer.bookTitle = fieldBuffer;
						break;
					case 1:
						//Get isbn
						bookBuffer.isbn = fieldBuffer;
						break;
					case 2:
						//Get author
						bookBuffer.author = fieldBuffer;
						break;
					case 3:
						//Get publisher
						bookBuffer.publisher = fieldBuffer;
						break;
					case 4:
						//Get date added
						bookBuffer.dateAdded = fieldBuffer;
						break;
					case 5:
						//Get quantity on hand
						bookBuffer.qtyOnHand = atoi(fieldBuffer);
						break;
					case 6:
						//Get wholesale value
						bookBuffer.wholesale = atof(fieldBuffer);
						break;
					case 7:
						//Get retail value
						bookBuffer.retail = atof(fieldBuffer);
						break;
					default:

						break;
					}*/
					unpost_form(userInputForm);
					wrefresh(notification);
					//delete[] fieldBuffer;
				}
				if (choice == 8) {
					bookList[currentBookCount] = bookBuffer;
					currentBookCount++;
				} else if (choice == 9) continueMenu = 0;
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
	return;
}

void ahandleSignal(const int signal) {
	astateProvider = signal;
	return;
}
