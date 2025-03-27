#ifndef LOOKUP_H
#define LOOKUP_H

#ifndef invmenu
#include "invmenu.h"
#endif

#include <string>
using namespace std;

int mainLookUp( BookType * const booklist[20] );
int findString (const std::string toSearch, BookType * const array[], const int size);
int findStringInCart (const std::string toSearch, BookType * const array[], const int size, int cart[]);
string AskKeyword (const int &bookCount );

#endif
