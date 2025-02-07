everything: mainmenu cashier invmenu reports bookInfo

mainmenu: mainmenu.cpp menuDriver
	g++ -o "mainmenu" mainmenu.cpp menuDriver.o -lncurses -lmenu
cashier: cashier.cpp 
	g++ -o "cashier" cashier.cpp
invmenu: invmenu.cpp menuDriver
	g++ -o "invmenu" invmenu.cpp menuDriver.o -lncurses -lmenu
reports: reports.cpp menuDriver
	g++ -o "reports" reports.cpp menuDriver.o -lncurses -lmenu
bookInfo: bookInfo.cpp
	g++ -o "bookinfo" bookInfo.cpp
menuDriver: menuDipity.cpp
	g++ -c -o "menuDriver.o" menuDipity.cpp 

clean:
	rm cashier mainmenu
