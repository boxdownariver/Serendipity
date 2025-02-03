everything: mainmenu cashier invmenu reports

mainmenu: mainmenu.cpp
	g++ -o "mainmenu" mainmenu.cpp -lncurses -lmenu
cashier: cashier.cpp
	g++ -o "cashier" cashier.cpp
invmenu: invmenu.cpp
	g++ -o "invmenu" invmenu.cpp -lncurses -lmenu
reports: reports.cpp
	g++ -o "reports" reports.cpp -lncurses -lmenu

clean:
	rm cashier mainmenu
