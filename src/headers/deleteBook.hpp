#ifndef DELETEBOOK_HPP
#define DELETEBOOK_HPP

#ifndef invmenu
#include "invmenu.h"
#endif

#include "bookInfo.h"
#include <string>

void mainDelete (BookType *books []);
void discardBook (BookType *books [], int index);

#endif
