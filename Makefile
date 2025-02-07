everything: mainmenu cashier invmenu reports bookInfo

mainmenu: mainmenu.cpp
	g++ -o "mainmenu" mainmenu.cpp -lncurses -lmenu
cashier: cashier.cpp
	g++ -o "cashier" cashier.cpp
invmenu: invmenu.cpp
	g++ -o "invmenu" invmenu.cpp -lncurses -lmenu
reports: reports.cpp
	g++ -o "reports" reports.cpp -lncurses -lmenu
bookInfo: bookInfo.cpp
	g++ -o "bookinfo" bookInfo.cpp
menuDriver: menuDipity.cpp
	g++ -o "menuDriver" menuDipity.cpp -lncurses -lmenu

clean:
	rm cashier mainmenu
