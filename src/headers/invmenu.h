#ifndef string
#include <string>
#endif
#define invmenu
int main_invmenu();
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
