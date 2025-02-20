//TJ Dignan                           CS1B                              Serendipity
/**********************************************************************************
 * BOOKINFO
 ********************************************************************************** 
 * This program is a placeholder for the information page on the different books
 * in the serendipity bookstore.
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

int mainbookInfo ( const BookType array[], const int &bookIndex )
{
// Outputs printed book info function
	bookInfoWindow(array, bookIndex);
	return 0;
}

// Function for printing book info
void bookInfoWindow(const BookType array[], const int bookIndex )
{
	cout << left << "-----------------------------------------------------------\n";
	cout <<         "-               Serendipity Booksellers                   -\n";
	cout <<         "-                    Book Information                     -\n";
	cout <<         "-                                                         -\n";
	cout <<         "-    ISBN             : " << array[bookIndex].bookTitle << endl;
	cout <<         "-    Title            : " << array[bookIndex].isbn << endl;                                             
	cout <<         "-    Author           : " << array[bookIndex].author << endl;                                  
	cout <<         "-    Publisher        : " << array[bookIndex].publisher << endl;
	cout <<         "-    Date Added       : " << array[bookIndex].dateAdded << endl;
	cout <<         "-    Quantity-On-Hand : " << array[bookIndex].qtyOnHand << endl;
	cout <<         "-    Wholesale Cost   : " << array[bookIndex].wholesale << endl;
	cout <<         "-    Retail Price     : " << array[bookIndex].retail << endl;
	cout <<         "-                                                         -\n";
	cout <<         "-----------------------------------------------------------\n";
}

