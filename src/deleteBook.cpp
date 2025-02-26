// Saliha Babar                    CS1B                            Serendipity
//
/******************************************************************************
 * DELETE BOOK IN DATABASE
 * ____________________________________________________________________________
 This deleteBook.cpp file allows the user to search for a book in the 
 * database using a keyword from the title or ISBN. If the book is found, 
 * the program deletes the entire record and updates the book count. 
 * If the book count is greater than 1, the user can continue searching for
 * and deleting more books.
 * @author Saliha Babar
 * @file deleteBook.cpp
 * ____________________________________________________________________________
 * INPUT 
 *   toDelete     : A keyword used to search for a book by title or ISBN, 
 *                  which will then be deleted from the database.
 * 
 * OUTPUT
 *  The book record that matches the search keyword is deleted, and the 
 *  book count is reduced by one.
 * ***************************************************************************/
#include <iomanip>
#include <iostream>
#include <cctype>
#include "headers/invmenu.h"
#ifndef LOOKUP_H
#include "headers/lookUp.h"
#endif
#ifndef BOOKINFO_H
#include "headers/bookInfo.h"
#endif
#ifndef DELETEBOOK_HPP
#include "headers/deleteBook.hpp"
#endif
#ifndef SETCOLOUR_H
#include "headers/setColour.h"
#endif

using namespace std;

/**
 * mainDelete manages the process of deleting a book from the database.
 * 
 * Parameters:
 * - books: An array of `BookType` objects representing the database of books.
 * - bookCount: A reference to the integer representing the number of books in the database, which is updated after each deletion.
 * 
 * Returns:
 * - This function does not return any values. It updates the `bookCount` by decrementing it after a successful deletion.
 */
void mainDelete (BookType books[], int &bookCount)
{
	string toDelete;
	char choice;
	int indexToDelete;

	do {
		// Prompt user for a search term, ensuring bookCount is valid
    		toDelete = validateAndAsk ( bookCount );
		
		// Proceed with finding string only if the book count is > 1
		if (toDelete != "" )
			{
			// Function to find the string
    			indexToDelete = findString (toDelete, books, bookCount );
				
				if (indexToDelete != -1)
    					{
        					// continue with deletion
						system("clear");
						// Pass the array to show the bookInfo
        					discardBook ( books, indexToDelete, bookCount);       
    					}
				
				cout << "Do you want to proceed another deletion (Y/N)?\n";
				cin.get (choice);
				cin.ignore (100, '\n');
				
				while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
					{
						cout << choice << " is invalid choice.. Only enter Y or N. ";
						cin.get (choice);
						cin.ignore (100, '\n');
					}
			}		
	}
	while (toupper(choice) != 'N' && bookCount!= 0);

	
    return;
}


/**
 * discardBook handles the deletion of a book from the database.
 * 
 * Parameters:
 * - books: An array of `BookType` objects representing the book database.
 * - index: The index of the book to be deleted.
 * - bookCount: A reference to the integer representing the number of books in the database, which is updated after the deletion.
 * 
 * Returns:
 * - This function does not return any value. It updates the `bookCount` by decrementing it after a successful deletion.
 */
void discardBook (BookType books[], int index, int &bookCount )
{
	char decision;

	mainbookInfo(books, index);
	setColour (33);
	cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
	cout << "                │  Are you sure you want to delete this book? (Y/N).Think Wisely   │\n";
	cout << "                └──────────────────────────────────────────────────────────────────┘\n";
	resetColour();
	cout << right << setw(50)<< "→  ";
	cin.get (decision);
	cin.ignore (100, '\n');

		while (toupper(decision) != 'N' && toupper(decision) != 'Y' )
			{
				cout << decision << " is invalid choice.. Only enter Y or N. ";
				cout << right << setw(50)<< "→";
				cin.get (decision);
				cin.ignore (100, '\n');
			}

		// Only proceed deleting if user is sure && bookCount is not 0
		if (toupper(decision) == 'Y' && bookCount > 0)
		{
				// Bring the last index data to current index
				books[index].bookTitle = books[bookCount-1].bookTitle;
				books[index].isbn = books[bookCount-1].isbn;
				books[index].author = books[bookCount-1].author;
				books[index].publisher = books[bookCount-1].publisher;
				books[index].dateAdded = books[bookCount-1].dateAdded;
				books[index].qtyOnHand = books[bookCount-1].qtyOnHand;
				books[index].wholesale = books[bookCount-1].wholesale;
				books[index].retail = books[bookCount-1].retail;
				
				// set the last index to default values
				books[bookCount -1].bookTitle = "EMPTY";
				books[bookCount -1].isbn = "EMPTY";
				books[bookCount -1].author = "EMPTY";
				books[bookCount -1].publisher = "EMPTY";
				books[bookCount -1].dateAdded = "EMPTY";
				books[bookCount -1].qtyOnHand = 0 ;
				books[bookCount -1].wholesale = 0 ;
				books[bookCount -1].retail = 0;

				// reduce the book count by one
				bookCount--;
				setColour (96);
				cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
				cout << "                │                     DELETED BOOK SUCCESSFULLY                    │\n";
				cout << "                └──────────────────────────────────────────────────────────────────┘\n";
				resetColour();
		}
}
