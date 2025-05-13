#ifndef EDITBOOK_HPP
#define EDITBOOK_HPP

#ifndef invmenu
#include "invmenu.h"
#endif
#include "bookType.h"
#include "linkedlist.hpp"

void mainEditBook(LinkedListType<BookType *>& books);
void editBook(LinkedListType<BookType *>& books, int bookIndex);
#endif
