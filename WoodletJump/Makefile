CXX = g++
CFLAGS = -Wall -DGL_GLEXT_PROTOTYPES -I"./include" -g3
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system -lGL -llibrary

all: bin/WoodletJump
bin/WoodletJump: build/main.o build/Shader.o
	$(CXX) -L./bin -Wl,-rpath=./ $(LIBRARIES) -o bin/WoodletJump build/main.o build/Shader.o
build/main.o: src/main.cpp
	$(CXX) $(CFLAGS) -c -o build/main.o src/main.cpp
build/Shader.o: src/Shader.cpp
	$(CXX) $(CFLAGS) -c -o build/Shader.o src/Shader.cpp
clean:
	rm build/*.o
