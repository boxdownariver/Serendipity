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
	cout << left << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
	cout <<         "║                                       Serendipity Booksellers                                      ║\n";
	cout <<         "║                                           Book Information                                         ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "║  ISBN             : " << setw (78) << left << array[bookIndex].bookTitle << " ║\n";
	cout <<         "║  Title            : " << setw(78) << left << array[bookIndex].isbn << " ║\n";                                              
	cout <<         "║  Author           : " << setw (78) << left << array[bookIndex].author << " ║\n";                                 
	cout <<         "║  Publisher        : " << setw (78) << left << array[bookIndex].publisher << " ║\n";
	cout <<         "║  Date Added       : " << setw (78) << left << array[bookIndex].dateAdded << " ║\n";
	cout <<         "║  Quantity-On-Hand : " << setw (78) << left << array[bookIndex].qtyOnHand << " ║\n";
	cout <<         "║  Wholesale Cost   : " << setw (78) << left << array[bookIndex].wholesale << " ║\n";
	cout <<         "║  Retail Price     : " << setw(78) << left << array[bookIndex].retail << " ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
}

