// BRANCH OF CASHIER.CPP
// Saliha Babar                    CS1A                            Serendipity
//
/**************************************************************************//**
 * DISPLAY A CASHIER REPORT
 * ____________________________________________________________________________
 * This cpp asks for book information ( date, quantity, isbn, title, and price ),
 * then it calculates the total price for each book type.
 * Finally it will create a nicely formatted cashier report.
 * @author Saliha Babar
 * @file cashier.cpp
 * ____________________________________________________________________________
 * INPUT 
 *    date                      : date the books are purchased
 *    quantity                  : quantity of books purchased
 *    isbn                      : book isbn
 *    title                     : title of the book
 *    price                     : price of a book
 * 
 * OUTPUT
 *  formatted cashier report
 * ***************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>     // To format in decimal places;
#include <cstring>     // To get the length
#include <cstdlib>     // To clear the screen
#include <cctype>      // To check for user choice effectively
#include <limits>      // To handle garbage input well
#include "headers/setColour.h"
using namespace std;

/**
 * CashierBookType\n
 * Currently, only cashier interfaces use this type.\n
 * Not to be confused with BookType
 */
struct CashierBookType {
	string date;    ///< Date to display on receipt
	int quantity;   ///< Quantity of book purchased
	string isbn;    ///< Book ISBN (10-13 digit code)
	string title;   ///< Book Title
	float price;    ///< Price of a book 
	float total;    ///< Total price of single type
};

void askData (CashierBookType &books);
void FormatReport (const CashierBookType &books);

/**
 * mainCashier handles the process of printing a receipt for a 
 * cashier transaction
 * This function manages the main cashier operations, including:
 * 1- Clearing the screen.
 * 2- Prompting the cashier for transaction data.
 * 3- Generating and formatting the receipt report.
 * 4- Asking if the cashier wants to proceed with another transaction
 * 
 * The function does not take any parameters and does not return any values.
 */
int mainCashier (){

	CashierBookType bookOne;
	char choice;

	do {

	// Clear the screen and set the colour
	system("clear");
	setColour (96);
		
	// Pass to a function to get the data.
	askData ( bookOne);
		
	// Clear the screen
	system("clear");
		
	// Pass to a function to show the formatted report
	FormatReport (bookOne); 

	cout << "\033[0m"; // Back to default colour
	cout << "Do you want to proceed another transaction(Y/N)?\n";
	cin.get (choice);
	cin.ignore (100, '\n');

		while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
			{
				cout << choice << " is invalid choice.. Only enter Y or N\n";
				cin.get (choice);
				cin.ignore (100, '\n');
			}
		
	}
	while (toupper (choice) != 'N');
	
	cout << "\033[0m"; // Back to default colour
	
	return 0;
}

/**
 * askData takes the input and stores it in 'CashierBookType' struct
 *
 * This function prompts user for the following data
 * 1- Date of book purchased
 * 2- Quantity of book
 * 3- Book isbn
 * 4- Book title
 * 5- Book price
 *
 * Then it calculates the total price based on quantity and price of each book
 * 
 * Function takes 'CashierBookType' as a parameter, and stores values in
 *  it and doesn't return any values
 */
void askData (CashierBookType &books)
{
	cout << setw (20) << left << "\nDate (MM/DD/YYYY)" << " : ";
	getline (cin, books.date);

	cout << setw (20) << left << "\nQuantity" << " : ";
	cin >> books.quantity;
	cin.ignore();
	
	cout << setw (20) << left << "\nISBN (10 - 13 digits)" << " : ";
	getline (cin, books.isbn);

	cout << setw (20) << left << "\nTitle" << " : ";
	getline (cin, books.title);

	cout << setw(20) << left << "\nPrice ($)" << " : ";
	cin >> books.price;
	cin.ignore();
		
	// Calculate the total.
	books.total = books.price * books.quantity;

	// Show the below txt in Yellow
	setColour (93);
	
	cout << "Information added, press enter to view the cashier receipt\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	
	
	return;
}


/**
 * FormatReport geenerates a cashier transaction using 'CashierBookType' 
 * 
 * It takes all the data stored, and proceed calculating the tax amount
 * 
 * Function takes 'CashierBookType' as a constant parameter, and retrieve values 
 * from 'CashierBookType'. It simply formats and prints the cashier receipt.
 * Function doesn't return any values
 */
void FormatReport (const CashierBookType &books)
{
	float subtotal;
	float tax_amt;
	const float TAX_PCT = 0.06;
	float totalAfterTax;
	string tempTitle;
	
	// Do the calculations
	subtotal = books.total;
	tax_amt = TAX_PCT * subtotal;
	totalAfterTax = tax_amt + subtotal;

	// For fixed precision ( show 2 decimal point )
	setColour (96);   // Receipt generally using cyan colour
	cout << fixed << setprecision(2);
	
	cout << "╔═════════════════════════════════════════════~════════════════════════════════╗\n";
	cout << "║                                                                              ║\n";
	cout << "║"; 
	// Set cyan colour for shop name
	setColour(97);
	cout << setw (78) << left << "Serendipity Book Sellers"; 
	setColour (96);    // Back cyan colour
	cout << "║\n";
	cout << "║                                                                              ║\n";
	cout << "║ Date: " << setw (71) << left << books.date << "║\n";
	cout << "║                                                                              ║\n";
	cout << "║" << setw(5) << left << "Qty" << setw(14) << left << "ISBN" << setw(38) << left << "Title";
	cout << setw (12) << left << "Price" << setw (9) << left << "Total" << "║\n";
	cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
	cout << "║" << setw(3) << right << books.quantity << "  " << setw (14) << left << books.isbn;
	
	// placement of the book title
	if (books.title.length() <= 34 )
	{
		cout << setw (36) << left << books.title;
	}
	else
	{
		tempTitle = books.title.substr(0, 33);
		cout << setw (32) << left << tempTitle << "...";
	}
	
	cout << setw (3) << right << "$" << setw (7) << right << books.price << setw (5) << right << "$" << setw(7) << right << books.total << " ║\n";
	cout << "║                                                                              ║\n";
	cout << "║                                                                              ║\n";
	cout << setw (58) << left << "║" << "Subtotal    $" << setw (8) << right << subtotal << "  ║\n";
	cout << setw (58) << left << "║" << "Tax         $" << setw (8) << right << tax_amt << "  ║\n";
	cout << setw (58) << left << "║";
	// Set total colour to Yellow
	setColour (93);
	cout << "Total       $" << setw (8) << right << totalAfterTax;
	setColour (96);     // Back to cyan
	cout << setw (3) << right << "  ║\n";
	cout << "║                                                                              ║\n";
	cout << "║ ";
	// Print thank you text in white
	setColour (97);
	cout<< setw (77) << left << "Thank you for shopping at Serendipity!";
	setColour (96);    // Back to cyan colour
	cout << "║\n";
	cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
	
	return;
}
