#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include "bookType"

using namespace std;

int bookType::bookCount = 0.0;

bookType::bookType()
{
	bookTitle = "UNSET";
	isbn = "UNSET";
	author = "UNSET";
	publisher = "UNSET";
	dateAdded = "UNSET";
	qtyOnHand = 0;
	wholesale = 0.0;
	retail = 0.0;
}

void bookType :: printBookInfo () const
{
	cout <<         "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
	cout <<         "║                                       Serendipity Booksellers                                      ║\n";
	cout <<         "║                                           Book Information                                         ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "║  ISBN             : " << setw (78) << left << getTitle() << " ║\n";
	cout <<         "║  Title            : " << setw(78) << left << getISBN() << " ║\n";
	cout <<         "║  Author           : " << setw (78) << left << getAuthor() << " ║\n";
	cout <<         "║  Publisher        : " << setw (78) << left << getPublisher() << " ║\n";
	cout <<         "║  Date Added       : " << setw (78) << left << getDate() << " ║\n";
	cout <<         "║  Quantity-On-Hand : " << setw (78) << left << getQuantity() << " ║\n";
	cout <<         "║  Wholesale Cost   : " << setw (78) << left << getWholesale() << " ║\n";
	cout <<         "║  Retail Price     : " << setw(78) << left << getRetail() << " ║\n";
	cout <<         "║                                                                                                    ║\n";
	cout <<         "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
}


bool bookType:: foundKeyword (string toSearch)
{
	string tempTitle;
	string searchUpper;

	// Copy the title and search word
	tempTitle = getTitle;
	searchUpper = toSearch;

	//Transform title and search word to uppercase
	transform(tempTitle.begin(), tempTitle.end(), tempTitle.begin(), ::toupper);
	transform(searchUpper.begin(), searchUpper.end(), searchUpper.begin(), ::toupper);

	// Search for title or isbn match
	return (tempTitle.find(searchUpper) != string::npos || isbn.find(searchUpper) != string::npos);
}
