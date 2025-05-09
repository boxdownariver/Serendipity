//Micah Krosby						CS1A					Ch. P. #
/**************************************************************************
 *
 *_________________________________________________________________________
 *
 *	FORMULAE-
 *_________________________________________________________________________
 *	INPUTS-
 *
 *	OUTPUTS-
 *
 *************************************************************************/

#include <iostream>
#include "headers/linkedlist.hpp"
using namespace std;

int main() {
	LinkedListType<int> ints;
	LinkedListIterator myInts = LinkedListIterator(ints);
	ints.insert_end(1);
	ints.insert_end(2);
	ints.insert_head(3);
	ints.insert_head(4);
	ints.delete_end();
	ints[2] = 8;
	for (int i = 0; i < ints.size(); i++) {
		std::cout << ints[i] << std::endl;
	}

	return 0;
}
