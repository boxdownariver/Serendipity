#ifndef CASHIER_H
#define CASHIER_H

#ifndef invmenu
#include "invmenu.h"
#endif
#include "linkedlist.hpp"

// make an array of max size for shopping cart, parallel array with BookType class

int mainCashier (LinkedListType<BookType *>& books);
char showCashierMenu (int cart[]);
void addBook (LinkedListType<BookType *>& books, int index, int cart[] );
void removeBook (LinkedListType<BookType *>& books, int index, int cart[]);
void showCart (LinkedListType<BookType *>& books, int cart[]);
void FormatReport ( LinkedListType<BookType *>& books, int cart[], string date);

#endif
