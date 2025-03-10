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
class BookType
{
	public:
	void setTitle (string title)				{	bookTitle = title;			} ///< Sets the book title
	void setISBN (string bookisbn )				{	isbn = bookisbn;			} ///< Sets the book ISBN
	void setAuthor (string bookAuthor )			{	author = bookAuthor;		} ///< Sets the book author
	void setPub (string bookPublisher)			{	 publisher = bookPublisher;	} ///< Sets the book publisher
	void setDateAdded (string date )			{	dateAdded = date;			} ///< Sets the date at which the book was added
	void setQtyOnHand (int quantity)			{	qtyOnHand = quantity; 		} ///< Sets the quantity of books available
	void setWholesale (double wholesalePrice)	{	wholesale = wholesalePrice;	} ///< Sets the wholesale price of book
	void setRetail (double retailPrice)			{	retail = retailPrice;		} ///< Sets the retail value of book
	static void incBookCount () 				{	bookCount++; 				} ///< Increments the count of all book types
	static void decBookCount () 				{ bookCount--; 					} ///< Decrements the count of all book types

	string getTitle () const		{	return bookTitle;	} ///< Gets the book title
	string getISBN () const			{	return isbn;		} ///< Gets the book ISBN
	string getAuthor () const		{	return author;		} ///< Gets the book author
	string getPub () const			{	return publisher;	} ///< Gets the book publisher
	string getDateAdded () const	{	return dateAdded;	} ///< Gets the date at which the book was added
	int getQtyOnHand () const		{	return qtyOnHand;	} ///< Gets the quantity of books available
	double getWholesale () const	{	return wholesale;	} ///< Gets the wholesale price of book
	double getRetail () const		{	return retail;		} ///< Gets the retail value of book
	static int getBookCount () 		{	return bookCount;	} ///< Gets the count of all book types

	void printBookInfo () const ; ///< bookInfo() replacement

	//bool foundKeyword (string toSearch); ///< Searches for substring within book name
	bool equalData (const BookType) const ; ///< Checks whether two books are equivalent

	BookType(); ///< Constructor with no arguments
	BookType (string, string, string, string, string, int, double, double); ///< Constructor with all possible values for book

	~BookType() {} ///< Destructor

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
