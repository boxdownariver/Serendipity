//TJ Dignan                           CS1B                              Serendipity
/**********************************************************************************
 * BOOKINFO
 ********************************************************************************** 
 * This program is a placeholder for the information page on the different books
 * in the serendipity bookstore.
 * @author TJ Dignan
 * @file bookInfo.cpp
 **********************************************************************************
 * OUTPUTS
 **********************************************************************************
 * bookInfoWindow - Displays the window with the book information formatted
 *********************************************************************************/

#include <iostream>
#include <iomanip>  //To keep it clean
#include "headers/bookInfo.h"

using namespace std;
// Funk prototype
void bookInfoWindow(const BookType array[], const int bookIndex );


/**
 * mainbookInfo serves as a wrapper function that calls `bookInfoWindow` to display detailed information 
 * about a specific book from the database.
 * 
 * This function takes in the following parameters:
 * - array: A constant reference to an array of `BookType` objects representing the book database.
 * - bookIndex: The index of the specific book within the array that the function will display.
 * 
 * The function does not return any usable value. It uses `bookInfoWindow` to output the details of the selected book.
 */
int mainbookInfo ( const BookType array[], const int &bookIndex )
{
	bookInfoWindow(array, bookIndex);
	return 0;
}


/**
 * bookInfoWindow is responsible for printing detailed information about a specific book.
 * 
 * This function takes in the following parameters:
 * - array: A constant reference to an array of `BookType` objects representing the book database.
 * - bookIndex: The index of the book whose information is to be displayed.
 * 
 * The function does not return any value. It is used to display the book's information in a user-friendly format.
 */
void bookInfoWindow(const BookType array[], const int bookIndex )
{
	cout << left << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
	cout <<         "║                                       Serendipity Booksellers                                      ║\n";
	cout <<         "║                                           Book Information                                         ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "║  ISBN             : " << setw (78) << left << array[bookIndex].getTitle() << " ║\n";
	cout <<         "║  Title            : " << setw(78) << left << array[bookIndex].getISBN() << " ║\n";
	cout <<         "║  Author           : " << setw (78) << left << array[bookIndex].getAuthor() << " ║\n";
	cout <<         "║  Publisher        : " << setw (78) << left << array[bookIndex].getPub() << " ║\n";
	cout <<         "║  Date Added       : " << setw (78) << left << array[bookIndex].getDateAdded() << " ║\n";
	cout <<         "║  Quantity-On-Hand : " << setw (78) << left << array[bookIndex].getQtyOnHand() << " ║\n";
	cout <<         "║  Wholesale Cost   : " << setw (78) << left << array[bookIndex].getWholesale() << " ║\n";
	cout <<         "║  Retail Price     : " << setw(78) << left << array[bookIndex].getRetail() << " ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
}

