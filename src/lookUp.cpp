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

/**
 * mainLookUp manages the process of searching for a book in the database.
 * 
 * Parameters:
 * - booklist: An array of `BookType` objects representing the book database.
 * - bookCount: A reference to the integer representing the number of books in the database.
 * 
 * Returns:
 * - This function does not return any value. It is used for searching and displaying book details.
 */

int mainLookUp( const BookType booklist[]) {
	string toSearch;
	char choice;
	int bookIndex;


// immediately let user exit if the book count is 0.
if (BookType::getBookCount() == 0)
	{
		system ("clear");
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
		cout << "║ " << setw (98) << left << "The book list is empty, no books available for search.. " << " ║ \n" ;
	   cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Wait for user input before continuing

		return 0;
	}


	do {
		
	// Prompt user for a search term, ensuring bookCount is valid
	toSearch = AskKeyword ( BookType::getBookCount() );
				
			// Search for the book in the list
    			bookIndex = findString (toSearch, booklist, BookType::getBookCount() );
			if (bookIndex != -1)
    				{
        				//show the book details to user
					system("clear");
					// Pass the array to show the bookInfo
        				//mainbookInfo ( booklist, bookIndex );       
					booklist[bookIndex].printBookInfo();
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
	while (toupper(choice) != 'N' && BookType::getBookCount() != 0);

	
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
             // Search foundKeyword function
             if (array[index].foundKeyword(toSearch) == true )
             {
					cout << "║ [" << setw (2) << right << bookFoundCount <<"]" << setw (100) << right << " ║ \n";
        			cout << "║ ";
					setColour(32); // Yellow text  
					cout << "RESULT -> : Title - " << setw (78) << left << array[index].getTitle();
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
	cout << "' found." ;
	resetColour ();
	cout << " ║ \n";

	 cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 

    return -1;  // Return -1 if no book was found
}


/**
 * findStringInCart searches for a book in the cart based on the title or ISBN.
 * Returns the index of the found book if the user confirms, otherwise continues searching.
 * If no match is found after checking all books, informs the user and returns -1.
 * 
 * Parameters:
 * - toSearch: The search term (book title or ISBN) entered by the user.
 * - array: An array of books to search through.
 * - size: The number of books in the array.
 * - cart: represents a user cart, a parallel array of BookType
 * 
 * Returns:
 * - The index of the first matching book if found and confirmed by the user.
 * - -1 if no matching book is found in the array.
 */
int findStringInCart (const string toSearch, const BookType array[], const int size, int cart[])
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
            if (cart[index] > 0) 
					{
             // Search for title or ISBN match in cart using foundKeyword
             if (array[index].foundKeyword(toSearch) == true)
             {
				cout << "║ [" << setw (2) << right << bookFoundCount <<"]" << setw (100) << right << " ║ \n";
        		cout << "║ ";
				setColour(32); // Yellow text  
				cout << "RESULT -> : Title - " << setw (78) << left << array[index].getTitle();
				resetColour();
				cout << " ║ \n║ ";
				setColour(32); // Yellow text
				cout << "Quantity -> : In your cart - [" << setw (2) << right << cart[index] << setw(66) << left << "]"; 
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
			}
             
             index++;
         }

	// No match found
	cout << "║ ";
	setColour (96);    // set to cyan
	cout << "End of cart reached. NO books with the title or ISBN '";
   	if (searchLength < 35 )
		cout << toSearch;
   	else 
		cout << setw(34) << left << toSearch.substr(0,34) << "...";
	
	if (searchLength <= 44 )
	cout << setw (44-searchLength) << left << "' found in your cart.";
	else
	cout << "' found in your cart." ;
	resetColour ();
	cout << " ║ \n";
	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 

    return -1;  // Return -1 if no book was found
}


/**
 * validateAndAsk prompts the user to search for a book and returns the search term.
 *
 * Parameters:
 * - bookCount: The number of books available in the book list (passed by reference).
 * 
 * Returns:
 * - A string representing the user's search term if the book list is not empty.
 * 
 */
string AskKeyword ( const int &bookCount)
{
	string toSearch;

	system ("clear");
	setColour (33);
	cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"; 
   cout << "║                                       >>> BOOK LOOKUP <<<                                          ║\n";
	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
   cout << "                                      Search → ";
		
   getline (cin, toSearch);
	resetColour();
	return toSearch;
}
