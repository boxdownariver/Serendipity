all: serendipity out/bookInfo

serendipity: src/mainmenu.cpp out/cashier.o out/menuDriver.o out/invmenu.o out/reports.o out/lookUp.o out/bookfile.o out/
	g++ --std=c++20 -o "serendipity" src/mainmenu.cpp out/menuDriver.o out/invmenu.o out/lookUp.o out/reports.o out/cashier.o out/bookfile.o -lncurses -lmenu
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
out/lookUp.o: src/lookUp.cpp out/
	g++ -c -o "out/lookUp.o" src/lookUp.cpp
out/bookfile.o: src/bookfile.cpp out/
	g++ -c -o "out/bookfile.o" src/bookfile.cpp
out/:
	mkdir out
clean:
	rm out/*.o
