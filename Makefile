all: serendipity

serendipity: src/mainmenu.cpp out/cashier.o out/menuDriver.o out/invmenu.o out/reports.o out/lookUp.o out/bookfile.o out/addbook.o out/bookInfo.o out/editbook.o out/setColour.o out/  
	g++ --std=c++20 -o "serendipity" src/mainmenu.cpp out/menuDriver.o out/invmenu.o out/lookUp.o out/reports.o out/cashier.o out/bookfile.o out/addbook.o out/bookInfo.o out/editbook.o out/setColour.o -lncurses -lmenu -lform
out/cashier.o: src/cashier.cpp out/
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
	g++ -c -o "out/lookUp.o" src/lookUp.cpp
out/bookfile.o: src/bookfile.cpp booklist.dat out/
	g++ -c -o "out/bookfile.o" src/bookfile.cpp
out/addbook.o: src/addbook.cpp out/
	g++ -c -o "out/addbook.o" src/addbook.cpp
out/editbook.o: src/editbook.cpp out/
	g++ -c -o "out/editbook.o" src/editbook.cpp
out/setColour.o: src/setColour.cpp out/
	g++ -c -o "out/setColour.o" src/setColour.cpp
out/:
	mkdir out
booklist.dat:
	touch booklist.dat
clean:
	rm out/*.o
