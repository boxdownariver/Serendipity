// Saliha Babar                    CS1B                            Serendipity
//
/**************************************************************************//**
 * DISPLAY A CASHIER REPORT
 * ____________________________________________________________________________
 * This cashier.cpp asks for book information ( date, quantity, isbn, title, and price ),
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
#include "headers/invmenu.h"
#include "headers/bookInfo.h"
#include "headers/lookUp.h"

using namespace std;

void purchaseBook (BookType books[], int index, int cart[] );
void showCart (BookType books[], int cart[]);
void FormatReport ( BookType books[], int cart[], string date);
string generateDate ();

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
int mainCashier (BookType books[]){
	int cart [20];
	string toPurchase;
	int indexToPurchase;
	char choice;
	char confirmPurchase;
	char repeat;
	string date;
	bool hasBooksInCart;


do {
	hasBooksInCart = false;
	toPurchase = validateAndAsk (BookType::getBookCount());
		if (toPurchase != "") {
			for (int i = 0; i < 20 ; i++){
				cart[i]=0;
			}

				do {	
					indexToPurchase = findString (toPurchase, books, BookType::getBookCount() );
					if (indexToPurchase != -1){
						system("clear");
						purchaseBook ( books, indexToPurchase, cart);
						system("clear");
						showCart (books, cart);
					}

					//Check if theres book in cart
					for (int i = 0; i < 20; i++) {
    						if (cart[i] > 0) {
        					hasBooksInCart = true;
        					break;
    						}
					}
					if (hasBooksInCart){
					cout << "Do you want to proceed another book purchase on the same receipt? (Y/N)?\n";
					cin.get (choice);
					cin.ignore (100, '\n');
					while (toupper(choice) != 'N' && toupper(choice) != 'Y') {
						cout << choice << " is invalid choice.. Only enter Y or N. ";
						cin.get (choice);
						cin.ignore(100, '\n');
					}
					if (toupper(choice) == 'Y' ){
					toPurchase = validateAndAsk (BookType::getBookCount()); 
					}
				}
				}	while (toupper (choice) != 'N');

			if (hasBooksInCart){
			system("clear");
			showCart (books, cart);
			cout << "Confirm Purchase and view the receipt ? (Y/N)\n";
			cin.get(confirmPurchase);
			cin.ignore (100,'\n');
			while (toupper(confirmPurchase) != 'N' && toupper(confirmPurchase) != 'Y')
				{
					cout << choice << " is invalid choice.. Only enter Y or N. ";
					cin.get (confirmPurchase);
					cin.ignore(100, '\n');
				}

			if (toupper(confirmPurchase) == 'Y')	
			{	
				date = generateDate();
				system("clear");
				FormatReport (books,cart, date );
			}
			}


			// Showed receipt, therefore ask if they want to repat
			cout << "Do you want to make another transaction ? (Y/N)\n";
			cin.get (repeat);
			cin.ignore (100, '\n');
			while (toupper(repeat) != 'N' && toupper(repeat) != 'Y' ){
					cout << repeat << " is invalid choice.. Only enter Y or N. ";
					cin.get (repeat);
					cin.ignore (100, '\n');
				}
		}
}
while (BookType::getBookCount() != 0 && toupper(repeat) != 'N');

	return 0;		
}

string generateDate ()
{
	time_t t = time(nullptr);  
   tm* tm = localtime(&t); // Convert to local time

    // Format the date as MM/DD/YYYY and store it in a string
    stringstream ss;
    ss << setfill('0') << setw(2) << (tm->tm_mon + 1) << "/"  // Month
       << setw(2) << tm->tm_mday << "/"                       // Day
       << (tm->tm_year + 1900);                               // Year

    // Copy the formatted date to a std::string
    string currentDate = ss.str();  // Now `currentDate` holds the date as a string

    // Print the string (date)
    cout << "Current date: " << currentDate << "\n";

    // You can use currentDate as a string now
    // Example: Copy to another string variable
    string copiedDate = currentDate;

	return copiedDate;

}


void purchaseBook (BookType books[], int index, int cart[])
{
	// show the book info to user to confirm purchase
	char decision;
	int numToPurchase;
	int numAvailable;

	numAvailable = books[index].getQtyOnHand() - cart[index];
	mainbookInfo(books, index);

	setColour (97);
	cout << "                           ┌────────────────────────────────────────┐\n";
	cout << "                                 Stock available : " << books[index].getQtyOnHand() << endl;
	cout << "                                 In Your Cart    : " << cart[index] << endl;
	cout << "                           └────────────────────────────────────────┘\n";

	if (numAvailable == 0)
			{
				cout << setw (15) << left << " " << "Sorry, we are out of stock of this book\n";
				cout << setw (25) << left << "Press enter to continue...\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				return;
			}

	setColour (33);
	cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
	cout << "                │     Would you like to add this book to your cart? (Y/N)          │\n";
	cout << "                └──────────────────────────────────────────────────────────────────┘\n";
	resetColour();
	cout << right << setw(50)<< "→  ";
	cin.get (decision);
	cin.ignore (100, '\n');
	
	while (toupper(decision) != 'N' && toupper(decision) != 'Y' )
			{
				cout << decision << " is invalid choice.. Only enter Y or N. ";
				cout << right << setw(50)<< "→";
				cin.get (decision);
				cin.ignore (100, '\n');
			}
	if (toupper(decision) == 'Y')
	{
		setColour (93);
		cout << setw (40) << right << "You can add up to " << numAvailable << " books. Please enter quantity below.\n";
		resetColour();
		cout << right << setw(50)<< "→  ";
		cin >> numToPurchase;
		cin.ignore();
			while (numToPurchase < 0)
			{
				cout << setw (40) << right <<"Invalid quantity entered..Enter quantity again..\n";
				cout << right << setw(50)<< "→  ";
				cin >> numToPurchase;
				cin.ignore();
			}

			if (numToPurchase > numAvailable)
			{
				setColour (96);
				cout << "    The requested quantity exceeds stock, so we've added the maximum available to your cart..\n";
				resetColour();
				numToPurchase = numAvailable ;
			}
			setColour(32);
			cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
			cout << "                │            " << setw (3) << right << numToPurchase << " books added to your cart successfully!            │\n";
			cout << "                └──────────────────────────────────────────────────────────────────┘\n";
			resetColour();
			cout << "Press enter to continue...\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cart[index] += numToPurchase;
			
	}


	return;
}

void showCart (BookType books[], int cart[])
{	setColour (96);
	char choice;
	bool cartPrinted = false;
	string substring;
	double totalBeforeTax = 0;
	cout << fixed << setprecision(2);
	int bookAddedCount = 1;
	string tempTitle;

	for (int i = 0; i < 20; i++)
	 {
        if (cart[i] > 0 && !cartPrinted) 
			{  // If any positive number found and "cart" not printed yet
            cout << "┌─────────────────────────────────────────────────────────────────────────┐\n";
				cout << "│  SERENDIPITY BOOK SELLERS                            YOUR SHOPPING CART │\n";
				cout << "│                                                                         │\n";
				cout << "│ No. Title                                                           Qty │\n";
				cout << "├─────────────────────────────────────────────────────────────────────────┤\n";
            cartPrinted = true;            // Mark "cart" as printed
            break;                         // Exit the loop after printing "cart"
        }
    }
	
	for (int i = 0; i < 20; i++)
	{
		if (cart[i] > 0)
			{
						cout << "│ " << setw (2) << right << bookAddedCount << ". ";
						// For placement of the title
						if (books[i].getTitle().length() <= 60 )
							{
								cout << setw (62) << left << books[i].getTitle();
							}
							else
							{
								tempTitle = books[i].getTitle().substr(0, 59);
								cout << setw (58) << left << tempTitle << "...";
							}
				cout << setw (4) << right << cart[i] << "  │\n";
				totalBeforeTax += books[i].getRetail() * cart[i];
				bookAddedCount++;
			}
	}
	cartPrinted = false;
	for (int i =0; i < 20; i++)
	{
		if (cart[i] > 0 && !cartPrinted)
		{
			cout << "│                                                                         │\n";
			cout << "│                                                                         │\n";
			cout << "│   " << setw (58) << right << "Total Before Tax  : " << " $ " << right << setw (8) << totalBeforeTax << " │ \n";
			cout << "└─────────────────────────────────────────────────────────────────────────┘\n";
			cartPrinted = true;
			break;
		}
	}
	resetColour();

}

/**
 * FormatReport generates a cashier transaction using 'BookType'. 
 * 
 * It takes all the data stored, and calculates the tax amount
 * tax percentage(assumed to be 6%).
 *
 * Function takes 'CashierBookType' as a constant parameter, and retrieve values 
 * from 'CashierBookType'. It simply formats and prints the cashier receipt.
 * Function doesn't return any values.
 */
void FormatReport ( BookType books[], int cart[], string date)
{
	float subtotal = 0;
	float tax_amt;
	const float TAX_PCT = 0.06;
	float totalAfterTax;
	string tempTitle;
	
	// making calculations adn reduce the quantity on database
	for (int i = 0; i < 20 ; i++)
	{
		if (cart[i] > 0)
			{
				books[i].setQtyOnHand(books[i].getQtyOnHand() - cart[i]);
				subtotal += books[i].getRetail() * cart[i];
			}
	}
	tax_amt = TAX_PCT * subtotal;
	totalAfterTax = subtotal + tax_amt;

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
	cout << "║ Date: " << setw (71) << left << date << "║\n";
	cout << "║                                                                              ║\n";
	cout << "║" << setw(5) << left << "Qty" << setw(14) << left << "ISBN" << setw(38) << left << "Title";
	cout << setw (12) << left << "Price" << setw (9) << left << "Total" << "║\n";
	cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";

for (int i = 0; i < 20 ; i++)
{
	if (cart[i] > 0)
	{
			cout << "║" << setw(3) << right << cart[i] << "  " << setw (14) << left << books[i].getISBN();
	
			// placement of the book title
			if (books[i].getTitle().length() <= 34 )
			{
				cout << setw (36) << left << books[i].getTitle();
			}
			else
			{
				tempTitle = books[i].getTitle().substr(0, 33);
				cout << setw (32) << left << tempTitle << "...";
			}

			cout << setw (3) << right << "$" << setw (7) << right << books[i].getRetail() << setw (5) << right << "$" << setw(7) << right << books[i].getRetail() * cart[i] << " ║\n";
	}
}	
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
	resetColour();
	cout<< setw (77) << left << "Thank you for shopping at Serendipity!";
	setColour (96);    // Back to cyan colour
	cout << "║\n";
	cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
	resetColour();
	return;
}
