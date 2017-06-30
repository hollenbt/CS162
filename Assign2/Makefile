CC = g++ -std=c++11
exe = online_library

$(exe)): library.o librarian.o patron.o cart.o validation_library.o driver.o
	$(CC) library.o librarian.o patron.o cart.o validation_library.o driver.o -o $(exe)

library.o: library.cpp
	$(CC) -c library.cpp

librarian.o: librarian.cpp
	$(CC) -c librarian.cpp

patron.o: patron.cpp
	$(CC) -c patron.cpp

cart.o: cart.cpp
	$(CC) -c cart.cpp

validation_library.o: validation_library.cpp
	$(CC) -c validation_library.cpp

driver.o: driver.cpp
	$(CC) -c driver.cpp

clean:
	rm -f *.o $(exe)
