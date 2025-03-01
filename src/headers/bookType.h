#include <string>

using namespace std;

class bookType
{
	public:
	void setTitle (string title)	{	title = bookTitle;	}
	void setISBN (string bookisbn )	{	bookisbn = isbn;	}
	void setAuthor (string bookAuthor )	{	bookAuthor = author;	}
	void setPublisher (string bookPublisher)	{	bookPublisher = publisher;	}
	void setDate (string date )	{	date = dateAdded	}
	void setQuantity (int quantity)	{	quantity = qtyOnHand; }
	void setWholesale (double wholesalePrice)	{	wholesalePrice = wholesale;	}
	void setRetail (double retailPrice)	{	retaiPrice = retail;	}

	string getTitle () const	{	return bookTitle;	}
	string getISBN () const	{	return isbn;	}
	string getAuthor () const	{	return author;	}
	string getPublisher () const	{	return publisher;	}
	string getDate () const	{	return dateAdded;	}
	int getQuantity () const	{	return qtyOnHand;	}
	double getWholesale () const	{	return wholesale;	}
	double getRetail () const	{	return retail;	}

	static void incrementBookCount () {	bookCount++; }

	static void decrementBookCount () { bookCount --; }

	void printBookInfo () const ;

	bool compareByTitleOrISBN (string toSearch);

	bookType();

	~bookType();

	private:
	string bookTitle;      ///< Book Title
	string isbn;           ///< Book ISBN-13 code
	string author;         ///< Book Author
	string publisher;      ///< Book Publisher
	string dateAdded;      ///< The date at which the book was added
	int qtyOnHand;         ///< Current book count for this book 
	double wholesale;      ///< Wholesale price of book
	double retail;   	     ///< Retail value of book
	static int bookCount;  ///< Holds the current book count in array
};
