everything: mainmenu cashier

mainmenu: mainmenu.cpp
	g++ -o "mainmenu" mainmenu.cpp -lncurses -lmenu
cashier: cashier.cpp
	g++ -o "cashier" cashier.cpp
clean:
	rm cashier mainmenu
