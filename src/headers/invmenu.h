#ifndef GLIBCXX_STRING
#include <string>
#endif
#define invmenu

/**
 * BookType\n
 * Definition for books in the database.\n
 * Currently, all invmenu interfaces use this type.\n
 * Not to be confused with CashierBookType
 */
struct BookType {
	std::string bookTitle; ///< Book Title
	std::string isbn;      ///< Book ISBN-13 code
	std::string author;    ///< Book Author
	std::string publisher; ///< Book Publisher
	std::string dateAdded; ///< The date at which the book was added
	int qtyOnHand;         ///< Current book count for this book
	double wholesale;      ///< Wholesale price of book
	double retail;         ///< Retail value of book
};

int main_invmenu(BookType (&books)[20], int &bookCount);
