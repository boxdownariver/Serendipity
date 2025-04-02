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
void readFile(BookType *books[20]) {
	BookType bookBuffer;
	std::ifstream file;
	std::string numbers;
	std::string bookTitle, isbn, author, publisher, dateAdded;
	int qtyOnHand;
	double wholesale, retail;

	file.open("booklist.dat");

	while (BookType::getBookCount() < 20 && getline(file, bookTitle, ',')) {
		getline(file, isbn, ',');
		getline(file, author, ',');
		getline(file, publisher, ',');
		getline(file, dateAdded, ',');
		getline(file, numbers, ',');
		qtyOnHand = stoi(numbers);
		getline(file, numbers, ',');
		wholesale = stod(numbers);
		getline(file, numbers, ',');
		retail = stod(numbers);
		bookBuffer = BookType(bookTitle, isbn, author, publisher,
				dateAdded, qtyOnHand, wholesale, retail);
		*books[BookType::getBookCount()] = bookBuffer;
		BookType::incBookCount();
	}
	file.close();
	return;
}
