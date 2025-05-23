all: serendipity

getterminfo: ~/.terminfo/x/xterm-256color

serendipity: src/mainmenu.cpp ./out/cashier.o out/menuDriver.o out/invmenu.o out/reports.o out/lookUp.o out/bookfile.o out/addbook.o out/editbook.o out/deleteBook.o out/setColour.o out/bookType.o out/getwinsize.o out/repListing.o out/  
	g++ --std=c++20 -o "serendipity" src/mainmenu.cpp out/menuDriver.o out/invmenu.o out/lookUp.o out/reports.o out/cashier.o out/bookfile.o out/addbook.o out/editbook.o out/deleteBook.o out/setColour.o out/bookType.o out/getwinsize.o out/repListing.o -L ./ncurses-fix/lib -l:libmenu.a -l:libform.a -l:libncurses.a

./out/cashier.o: src/cashier.cpp out/
	g++ -c -o "out/cashier.o" src/cashier.cpp

out/invmenu.o: src/invmenu.cpp out/
	g++ --std=c++20 -c -o "out/invmenu.o" src/invmenu.cpp

out/reports.o: src/reports.cpp out/
	g++ --std=c++20 -c -o "out/reports.o" src/reports.cpp

out/bookInfo.o: src/bookInfo.cpp out/
	g++ -c -o "out/bookInfo.o" src/bookInfo.cpp

out/menuDriver.o: src/menuDipity.cpp out/
	g++ --std=c++20 -c -o "out/menuDriver.o" src/menuDipity.cpp

out/lookUp.o: src/lookUp.cpp out/
	g++ --std=c++20 -c -o "out/lookUp.o" src/lookUp.cpp

out/bookfile.o: src/bookfile.cpp booklist.dat out/
	g++ -c -o "out/bookfile.o" src/bookfile.cpp

out/addbook.o: src/addbook.cpp out/
	g++ --std=c++20 -c -o "out/addbook.o" src/addbook.cpp

out/editbook.o: src/editbook.cpp out/
	g++ --std=c++20 -c -o "out/editbook.o" src/editbook.cpp

out/deleteBook.o: src/deleteBook.cpp out/
	g++ -c -o "out/deleteBook.o" src/deleteBook.cpp

out/setColour.o: src/setColour.cpp out/
	g++ -c -o "out/setColour.o" src/setColour.cpp

out/bookType.o: src/bookType.cpp out/
	g++ -c -o "out/bookType.o" src/bookType.cpp

out/getwinsize.o: src/getwinsize.cpp out/
	g++ -c -o "out/getwinsize.o" src/getwinsize.cpp

out/repListing.o: src/repListing.cpp out/
	g++ --std=c++20 -c -o "out/repListing.o" src/repListing.cpp

listtest: src/testlinkedlist.cpp src/headers/linkedlist.hpp
	g++ --std=c++20 -o listtest src/testlinkedlist.cpp

out/:
	mkdir out

booklist.dat:
	touch booklist.dat
~/.terminfo/x/xterm-256color:
	cp /usr/share/terminfo/x/xterm-256color ~/.terminfo/x

clean:
	rm out/*.o
