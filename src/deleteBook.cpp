#include <iostream>
#include <string>
#include <iomanip>
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

using namespace std;

void mainDelete (BookType books[], int &bookCount)
{
	string toDelete;
	char choice;
	int indexToDelete;

	do {
	 cout << "         >>>>>>>>>>   DELETE BOOK   <<<<<<<<<<\n";
    toDelete = validateAndAsk ( bookCount );
		// Proceed with finding string only if the book count is > 1
		if (toDelete != "invalid" )
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
							cout << "Do you want to proceed another deletion(Y/N)?\n";
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

void discardBook (BookType books[], int index, int &bookCount )
{
	char decision;

	mainbookInfo(books, index);
	cout << "Are you sure you want to delete this book? (Y/N)\n";
	cin.get (decision);
	cin.ignore (100, '\n');

		while (toupper(decision) != 'N' && toupper(decision) != 'Y' )
			{
				cout << decision << " is invalid choice.. Only enter Y or N. ";
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
				cout << "SUCCESSFULLY DELETED A BOOK\n";

		}

}
