// Saliha Babar                    CS1B                            Serendipity
//
/**************************************************************************//**
 * DISPLAY A CASHIER REPORT
 * ____________________________________________________________________________
 * This cashier.cpp asks for book information to purchase (by title or by name)
 * and it allows user to select more books on the same receipt.
 * Then it calculates the total price for each book type.
 * Finally it will create a nicely formatted cashier report.
 * @author Saliha Babar
 * @file cashier.cpp
 * ____________________________________________________________________________
 * INPUT 
 *    keyword                     : title or isbn of the book to search for
 *    cart                        : array of user shopping cart
 * 
 * OUTPUT
 *    date                        : current date to be printed on receipt
 *    subtotal                    : total before tax
 *		tax_amt                     : amount of tax applied
 *    totalAfterTax               : total after tax (subtotal + tax_amt)
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
char showCashierMenu (int cart[]);
void addBook (BookType *books[], int index, int cart[] );
void removeBook (BookType *books[], int index, int cart[]);
void showCart (BookType *books[], int cart[]);
void FormatReport ( BookType *books[], int cart[], string date);
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
int mainCashier (BookType *books[])
{
		if (BookType::getBookCount() == 0)
			{
			// immediately exit program
			system ("clear");
			cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "║ " << setw (98) << left << "The book list is empty. No books available for cashier registration." << " ║ \n" ;
	   	cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   	cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return 0;
			}


	int cart[20];
	char choice;
	string keyword;
	int indexOfBook;
	bool cartFilled;
	char confirm;
	char repeat;
	string date;
	char exit;

// initialize cart with 0s before entering loop
	for (int i = 0; i < 20 ; i++){
				cart[i] = 0;
			}
	cartFilled = false;


do {
		//	Before entering inner loop, always check if cart is filled
		cartFilled = false;
		for (int i = 0; i < 20; i++) {
    		if (cart[i] > 0) {
      			cartFilled = true;
					break;	}	}

		// show menu
		choice = showCashierMenu (cart);

		switch(choice)
		{
			case '1' :
			keyword = AskKeyword (BookType::getBookCount());
			indexOfBook = findString (keyword, books, BookType::getBookCount());
			if (indexOfBook == -1){
			cout << "Press enter to continue...\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');}
			else	{
				addBook ( books, indexOfBook, cart);
			}
			break;

			case '2' :
			keyword = AskKeyword (BookType::getBookCount());
			indexOfBook = findStringInCart (keyword, books, BookType::getBookCount(), cart);
			if (indexOfBook == -1){
			cout << "Press enter to continue...\n"; 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');}
			else 	{
						removeBook ( books, indexOfBook, cart);
					}
			break;
  
			
			case '3':
			showCart(books, cart);
			cout << "Press any key to continue...\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
			
			case '4':
				system ("Clear");
				showCart (books, cart);
				cout << "Confirm Purchase ? (Y/N)\n";
				cin.get (confirm);
				cin.ignore (100, '\n');

				while (toupper(confirm) != 'N' && toupper(confirm) != 'Y' ){
				cout << confirm << " is invalid choice.. Only enter Y or N.\n";
				cin.get (confirm);
				cin.ignore (100, '\n');}

				if (toupper(confirm) == 'Y')
						{

							date = generateDate ();
							FormatReport (books, cart, date);
							cout << "      ┌──────────────────────────────────────────────────────────────────┐\n";
							cout << "      │                       TRANSACTION COMPLETED !                    │\n";
							cout << "      ├──────────────────────────────────────────────────────────────────┤\n";
							cout << "      │            Would you like to make another transaction? (Y/N)     │\n";
							cout << "      └──────────────────────────────────────────────────────────────────┘\n";
							cout << right << setw(35)<< "→  ";
							cin.get (repeat);
							cin.ignore (100, '\n');

							while (toupper(repeat) != 'N' && toupper(repeat) != 'Y' ){
							cout << right << setw(35)<< "→  ";
							cout << repeat << " is invalid choice.. Only enter Y or N.\n";
							cin.get (repeat);
							cin.ignore (100, '\n');}
									 if (toupper(repeat) == 'Y')
											{	for (int i = 0; i < 20 ; i++){
											cart[i] = 0;
											cartFilled = false;} }
									else
									return 0;
						}
			break;

			case '0':
			if (cartFilled){
			cout << "  ┌─────────────────────────────────────────────────────────────────────────────────────┐\n";
			cout << "  │                Exit the Cashier? (Y/N) Your current cart will be lost.              │\n";
			cout << "  └─────────────────────────────────────────────────────────────────────────────────────┘\n";
			cin.get (exit);
			cin.ignore (100, '\n');

					while (toupper(exit) != 'N' && toupper(exit) != 'Y' ){
					cout << exit << " is invalid choice.. Only enter Y or N.\n";
					cin.get (exit);
					cin.ignore (100, '\n');}
			if (toupper(exit) == 'Y')
			return 0;
			}
			
			else {
				return 0; }
			break;
		};

	}	while (BookType::getBookCount() !=0);

	return 0;
}


/**
* showCashierMenu displays the cashier menu and prompts the user for a choice.
*
* returns a char representing the user choice for the menu.
*/
char showCashierMenu (int cart[])
{
		
		bool cartFilled = false;
		for (int i = 0; i < 20; i++) {
    		if (cart[i] > 0) {
      			cartFilled = true;
					break;	}	}

	char choice;
	system ("clear");
	setColour(96);
	cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
	cout << "                │                 Welcome to Serendipity Cash Register             │\n";
 	cout << "                │                                                                  │\n";
	cout << "                │     (1) -   Add a Book to Your Cart                              │\n";
	if (cartFilled){
	cout << "                │     (2) -   Remove a Book from Your Cart                         │\n";
	cout << "                │     (3) -   View Your Cart                                       │\n";
	cout << "                │     (4) -   CheckOut Your Cart                                   │\n";
	}
	cout << "                ├──────────────────────────────────────────────────────────────────┤\n";	
	cout << "                │     (0) -   Exit the Cashier AND Cancel the Current Transaction  │\n";
	cout << "                └──────────────────────────────────────────────────────────────────┘\n";
	resetColour();

	if (cartFilled == false ){
	cout << "                                    Enter your choice ( 1 or 0 )\n";
	cout << right << setw(50)<< "→  ";
	cin.get (choice);
	cin.ignore (100, '\n');

		while (choice < '0' || choice > '1' )
		{
			cout << choice << " is not a valid option. Please enter a number between 1 and 0.\n";
			cout << right << setw(50)<< "→  ";
			cin.get (choice);
			cin.ignore (100, '\n');
		}
	}

	else
	{
	cout << "                           Enter your choice ( 1 - 5 or 0 to exit )\n";
	cout << right << setw(50)<< "→  ";
	cin.get (choice);
	cin.ignore (100, '\n');

		while (choice < '0' || choice > '4' )
		{
		cout << choice << " is not a valid option. Please enter a number between 1 and 4 (or 0) based on the menu.\n";
		cout << right << setw(50)<< "→  ";
		cin.get (choice);
		cin.ignore (100, '\n');
		}
	}

	return choice;
}


/**
 * generateDate Generates the current date in MM/DD/YYYY format.
 *
 * This function retrieves the system's current date using the `time` library,
 * converts it to local time, and formats it into a string representation.
 * The generated date is returned as a string.
 *
 * returns a string representing the current date in MM/DD/YYYY format.
 */
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

/**
 * purchaseBook allows a user to purchase a book and adds it to their cart.
 *
 * This function displays the selected book's information, checks availability, 
 * and prompts the user to confirm adding it to their cart. If the stock is 
 * insufficient, the function automatically adjusts the purchase quantity to 
 * the maximum available stock. The user's cart is then updated accordingly.
 *
 * first parameter is books Array of `BookType` objects containing book information.
 * second parameter is index of the book being purchased in the `books` array.
 * third array is cart Array representing the user's cart, tracking quantities of books added.
 */
void addBook (BookType *books[], int index, int cart[])
{
	// show the book info to user to confirm purchase
	char decision;
	int numToPurchase;
	int numAvailable;

	numAvailable = books[index]->getQtyOnHand() - cart[index];
	system ("clear");
	//mainbookInfo(books, index);
	books[index]->printBookInfo();

	setColour (97);
	cout << "                           ┌────────────────────────────────────────┐\n";
	cout << "                                 Stock available : " << books[index]->getQtyOnHand() << endl;
	cout << "                                 In Your Cart    : " << cart[index] << endl;
	cout << "                           └────────────────────────────────────────┘\n";

	if ( books[index]->getQtyOnHand() == 0 && cart[index] == 0 )
			{	setColour (33);
				cout << setw(70) << right << "Sorry, we are out of stock for this book.\n";
				resetColour();
				cout << "Press enter to continue...\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				return;
			}

	if (numAvailable == 0 && books[index]->getQtyOnHand() == cart[index] )
			{	setColour (33);
				cout << "          Can't add more of this book. Your cart has the maximum quantity of this book. \n";
				resetColour();
				cout << "Press enter to continue...\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				return;
			}

	
	setColour (33);
	cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
	cout << "                │       Would you like to add this book to your cart? (Y/N)        │\n";
	cout << "                └──────────────────────────────────────────────────────────────────┘\n";
	resetColour();
	cout << right << setw(50)<< "→  ";
	cin.get (decision);
	cin.ignore (100, '\n');
	
	while (toupper(decision) != 'N' && toupper(decision) != 'Y' )
			{
				cout << decision << " is invalid choice.. Only enter Y or N.\n";
				cout << right << setw(50)<< "→  ";
				cin.get (decision);
				cin.ignore (100, '\n');
			}
	if (toupper(decision) == 'Y')
	{
		setColour (93);
		cout << setw (40) << right << "You can add up to " << numAvailable << " book(s). Please enter quantity below.\n";
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

			if (numToPurchase > numAvailable )
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
			cout << setw (30) << left << "Press enter to continue...\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cart[index] += numToPurchase;
	}

	return;
}

/**
 * removeBook allows user to remove a book from their cart
 *
 * This function displays the selected book's information, checks if the book is currently in cart,
 * and prompts the user to confirm delete it from their cart.
 *
 * first parameter is books Array of `BookType` objects containing book information.
 * second parameter is index of the book being deleted in the `books` array.
 * third array is cart Array representing the user's cart, tracking quantities of books deleted
 */
void removeBook (BookType *books[], int index, int cart[])
{
	char decision;
	int numToDelete;
	int numAvailable = cart[index];
	system ("clear");
	//mainbookInfo(books, index);
	books[index]->printBookInfo();
	cout << "                           ┌────────────────────────────────────────┐\n";
	cout << "                                 Stock available : " << books[index]->getQtyOnHand() << endl;
	cout << "                                 In Your Cart    : " << cart[index] << endl;
	cout << "                           └────────────────────────────────────────┘\n";
	setColour (33);
	cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
	cout << "                │     Would you like to remove this book from your cart (Y/N)      │\n";
	cout << "                └──────────────────────────────────────────────────────────────────┘\n";
	resetColour();
	cout << right << setw(50)<< "→  ";
	cin.get (decision);
	cin.ignore (100, '\n');
	
	while (toupper(decision) != 'N' && toupper(decision) != 'Y' )
			{
				cout << decision << " is invalid choice.. Only enter Y or N.\n";
				cout << right << setw(50)<< "→  ";
				cin.get (decision);
				cin.ignore (100, '\n');
			}


	if (toupper(decision) == 'Y')
	{
		setColour (93);
		cout << setw (40) << right << "You can delete up to " << numAvailable << " book(s). Please enter quantity below.\n";
		resetColour();
		cout << right << setw(50)<< "→  ";
		cin >> numToDelete;
		cin.ignore();
			while (numToDelete < 0 || numToDelete > numAvailable)
			{
				cout << setw(50) << right << "Invalid quantity entered. Only enter quantity within 0 - " << numAvailable << endl;
				cout << right << setw(50)<< "→  ";
				cin >> numToDelete;
				cin.ignore();
			}
			
			if (numToDelete > 0){
			setColour(32);
			cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
			cout << "                │        " << setw (3) << right << numToDelete << " books removed from your cart successfully!            │\n";
			cout << "                └──────────────────────────────────────────────────────────────────┘\n";
			resetColour();
			}
			else		{
			setColour(32);
			cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
			cout << "                │         Quantity of the book remains the same in your cart       │\n";
			cout << "                └──────────────────────────────────────────────────────────────────┘\n";
			resetColour();}
			
			cout << setw (30) << left << "Press enter to continue...\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cart[index] -= numToDelete;

			
	}

return;
}

/**
 * showCart Displays the contents of the shopping cart.
 *
 * This function iterates through the `cart` array and prints a formatted table 
 * displaying the books that have been added to the cart along with their 
 * quantities. It also calculates and displays the total cost before tax.
 *
 * first paramter is books Array of `BookType` objects containing book information.
 * second paramater is cart Array representing the user's cart, tracking quantities of books added.
 */
void showCart (BookType *books[], int cart[])
{	setColour (96);
	bool cartFilled;
	double totalBeforeTax = 0;
	double tax_amt;
	double tax_pct = 0.06;
	int bookAddedCount = 1;
	string tempTitle;

	for (int i = 0; i < 20; i++)
	 {
        if (cart[i] > 0) 
		  {
				cartFilled = true;
				break;
        }
    }
	
	if (cartFilled == false)
	{
	cout << "                ┌──────────────────────────────────────────────────────────────────┐\n";
	cout << "                │        Cart is currently empty, Add book to view the cart.       │\n";
	cout << "                └──────────────────────────────────────────────────────────────────┘\n";
	resetColour();
	cout << "Press any key to continue..\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;

	}
	cout << fixed << setprecision(2);
	system ("clear");
	cout << "┌─────────────────────────────────────────────────────────────────────────┐\n";
	cout << "│  SERENDIPITY BOOK SELLERS                            YOUR SHOPPING CART │\n";
	cout << "│                                                                         │\n";
	cout << "│ No. Title                                                           Qty │\n";
	cout << "├─────────────────────────────────────────────────────────────────────────┤\n";
    
	for (int i = 0; i < 20; i++)
	{
		if (cart[i] > 0)
			{
				cout << "│ " << setw (2) << right << bookAddedCount << ". ";
				// For placement of the title
				if (books[i]->getTitle().length() <= 60 )
					{
						cout << setw (62) << left << books[i]->getTitle();
					}
					else
					{
						tempTitle = books[i]->getTitle().substr(0, 59);
						cout << setw (58) << left << tempTitle << "...";
					}
				cout << setw (4) << right << cart[i] << "  │\n";
				totalBeforeTax += books[i]->getRetail() * cart[i];
				bookAddedCount++;
			}
	}
		tax_amt = tax_pct * totalBeforeTax;
	
		cout << "│                                                                         │\n";
		cout << "│                                                                         │\n";
		cout << "│   " << setw (58) << right << "Total Before Tax  : " << " $ " << right << setw (8) << totalBeforeTax << " │ \n";
		cout << "│   " << setw (58) << right << "Amount of Tax     : " << " $ " << right << setw (8) << tax_amt << " │ \n";
		cout << "├─────────────────────────────────────────────────────────────────────────┤\n";
		cout << "│   " << setw (58) << right << "Grand Total       : " << " $ " << right << setw (8) << totalBeforeTax + tax_amt << " │ \n";
		cout << "└─────────────────────────────────────────────────────────────────────────┘\n";
		resetColour();
}

/**
 * FormatReport Generates and displays a formatted sales receipt for the purchased books.
 *
 * This function calculates the subtotal, tax amount, and total price of the books 
 * purchased. It then prints a receipt-like output that includes book details, 
 * purchase quantities, prices, and the final total. Additionally, it updates 
 * the available stock by deducting the purchased quantities from inventory.
 *
 * first parameter is books Array of `BookType` objects containing book details.
 * second parameter cart Array representing the user's shopping cart with quantities of books purchased.
 * third parameter is a date as a string to be displayed on the receipt.
 */
void FormatReport ( BookType *books[], int cart[], string date)
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
				books[i]->setQtyOnHand(books[i]->getQtyOnHand() - cart[i]);
				subtotal += books[i]->getRetail() * cart[i];
			}
	}
	tax_amt = TAX_PCT * subtotal;
	totalAfterTax = subtotal + tax_amt;

	// For fixed precision ( show 2 decimal point )
	setColour (96);   // Receipt generally using cyan colour
	cout << fixed << setprecision(2);
	system ("clear");
	cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
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
			cout << "║" << setw(3) << right << cart[i] << "  " << setw (14) << left << books[i]->getISBN();
	
			// placement of the book title
			if (books[i]->getTitle().length() <= 34 )
			{
				cout << setw (36) << left << books[i]->getTitle();
			}
			else
			{
				tempTitle = books[i]->getTitle().substr(0, 33);
				cout << setw (32) << left << tempTitle << "...";
			}

			cout << setw (3) << right << "$" << setw (7) << right << books[i]->getRetail() << setw (5) << right << "$" << setw(7) << right << books[i]->getRetail() * cart[i] << " ║\n";
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
