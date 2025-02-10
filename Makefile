all: out/serendipity out/bookInfo

out/serendipity: src/mainmenu.cpp out/cashier.o out/menuDriver.o out/invmenu.o out/reports.o out/
	g++ --std=c++20 -o "out/serendipity" src/mainmenu.cpp out/menuDriver.o out/invmenu.o out/reports.o out/cashier.o -lncurses -lmenu
out/cashier.o: src/cashier.cpp out/
	g++ -c -o "out/cashier.o" src/cashier.cpp
out/invmenu.o: src/invmenu.cpp out/
	g++ --std=c++20 -c -o "out/invmenu.o" src/invmenu.cpp
out/reports.o: src/reports.cpp out/
	g++ --std=c++20 -c -o "out/reports.o" src/reports.cpp
out/bookInfo: src/bookInfo.cpp out/
	g++ -o "out/bookinfo" src/bookInfo.cpp
out/menuDriver.o: src/menuDipity.cpp out/
	g++ --std=c++20 -c -o "out/menuDriver.o" src/menuDipity.cpp
out/:
	mkdir out
clean:
	rm out/*.o
