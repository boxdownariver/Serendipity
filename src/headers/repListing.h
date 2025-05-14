#ifndef REPLISTING_H
#define REPLISTING_H

#ifndef invmenu
#include "invmenu.h"
#endif
#include "linkedlist.hpp"

// make an array of max size for shopping cart, parallel array with BookType class

int mainRepListing (LinkedListType<BookType *>& books);
void mainSorting (LinkedListType<BookType *>& books);
void mainCalculations (LinkedListType<BookType *>& books, char indicator);
int mainCostListing (LinkedListType<BookType *>& books, string header, double totalPrice);

#endif
