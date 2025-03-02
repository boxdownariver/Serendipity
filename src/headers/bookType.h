#ifndef BOOKTYPE_H
#define BOOKTYPE_H
#include <string>
using namespace std;

/**
 * bookType class represents a book with various attributes such as title, ISBN, author, etc.
 * 
 * The `bookType` class stores information about a book, including its title, ISBN, author, publisher, 
 * date added, quantity on hand, wholesale price, and retail price. It provides setter and getter functions for 
 * these attributes, along with functions to manage the book count, compare the book by title or ISBN, and print 
 * detailed book information.
 */
class bookType
{
	public:
	void setTitle (string title)	{	bookTitle = title;	}
	void setISBN (string bookisbn )	{	isbn = bookisbn;	}
	void setAuthor (string bookAuthor )	{	author = bookAuthor;	}
	void setPub (string bookPublisher)	{	 publisher = bookPublisher;	}
	void setDateAdded (string date )	{	dateAdded = date;	}
	void setQtyOnHand (int quantity)	{	qtyOnHand= quantity; }
	void setWholesale (double wholesalePrice)	{	wholesale= wholesalePrice;	}
	void setRetail (double retailPrice)	{	retail = retailPrice;	}
	static void incBookCount () {	bookCount++; }
	static void decBookCount () { bookCount --; }

	string getTitle () const	{	return bookTitle;	}
	string getISBN () const	{	return isbn;	}
	string getAuthor () const	{	return author;	}
	string getPub () const	{	return publisher;	}
	string getDateAdded () const	{	return dateAdded;	}
	int getQtyOnHand () const	{	return qtyOnHand;	}
	double getWholesale () const	{	return wholesale;	}
	double getRetail () const	{	return retail;	}
	int getBookCount () const {	return bookCount;	} 
	

	void printBookInfo () const ;

	bool foundKeyword (string toSearch);
	bool equalData (const bookType) const ;

	bookType();
	bookType (string, string, string, string, string, int, double, double);

	~bookType();

	private:
	string bookTitle;      ///< Book Title
	string isbn;           ///< Book ISBN-13 code
	string author;         ///< Book Author
	string publisher;      ///< Book Publisher
	string dateAdded;      ///< The date at which the book was added
	int qtyOnHand;         ///< Current book count for this book 
	double wholesale;      ///< Wholesale price of book
	double retail;         ///< Retail value of book
	static int bookCount;  ///< Holds the current book count in array
};
#endif
