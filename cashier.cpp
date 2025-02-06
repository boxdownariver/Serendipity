// Saliha Babar                    CS1A                            Serendipity
//
/******************************************************************************
 * DISPLAY A CASHIER REPORT
 * ____________________________________________________________________________
 * This cpp asks for book information ( date, quantity, isbn, title, and price ),
 * then it calculates the total price for each book type.
 * Finally it will create a nicely formatted cashier report.
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

using namespace std;

struct bookType {
	string date;
	int quantity;
	string isbn;
	string title;
	float price;
	float total;
};

void askData (bookType &books);
void FormatReport (const bookType &books);
void setColour ( int colourCode );


int main (){

	bookType bookOne;
	setColour (95);
	// Pass to a function to get the data.
	askData ( bookOne);

	// Pass to a function to show the formatted report
	FormatReport (bookOne); 

	return 0;
}

void askData (bookType &books)
{
	cout << setw (20) << left << "\nDate (MM/DD/YYYY)" << " : ";
	getline (cin, books.date);

	cout << setw (20) << left << "\nQuantity" << " : ";
	cin >> books.quantity;
	cin.ignore();
	
	cout << setw (20) << left << "\nISBN " << " : ";
	getline (cin, books.isbn);

	cout << setw (20) << left << "\nTitle" << " : ";
	getline (cin, books.title);

	cout << setw(20) << left << "\nPrice ($)" << " : ";
	cin >> books.price;
	cin.ignore();
		
	// Calculate the total.
	books.total = books.price * books.quantity;
	
	return;
}

void FormatReport (const bookType &books)
{
	// Clear the screen
	system("clear");

	float subtotal;
	float tax_amt;
	const float TAX_PCT = 0.06;
	float totalAfterTax;
	string shortTitle;
	
	// Do the calculations
	subtotal = books.total;
	tax_amt = TAX_PCT * subtotal;
	totalAfterTax = tax_amt + subtotal;

	// For fixed precision ( show 2 decimal point )
	setColour (95);   // Receipt generally using magenta colour
	cout << fixed << setprecision(2);
	
	cout << "+-----------------------------------------------------------------------------+\n";
	cout << char (196) << setw (70) << right << char (196) << endl;
	cout << "|"; 
	// Set cyan colour for shop name
	setColour(36);
	cout << setw (78) << left << "Serendipity Book Sellers"; 
	setColour (95);    // Back magenta colour
	cout << "|\n";
	cout << "|                                                                              |\n";
	cout << "-Date: " << setw (72) << left << books.date << "-\n";
	cout << "|                                                                              |\n";
	cout << "|" << setw(5) << left << "Qty" << setw(14) << left << "ISBN" << setw(38) << left << "Title";
	cout << setw (12) << left << "Price" << setw (9) << left << "Total" << "|\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "-" << setw(3) << right << books.quantity << "  " << setw (14) << left << books.isbn;
	
	// placement of the book title
	if (books.title.length() <= 34 )
	{
		cout << setw (36) << left << books.title;
	}
	else
	{
		shortTitle = books.title.substr(0, 33);
		cout << setw (32) << left << shortTitle << "...";
	}
	
	cout << setw (3) << right << "$" << setw (7) << right << books.price << setw (5) << right << "$" << setw(7) << right << books.total << " -\n";
	cout << "|                                                                              |\n";
	cout << "|                                                                              |\n";
	cout << setw (58) << left << "|" << "Subtotal    $" << setw (7) << right << subtotal << setw (2) << right << " -\n";
	cout << setw (58) << left << "|" << "Tax         $" << setw (7) << right << tax_amt << setw (2) << right << " -\n";
	cout << setw (58) << left << "|";
	// Set total colour to Yellow
	setColour (93);
	cout << "Total       $" << setw (7) << right << totalAfterTax;
	setColour (95);     // Back to Magenta
	cout << setw (2) << right << " |\n";
	cout << "|                                                                              |\n";
	cout << "| ";
	// Print thank you text in white
	setColour (97);
	cout<< setw (77) << left << "Thank you for shopping at Serendipity!";
	setColour (95);    // Back to Magenta colour
	cout << "|\n";
	cout << "+------------------------------------------------------------------------------+\n";

	return;
}

void setColour (int colourCode )
{
	cout << "\033[1;" << colourCode << "m";
	return;
}
