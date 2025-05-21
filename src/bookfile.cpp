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
void readFile(LinkedListType<BookType *>& books) {
	BookType * bookBuffer = nullptr;
	std::ifstream file;
	std::string numbers;
	std::string bookTitle, isbn, author, publisher, dateAdded;
	int qtyOnHand;
	double wholesale, retail;

	file.open("booklist.dat");

	file.ignore(65536, '\n');
	while (getline(file, bookTitle)) {
		file.ignore(65536, '\n');
		getline(file, isbn);

		file.ignore(65536, '\n');
		getline(file, author);
		file.ignore(65536, '\n');
		getline(file, publisher);
		file.ignore(65536, '\n');
		getline(file, dateAdded);
		file.ignore(65536, '\n');
		getline(file, numbers);
		if (isdigit(numbers[0]))
		qtyOnHand = stoi(numbers);
		file.ignore(65536, '\n');
		getline(file, numbers);
		if (isdigit(numbers[0]))
		wholesale = stod(numbers);
		file.ignore(65536, '\n');
		getline(file, numbers);
		if (isdigit(numbers[0]))
		retail = stod(numbers);

		bookBuffer = new BookType(bookTitle, isbn, author, publisher,
				dateAdded, qtyOnHand, wholesale, retail);
		books.insert_head(bookBuffer);
		BookType::incBookCount();
		file.ignore(65536, '\n');
		file.ignore(65536, '\n');
	}
	file.close();
	return;
}
