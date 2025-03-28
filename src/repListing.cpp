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
#include "headers/setColour.h"
#include "headers/invmenu.h"
#include "headers/repListing.h"
#include "headers/reports.h"

int mainRepListing (BookType *books[])
{
	cout << "Inside Reports Listing\n";

	cout << "Press Enter to Continue..\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return 0;
}
