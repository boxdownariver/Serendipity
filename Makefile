everything: mainmenu bookInfo

mainmenu: mainmenu.cpp cashier menuDriver invmenu reports
	g++ -o "mainmenu" mainmenu.cpp menuDriver.o invmenu.o reports.o cashier.o -lncurses -lmenu
cashier: cashier.cpp 
	g++ -c -o "cashier.o" cashier.cpp
invmenu: invmenu.cpp
	g++ -c -o "invmenu.o" invmenu.cpp
reports: reports.cpp
	g++ -c -o "reports.o" reports.cpp
bookInfo: bookInfo.cpp
	g++ -o "bookinfo" bookInfo.cpp
menuDriver: menuDipity.cpp
	g++ -c -o "menuDriver.o" menuDipity.cpp 

clean:
	rm cashier mainmenu
