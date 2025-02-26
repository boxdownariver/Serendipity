// Saliha Babar                    CS1B                            Serendipity
//
/******************************************************************************
 * LOOKUP BOOK IN DATABASE
 * ____________________________________________________________________________
 * This lookUp.cpp checks the current book count. If `bookCount > 1`, 
 * the user is allowed to search for a book using any keyword from the title 
 * or ISBN. The program then displays book information based on the search query.
 * @author Saliha Babar
 * @file lookUp.cpp
 * ____________________________________________________________________________
 * INPUT 
 *   toSearch     : A keyword used to search for a book by title or ISBN.
 * 
 * OUTPUT
 *   Displays the book details if found.
 * ***************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "headers/invmenu.h"
#include "headers/bookInfo.h"
#include "headers/lookUp.h"
#include "headers/setColour.h"
using namespace std;

int mainLookUp( const BookType booklist[], int &bookCount ) {
	string toSearch;
	char choice;
	int bookIndex;

	do {
		
	// Prompt user for a search term, ensuring bookCount is valid
	toSearch = validateAndAsk ( bookCount );

		// Proceed with search if input is valid
		if (toSearch != "" )
			{
				
			// Search for the book in the list
    			bookIndex = findString (toSearch, booklist, bookCount );
			if (bookIndex != -1)
    				{
        				//show the book details to user
					system("clear");
					// Pass the array to show the bookInfo
        				mainbookInfo ( booklist, bookIndex );       
    				}
				// Prompt user for another lookup attempt
				cout << "Do you want to proceed another look up(Y/N)?\n";
				cin.get (choice);
				cin.ignore (100, '\n');

				while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
					{
						cout << choice << " is invalid choice.. Only enter Y or N.\n";
						cin.get (choice);
						cin.ignore (100, '\n');
					}
			}		
	}
	while (toupper(choice) != 'N' && bookCount!= 0);

	
    return 0;
}


/**
 * findString searches for a book in the array based on the title or ISBN.
 * Returns the index of the found book if the user confirms, otherwise continues searching.
 * If no match is found after checking all books, informs the user and returns -1.
 * 
 * Parameters:
 * - toSearch: The search term (book title or ISBN) entered by the user.
 * - array: An array of books to search through.
 * - size: The number of books in the array.
 * 
 * Returns:
 * - The index of the first matching book if found and confirmed by the user.
 * - -1 if no matching book is found in the array.
 */
int findString (const string toSearch, const BookType array[], const int size)
{
	int index = 0;
	int bookFoundCount = 1;
	string tempTitle;
	string searchUpper;
	char choice;
	int searchLength = toSearch.length();   // Get length of search term
	
    // Convert search string to uppercase
    searchUpper = toSearch;
    transform (searchUpper.begin (), searchUpper.end(), searchUpper.begin (), :: toupper);
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"; 
    cout << "║                                                                                                    ║\n";
	
     while (index < size)
         {
             // Convert book title to uppercase for case-insensitive search
             tempTitle = array[index].bookTitle; transform (tempTitle.begin (), tempTitle.end(), tempTitle.begin (), :: 
             toupper);

             // Search for title or ISBN match
             if (tempTitle.find(searchUpper) != string::npos || array[index].isbn.find (toSearch)!= string::npos)
             {
		cout << "║ [" << setw (2) << right << bookFoundCount <<"]" << setw (100) << right << " ║ \n";
        	cout << "║ ";
		setColour(32); // Yellow text  
		cout << "RESULT -> : Title - " << setw (78) << left << array[index].bookTitle;
		resetColour();

		cout << " ║\n";
                cout << "║ " << setw (98) << left << "Is this the book you intended to search for? (Y/N) : " << " ║ " ;
                cin.get (choice);
	        cin.ignore (100, '\n');
		cout << "║                                                                                                    ║\n";
		     
		// Validate user input
                while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
			{
				cout << "║ " << choice << setw (97) << " is invalid choice.. Only enter Y or N " << " ║ ";
				cin.get (choice);
			        cin.ignore (100, '\n');
 			  	cout << "║                                                                                                    ║\n";
		        }    
		     
                if (toupper (choice) == 'Y' )
                return index;        // Return the index if user confirms
		bookFoundCount++;

             }
             
             index++;
         }

	// No match found
	cout << "║ ";
	setColour (96);    // set to cyan
	cout << "End of the book list reached. NO books with the title or ISBN '";
   	if (searchLength < 25 )
		cout << toSearch;
   	else 
		cout << setw(24) << left << toSearch.substr(0,24) << "...";
	
	if (searchLength <= 35 )
	cout << setw (35-searchLength) << left << "' found.";
	else
	cout << setw (0) << left << "' found." ;
	resetColour ();
	cout << " ║ \n";

	 cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 

    return -1;  // Return -1 if no book was found
}



/**
 * validateAndAsk prompts the user to search for a book and returns the search term.
 * If the book list is empty, it waits for user input before returning an empty string.
 * 
 * Parameters:
 * - bookCount: The number of books available in the book list (passed by reference).
 * 
 * Returns:
 * - A string representing the user's search term if the book list is not empty.
 * - An empty string ("") if the book list is empty.
 */
string validateAndAsk ( const int &bookCount)
{
	string toSearch;
	int bookIndex;

	if (bookCount == 0)
	{
		system ("clear");
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
		cout << "║ " << setw (98) << left << "The book list is empty, no books available for search.. " << " ║ \n" ;
	   	cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Wait for user input before continuing
	}

	else {
		system ("clear");
		setColour (33);
		cout << "There is currently " << bookCount << " books available at Serendipity Booksellers\n";
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"; 
    		cout << "║                                       >>> BOOK LOOKUP <<<                                          ║\n";
		cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
    		cout << "                                      Search : ";
		
    	getline (cin, toSearch);
	resetColour();
	return toSearch;
	}

	return ""; // Return empty string if book count is 0 and user pressed a key
}
