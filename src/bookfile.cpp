/**********************************************************************//**
 * READ FILE INTO BOOK LIST
 * ________________________________________________________________________
 * This program reads a file into the book list. File is "booklist.dat",
 * input is comma-separated.
 * @author Micah Krosby
 * @file bookfile.cpp
 * ________________________________________________________________________
 *
 *	PROCESS-
 * 		BookType[20] books, int bookNumber -> Book array with current size
 * 			to be mutated by the file input program.
 *************************************************************************/
#include "headers/bookfile.h"
#include <fstream>

///readFile(BookType[20], int) -> Stores file entries as members of books.
void readFile(BookType books[20]) {
	BookType bookBuffer;
	std::ifstream file;
	std::string numbers;

	file.open("booklist.dat");

	while (BookType::getBookCount < 20 && getline(file, books[BookType::getBookCount()].bookTitle, ',')) {
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
		books[BookType::getBookCount] = bookBuffer;
		BookType::incBookCount();
	}
	file.close();
	return;
}
