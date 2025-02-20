#ifndef GLIBCXX_STRING
#include <string>
#endif
#define invmenu
struct BookType {
	std::string bookTitle;
	std::string isbn;
	std::string author;
	std::string publisher;
	std::string dateAdded;
	int qtyOnHand;
	double wholesale;
	double retail;
};
int main_invmenu(BookType (&books)[20], int &bookCount);
