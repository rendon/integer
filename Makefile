CXX		= g++
LIBS	= -L/usr/local/include -lUnitTest++

first: integer

integer: test.o integer.o
	$(CXX) -o integer test.o integer.o $(LIBS)

test.o: test.cpp integer.o
	$(CXX) -c test.cpp

integer.o: integer.cpp integer.h
	$(CXX) -c integer.cpp


	
