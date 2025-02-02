// This is Saliha's working branch
// Checking how pull and push works...
// Checking ..

#include <iostream>
#include <string>

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

int main (){
	bookType bookOne;
	// Pass to a function to get the data.
	askData (&bookOne);

	return 0;
}

void askData (bookType &books)
{
	cout << "\nDate (MM/DD/YYYY) : ";
	getline (cin, books.date);

	cout << "\nQuantity : ";
	cin >> books.quantity;

	cout << "\nISBN : ";
	getline (cin, books.isbn);

	cout << "\nTitle : ";
	getline (cin, books.title);

	cout << "\nPrice  : ";
	cin >> books.price;

	// Calculate the total.
	books.total = books.price * books.quantity;
}
