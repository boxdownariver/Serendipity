struct MenuLines {
	char menuName[8];
	char menuLines[7][26];
	char storeName[24] = "Serendipity Booksellers";
};

int makeMenu(MenuLines &menu);
void createMenu(MENU *&mainMenu, WINDOW *mainWindow,
		const MenuLines &mainMenuInfo, ITEM **&items);
void deleteMenu(MENU *&mainMenu, ITEM **&items, size_t menuLineSize);
void startWindow(WINDOW *&mainWindow);
void endWindow(WINDOW *&mainWindow);
void handleSignal(const int signal);
void refreshWindow(MENU *&mainMenu, WINDOW *&mainWindow,
		MenuLines mainMenuInfo);


