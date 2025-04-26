CXX = g++
CFLAGS = -g3

all: library
library: library.o
	$(CXX) -shared -o bin/liblibrary.so build/library.o
library.o: src/library.cpp
	$(CXX) $(CFLAGS) -c -fpic -o build/library.o src/library.cpp
clean:
	rm build/*.o
