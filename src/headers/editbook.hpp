#ifndef EDITBOOK_HPP
#define EDITBOOK_HPP

#ifndef invmenu
#include "invmenu.h"
#endif
#include "bookType.h"

void mainEditBook(BookType *books[20]);
void editBook(BookType *books[20], int bookIndex);
#endif
