everything: mainmenu cashier invmenu reports bookInfo

mainmenu: mainmenu.cpp menuDriver invmenu reports
	g++ -o "mainmenu" mainmenu.cpp menuDriver.o invmenu.o reports.o -lncurses -lmenu
cashier: cashier.cpp 
	g++ -o "cashier" cashier.cpp
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
