#ifndef DELETEBOOK_HPP
#define DELETEBOOK_HPP

#ifndef invmenu
#include "invmenu.h"
#endif

#include "bookInfo.h"
#include <string>
#include "linkedlist.hpp"

void mainDelete (LinkedListType<BookType *>& books );
void discardBook (LinkedListType<BookType *>& books , int index);

#endif
