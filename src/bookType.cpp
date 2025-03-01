#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include "bookType"

using namespace std;

int bookType::bookCount = 0;

/**
* Default constructor for bookType class. Initializes member variables with default values.
*/
bookType::bookType()
{
	bookTitle = "UNSET";
	isbn = "UNSET";
	author = "UNSET";
	publisher = "UNSET";
	dateAdded = "UNSET";
	qtyOnHand = 0;
	wholesale = 0.0;
	retail = 0.0;
}

/**
* Constructor with parameters for bookType class. Initializes member variables with given values.
*/
bookType ::bookType (string title, string isbn , string auth, string pub, string date , int qty, double ws, double ret)
{
	setTitle (title);
	setISBN (isbn);
	setAuthor (auth);
	setPub (pub);
	setDateAdded (date);
	setQtyOnHand (qty);
	setWholesale (ws);
	setRetail (ret);
}

/**
 * printBookInfo function prints the information of the book in a formatted manner.
 * 
 * The function prints details like ISBN, title, author, publisher, date added, 
 * quantity on hand, wholesale cost, and retail price in a well-organized table.
 */
void bookType :: printBookInfo () const
{
	cout <<         "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
	cout <<         "║                                       Serendipity Booksellers                                      ║\n";
	cout <<         "║                                           Book Information                                         ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "║  ISBN             : " << setw (78) << left << getISBN() << " ║\n";
	cout <<         "║  Title            : " << setw(78) << left << getTitle() << " ║\n";
	cout <<         "║  Author           : " << setw (78) << left << getAuthor() << " ║\n";
	cout <<         "║  Publisher        : " << setw (78) << left << getPub() << " ║\n";
	cout <<         "║  Date Added       : " << setw (78) << left << getDateAdded() << " ║\n";
	cout <<         "║  Quantity-On-Hand : " << setw (78) << left << getQtyOnHand() << " ║\n";
	cout <<         "║  Wholesale Cost   : " << setw (78) << left << fixed << setprecision(2) << getWholesale() << " ║\n";
	cout <<         "║  Retail Price     : " << setw(78) << left << fixed << setprecision(2) << getRetail() << " ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
}

/**
 * equalData function compares two books to see if they have identical attributes.
 * 
 * Parameter anotherBook is the book object to compare the current object with.
 * @return true if all attributes of both books are identical.
 * @return false if any attribute of the two books differs.
 */
bool bookType::equalData (const bookType anotherBook) const 
{
	if (bookTitle == anotherBook.bookTitle && isbn == anotherBook.isbn && author == anotherBook.author &&
		publisher == anotherBook.publisher && dateAdded == anotherBook.dateAdded && qtyOnHand == anotherBook.qtyOnHand &&
		wholesale == anotherBook.wholesale && retail == anotherBook.retail)
		{
			return true;
		}
	return false;
}

/**
 * foundKeyword function searches for a keyword in the book's title or ISBN.
 * 
 * This function checks if the `toSearch` string is found within the book's title or ISBN. The comparison is
 * case-insensitive, and the search is performed after converting both the title and the search keyword to uppercase.
 * 
 * parameter toSearch is the keyword to search for in the book's title or ISBN.
 * @return true If the search keyword is found in the title or ISBN.
 * @return false If the search keyword is not found in either the title or ISBN.
 */
bool bookType:: foundKeyword (string toSearch)
{
	string tempTitle;
	string searchUpper;

	// Copy the title and search word
	tempTitle = getTitle ();
	searchUpper = toSearch;

	//Transform title and search word to uppercase
	transform(tempTitle.begin(), tempTitle.end(), tempTitle.begin(), ::toupper);
	transform(searchUpper.begin(), searchUpper.end(), searchUpper.begin(), ::toupper);

	// Search for title or isbn match
	return (tempTitle.find(searchUpper) != string::npos || isbn.find(searchUpper) != string::npos);
}
