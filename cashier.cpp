// This is Saliha's working branch
// Checking how pull and push works...
// Checking ..

#include <iostream>
#include <string>
#include <iomanip>

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

int main (){
	bookType bookOne;
	// Pass to a function to get the data.
	askData ( bookOne);

	// Pass to a function to show the formatted report
	FormatReport (bookOne); 

	
	return 0;
}

void askData (bookType &books)
{
	cout << "\nDate (MM/DD/YYYY) : ";
	getline (cin, books.date);

	cout << "\nQuantity : ";
	cin >> books.quantity;
	cin.ignore();
	
	cout << "\nISBN : ";
	getline (cin, books.isbn);

	cout << "\nTitle : ";
	getline (cin, books.title);

	cout << "\nPrice ($) : ";
	cin >> books.price;
	
	// Calculate the total.
	books.total = books.price * books.quantity;
}



void FormatReport (const bookType &books)
{
	float subtotal;
	float tax_amt;
	const float taxPct = 0.06;
	float totalAfterTax;

	subtotal = books.total;
	tax_amt = taxPct * subtotal;
	totalAfterTax = tax_amt + subtotal;
	
	cout << "--------------------------------------------------------------------------------\n";
	cout << "-                                                                              -\n";
	cout << "- Serendipity Book Sellers                                                     -\n";
	cout << "-                                                                              -\n";	
	cout << "Date: " << books.date << endl;
	cout << "-" << setw(5) << left << "Qty" << setw(14) << left << "ISBN" << setw(38) << left << "Title";
	cout << setw (12) << left << "Price" << setw (9) << left << "Total" << "-\n";
	cout << "--------------------------------------------------------------------------------\n"; 

	cout << "-" << setw(3) << right << books.quantity << setw (16) << right << books.isbn << setw (35) << left. books.title;
	cout << setw (4) << right << "$" << setw (7) << right << books.price << setw (5) << right << "$" << setw(8) << right << books.total << "-\n";
	cout << setw (58) << left << "-" << "Subtotal    $" << setw (7) << right << subtotal << setw (2) << right << "-\n";
	cout << setw (58) << left << "-" << "Tax         $" << setw (7) << right << tax_amt << setw (2) << right << "-\n";
	cout << setw (58) << left << "-" << "Total       $" << setw (7) << right << totalAfterTax  << setw (2) << right << "-\n";
	cout << "-                                                                              -\n";
	cout << "- " << setw (77) << left << "Thank you for shopping at Serendipity" << "-\n";

	
}
