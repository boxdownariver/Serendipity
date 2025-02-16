// This is a stub function
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
using namespace std;


struct bookType {
string bookNames;
string isbn;
};

int findString (string toSearch, bookType array[]);
void showBook (int index, const bookType array []);

int mainLookUp() {
    bookType books [5];
    string toSearch;
    int bookIndex;
    
    books[0].bookNames = "Star Wars";
    books[1].bookNames = "Star Wars Part the First";
    books[2].bookNames = "Star Wars Part the Second";
    books[3].bookNames = "Revenge of the Sith";
    books[4].bookNames = "Star Wars: Verily, A New Hope";
    
    books[0].isbn = "01010101";
    books[1].isbn = "123456789";
    books[2].isbn = "101112131";
    books[3].isbn = "141516171";
    books[4].isbn = "18192021\n";

    cout << ">>> BOOK LOOKUP <<<\n";
    cout << "Search : ";
    getline (cin, toSearch);

    bookIndex = findString (toSearch, books);
    if (bookIndex != -1)
    {
        //show the book details to user
	system("clear");
        showBook (bookIndex, books);
    }
	
	
    return 0;
}

int findString (string toSearch, bookType array[])
{
    int index = 0;
    string tempTitle;
    string searchUpper;
    char choice;

    // make the search string all uppercase
    searchUpper = toSearch;
    transform (searchUpper.begin (), searchUpper.end(), searchUpper.begin (), :: toupper);
    
     while (index < 5)
         {
             // make each array uppercase based on the index
             tempTitle = array[index].bookNames;
             transform (tempTitle.begin (), tempTitle.end(), tempTitle.begin (), :: toupper);

             // Look up for the string name or isbn
             if (tempTitle.find(searchUpper) != string::npos || array[index].isbn.find (toSearch)!= string::npos)
             {
                 cout << "\nRESULT -> : Title - " << array[index].bookNames;

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


void showBook (int index, const bookType array [])
{
	
    cout << "----------------------------------------------------------------------------\n";	
    cout << "* Book Title : ------------------> " << setw(40) << left << array[index].bookNames << "*\n";
    cout << "* ISBN : ------------------------> " << setw(40) << left << array[index].isbn << "*\n";
    cout << "----------------------------------------------------------------------------\n";	
	cout << "\nPress any key to continue..\n";
	cin.ignore();	
}
