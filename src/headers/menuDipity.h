#ifndef menu_driver_h
#define menu_driver_h

#ifndef string
#include <string>
#endif
#include <vector>

#ifndef menu_lines_struct
#define menu_lines_struct
/**
 * MenuLines\n
 * Contains all the text information required for menu generation.\n
 */
struct MenuLines {
	std::string menuName;								///< Menu Name
	std::vector<std::string> menuLines;					///< Menu Options
	int longestMenuLength;								///< Longest Line Length
	std::string storeName = "Serendipity Booksellers";	///< Name of Store
};
#endif

#ifndef make_menu
#define make_menu
int makeMenu(MenuLines &, std::string);
#endif

#ifndef menu_utils
#define menu_utils
#include <menu.h>
#include <curses.h>
void createMenu(MENU *&mainMenu, WINDOW *mainWindow,
                const MenuLines &mainMenuInfo, ITEM **&items);
void deleteMenu(MENU *&mainMenu, ITEM **&items, size_t menuLineSize);
void startWindow(WINDOW *&mainWindow);
void endWindow(WINDOW *&mainWindow);
void refreshWindow(MENU *&mainMenu, WINDOW *&mainWindow, WINDOW *&notification,
                const MenuLines &mainMenuInfo);
void refreshWindowMiddleSplit(MENU *&mainMenu, WINDOW *&mainWindow, WINDOW *&notification,
                const MenuLines &mainMenuInfo);
void createMenuMiddleSplit(MENU *&mainMenu, WINDOW *mainWindow,
                const MenuLines &mainMenuInfo, ITEM **&items);
//void handleSignal(const int signal);
#endif
#endif
