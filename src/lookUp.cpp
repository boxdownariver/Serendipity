
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "headers/invmenu.h"
using namespace std;

int findString (const string toSearch,const BookType array[], const int size);
void showBook (int index, const BookType array []);

int mainLookUp( const BookType booklist[], int &bookCount ) {
    string toSearch;
    int bookIndex;
    char choice = 'Y';  // Initialized so the loop executes for the first time

	if (bookCount == 0)
	{
		system ("clear");
		cout << "The book list is empty, no books available for search.\n";
		cout << "Press any key to continue\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	else {
		while (bookCount != 0 && toupper (choice) != 'N' )
	{
		system ("clear");
		cout << "         >>> BOOK LOOKUP <<<\n";
    	cout << "         Search : ";
    		getline (cin, toSearch);

    		bookIndex = findString (toSearch, booklist, bookCount );
    			if (bookIndex != -1)
    				{
        				//show the book details to user
					system("clear");
        				showBook (bookIndex, booklist);
    				}
		cout << "Do you want to proceed another look up(Y/N)?\n";
		cin.get (choice);
		cin.ignore (100, '\n');
		
		while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
			{
				cout << choice << " is invalid choice.. Only enter Y or N. ";
				cin.get (choice);
				cin.ignore (100, '\n');
			}
	}
	}
	
    return 0;
}

int findString (const string toSearch, const BookType array[], const int size)
{
    int index = 0;
    string tempTitle;
    string searchUpper;
    char choice;

    // make the search string all uppercase
    searchUpper = toSearch;
    transform (searchUpper.begin (), searchUpper.end(), searchUpper.begin (), :: toupper);
    
     while (index < size)
         {
             // make each array uppercase based on the index
             tempTitle = array[index].bookTitle;
             transform (tempTitle.begin (), tempTitle.end(), tempTitle.begin (), :: toupper);

             // Look up for the string name or isbn
             if (tempTitle.find(searchUpper) != string::npos || array[index].isbn.find (toSearch)!= string::npos)
             {
                 cout << "\nRESULT -> : Title - " << array[index].bookTitle;

                 cout << "\nIs this the book you intended to search for? (Y/N) : ";
                 cin.get (choice);
	         cin.ignore (100, '\n');

                 while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
			        {
				        cout << choice << " is invalid choice.. Only enter Y or N\n";
				        cin.get (choice);
				        cin.ignore (100, '\n');
			        }    
                if (toupper (choice) == 'Y' )
                return index;

             }
             
             index++;
         }
    cout << "Reached end of the book list. No book found..\n";
    return -1;
}


void showBook (int index, const BookType array [])
{
	
    cout << "----------------------------------------------------------------------------\n";	
    cout << "* Book Title            : -------> " << setw(40) << left << array[index].bookTitle << "*\n";
    cout << "* ISBN                  : -------> " << setw(40) << left << array[index].isbn << "*\n";
    cout << "* Author                : -------> " << setw(40) << left << array[index].author << "*\n";
    cout << "* Publisher             : -------> " << setw(40) << left << array[index].publisher << "*\n";
    cout << "* Date added            : -------> " << setw(40) << left << array[index].dateAdded << "*\n";
    cout << "* Quantity On Hand      : -------> " << setw(40) << left << array[index].qtyOnHand << "*\n";
    cout << "* Wholesale Price ($)   : -------> " << setw(40) << left << array[index].wholesale << "*\n";
    cout << "* Retail Price ($)      : -------> " << setw(40) << left << array[index].retail << "*\n";
    cout << "----------------------------------------------------------------------------\n";		
}
