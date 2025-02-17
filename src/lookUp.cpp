// This is a stub function
// Requirements (requires a function call to addBook program)
// Book Count while the user is adding book
// Data from addbook function ( bookType array )

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include "headers/invmenu.h"
using namespace std;

/*struct bookType {     // defined struct only for this function to work
string bookNames;
string isbn;
};*/

int findString (string toSearch, BookType array[], const int size);
void showBook (int index, const BookType array []);

int mainLookUp() {
    BookType books [5];
    string toSearch;
    int bookIndex;
    int bookCount = 0;  // This is just an example, book count only depend on addbook function.
    char choice = 'Y';  // Initialized so the loop executes for the first time
	
    books[0].bookTitle = "Star Wars";
    books[1].bookTitle = "Star Wars Part the First";
    books[2].bookTitle = "Star Wars Part the Second";
    books[3].bookTitle = "Revenge of the Sith";
    books[4].bookTitle = "Star Wars: Verily, A New Hope";
    
    books[0].isbn = "01010101";
    books[1].isbn = "123456789";
    books[2].isbn = "101112131";
    books[3].isbn = "141516171";
    books[4].isbn = "18192021";
    bookCount = 5;

	if (bookCount == 0)
	{
		cout << "The book list is empty, no books available for search.\n";
	}

	else {
		while (bookCount != 0 && toupper (choice) != 'N' )
	{
		cout << ">>> BOOK LOOKUP <<<\n";
    		cout << "Search : ";
    		getline (cin, toSearch);

    		bookIndex = findString (toSearch, books, bookCount );
    			if (bookIndex != -1)
    				{
        				//show the book details to user
					system("clear");
        				showBook (bookIndex, books);
    				}
		cout << "Do you want to proceed another look up(Y/N)?\n";
		cin.get (choice);
		cin.ignore (100, '\n');
		
		while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
			{
				cout << choice << " is invalid choice.. Only enter Y or N\n";
				cin.get (choice);
				cin.ignore (100, '\n');
			}
	}
	}
	
    return 0;
}

int findString (string toSearch, BookType array[], const int size)
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
    cout << "* Book Title : ------------------> " << setw(40) << left << array[index].bookTitle << "*\n";
    cout << "* ISBN : ------------------------> " << setw(40) << left << array[index].isbn << "*\n";
    cout << "----------------------------------------------------------------------------\n";		
}
