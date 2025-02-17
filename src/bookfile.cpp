#include "headers/bookfile.h"
#include <fstream>

void readFile(BookType books[20], int &bookNumber) {
	BookType bookBuffer;
	std::ifstream file;
	std::string numbers;

	file.open("booklist.dat");

	while (bookNumber < 20 && getline(file, books[bookNumber].bookTitle, ',')) {
		getline(file, bookBuffer.isbn, ',');
		getline(file, bookBuffer.author, ',');
		getline(file, bookBuffer.publisher, ',');
		getline(file, bookBuffer.dateAdded, ',');
		getline(file, numbers, ',');
		bookBuffer.qtyOnHand = stoi(numbers);
		getline(file, numbers, ',');
		bookBuffer.wholesale = stod(numbers);
		getline(file, numbers, ',');
		bookBuffer.retail = stod(numbers);
		books[bookNumber] = bookBuffer;
		bookNumber++;
	}
	file.close();
	return;
}
