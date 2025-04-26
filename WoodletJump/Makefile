CXX = g++
CFLAGS = -g3
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system -lGL -llibrary

all: WoodletJump
WoodletJump: main.o
	$(CXX) -L./bin -Wl,-rpath=./ $(LIBRARIES) -o bin/WoodletJump build/main.o
main.o: src/main.cpp
	$(CXX) $(CFLAGS) -c -o build/main.o src/main.cpp
clean:
	rm build/*.o
