all: serendipity bookInfo

serendipity: mainmenu.cpp cashier.o menuDriver.o invmenu.o reports.o
	g++ --std=c++20 -o "serendipity" mainmenu.cpp menuDriver.o invmenu.o reports.o cashier.o -lncurses -lmenu
cashier.o: cashier.cpp 
	g++ -c -o "cashier.o" cashier.cpp
invmenu.o: invmenu.cpp
	g++ --std=c++20 -c -o "invmenu.o" invmenu.cpp
reports.o: reports.cpp
	g++ --std=c++20 -c -o "reports.o" reports.cpp
bookInfo: bookInfo.cpp
	g++ -o "bookinfo" bookInfo.cpp
menuDriver.o: menuDipity.cpp
	g++ --std=c++20 -c -o "menuDriver.o" menuDipity.cpp 

clean:
	rm cashier mainmenu
