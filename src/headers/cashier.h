#ifndef CASHIER_H
#define CASHIER_H

#ifndef invmenu
#include "invmenu.h"
#endif

// make an array of max size for shopping cart, parallel array with BookType class

int mainCashier (BookType *books[]);
char showCashierMenu (int cart[]);
void addBook (BookType *books[], int index, int cart[] );
void removeBook (BookType *books[], int index, int cart[]);
void showCart (BookType *books[], int cart[]);
void FormatReport ( BookType *books[], int cart[], string date);

#endif
