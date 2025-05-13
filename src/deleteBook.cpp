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
#include <limits>
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


void mainDelete (LinkedListType<BookType *>& books)
{

	
	// immidiately let user exit if the bookcount is 0
	if (BookType::getBookCount() == 0)
			{
			// immediately exit program
			system ("clear");
			cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "║ " << setw (98) << left << "The book list is empty, no books available for deletion.. " << " ║ \n" ;
	   	cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
	}
	string toDelete;
	char choice;
	int indexToDelete;

 
	do {
		// Prompt user for a search term, ensuring bookCount is valid
    		toDelete = AskKeyword ( BookType::getBookCount() );
	
		// Function to find the string
    			indexToDelete = findString (toDelete, books, BookType::getBookCount() );
				
				if (indexToDelete != -1)
    					{
        					// continue with deletion
						system("clear");
						// Pass the array to show the bookInfo
        					discardBook ( books, indexToDelete);
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
	while (toupper(choice) != 'N' && BookType::getBookCount() != 0);

	
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
void discardBook (LinkedListType<BookType *>& books, int index) //NEEDS FULL REWORK
{
	char decision;
	int curBookCount;

	//mainbookInfo(books, index);
	books[index]->printBookInfo();
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
		if (toupper(decision) == 'Y' && BookType::getBookCount() > 0)
		{
				// reduce the book count by one
				BookType::decBookCount();
				curBookCount = BookType::getBookCount();

				// Bring the last index data to current index
				// !!! Could make a new constructor for this
				// !!! Also try aggregate set
				books[index]->setTitle(books[curBookCount]->getTitle());
				books[index]->setISBN(books[curBookCount]->getISBN());
				books[index]->setAuthor(books[curBookCount]->getAuthor());
				books[index]->setPub(books[curBookCount]->getPub());
				books[index]->setDateAdded(books[curBookCount]->getDateAdded());
				books[index]->setQtyOnHand(books[curBookCount]->getQtyOnHand());
				books[index]->setWholesale(books[curBookCount]->getWholesale());
				books[index]->setRetail(books[curBookCount]->getRetail());
				
				// set the last index to default values
				/*books[curBookCount].setTitle("EMPTY");
				books[curBookCount].setISBN("EMPTY");
				books[curBookCount].setAuthor("EMPTY");
				books[curBookCount].setPub("EMPTY");
				books[curBookCount].setDateAdded("EMPTY");
				books[curBookCount].setQtyOnHand(0);
				books[curBookCount].setWholesale(0);
				books[curBookCount].setRetail(0);
				*/
				delete books[curBookCount];
				setColour (96);
				cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
				cout << "                │                     DELETED BOOK SUCCESSFULLY                    │\n";
				cout << "                └──────────────────────────────────────────────────────────────────┘\n";
				resetColour();
		}
}
