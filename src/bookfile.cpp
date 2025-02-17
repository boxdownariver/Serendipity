#include "headers/invmenu.h"
#include <fstream>

void readFile(BookType books[20], int &bookNumber) {
	BookType bookBuffer;
	std::ifstream file;

	file.open("booklist.dat");

	while (bookNumber < 20 && getline(file, books[bookNumber].bookTitle)) {
		file >> books[bookNumber].isbn;
		file >> books[bookNumber].author;
		file >> books[bookNumber].publisher;
		file >> books[bookNumber].dateAdded;
		file >> books[bookNumber].qtyOnHand;
		file >> books[bookNumber].wholesale;
		file >> books[bookNumber].retail;
		//books[bookNumber] = bookBuffer;
		bookNumber++;
	}
	file.close();
	return;
}
