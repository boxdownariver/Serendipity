#ifndef LOOKUP_H
#define LOOKUP_H

#ifndef invmenu
#include "invmenu.h"
#endif
#include "linkedlist.hpp"

#include <string>
using namespace std;

int mainLookUp( LinkedListType< BookType *>& booklist );
int findString (const std::string toSearch, LinkedListType< BookType *>& array, const int size);
int findStringInCart (const std::string toSearch, LinkedListType< BookType *>& array, const int size, int cart[]);
string AskKeyword (const int &bookCount );

#endif
