testbst: testbst.o intbst.o
	g++ testbst.o intbst.o -o testbst
testbst.o: testbst.cpp intbst.h
	g++ -c testbst.cpp
intbst.o: intbst.cpp intbst.h
	g++ -c intbst.cpp
clean:		
	rm -f testbst testbst.o intbst.o