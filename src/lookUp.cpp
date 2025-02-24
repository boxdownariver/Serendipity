#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "headers/invmenu.h"
#include "headers/bookInfo.h"
#include "headers/lookUp.h"
using namespace std;



int mainLookUp( const BookType booklist[], int &bookCount ) {
    string toSearch;
    int bookIndex;
    char choice = 'Y';  // Initialized so the loop executes for the first time

	if (bookCount == 0)
	{
		system ("clear");
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
		cout << "║ " << setw (98) << left << "The book list is empty, no books available for search.. " << " ║ \n" ;
	   cout << "║ " << setw (98) << left << "Press any key to continue " << " ║ \n" ;
	   cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	else {
		while (bookCount != 0 && toupper (choice) != 'N' )
	{
		system ("clear");
		cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"; 
    	cout << "║                                     >>> BOOK LOOKUP <<<                                            ║\n";
		cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
    	cout << "                                      Search : ";
    	getline (cin, toSearch);

		// Function to find the string
    	bookIndex = findString (toSearch, booklist, bookCount );

    			if (bookIndex != -1)
    				{
        				//show the book details to user
					system("clear");
						// Pass the array to show the bookInfo
        				mainbookInfo ( booklist, bookIndex );       
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
	 int bookFoundCount = 1;
    string tempTitle;
    string searchUpper;
    char choice;
	 int searchLength = toSearch.length();   // to set the length of the searched word
    // make the search string all uppercase
    searchUpper = toSearch;
    transform (searchUpper.begin (), searchUpper.end(), searchUpper.begin (), :: toupper);
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"; 
    cout << "║                                                                                                    ║\n";
     while (index < size)
         {
             // make each array uppercase based on the index
             tempTitle = array[index].bookTitle; transform (tempTitle.begin (), tempTitle.end(), tempTitle.begin (), :: 
             toupper);

             // Look up for the string name or isbn
             if (tempTitle.find(searchUpper) != string::npos || array[index].isbn.find (toSearch)!= string::npos)
             {
					  cout << "║ [" << setw (2) << right << bookFoundCount <<"]" << setw (100) << right << " ║ \n";
                 cout << "║ RESULT -> : Title - " << setw (78) << left << array[index].bookTitle << " ║\n";
                 cout << "║ " << setw (98) << left << "Is this the book you intended to search for? (Y/N) : " << " ║ " ;
                 cin.get (choice);
	        		  cin.ignore (100, '\n');
					  cout << "║                                                                                                    ║\n";
                 while (toupper(choice) != 'N' && toupper(choice) != 'Y' )
			        {
				        cout << "║ " << choice << setw (97) << " is invalid choice.. Only enter Y or N " << " ║ ";
				        cin.get (choice);
				        cin.ignore (100, '\n');
						  cout << "║                                                                                                    ║\n";
			        }    
                if (toupper (choice) == 'Y' )
                return index;
					bookFoundCount++;

             }
             
             index++;
         }
    cout << "║ End of the book list reached. No books with the title or ISBN '";
	if (searchLength < 25 )
		cout << toSearch;
	else 
		cout << setw(24) << left << toSearch.substr(0,24) << "...";
	
	if (searchLength <= 35 )
	cout << setw (35-searchLength) << left << "' found." << " ║ \n" ;
	else
	cout << setw (0) << left << "' found." << " ║ \n" ;

	 cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"; 

    return -1;
}
