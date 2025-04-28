CXX = g++
CFLAGS = -Wall -DGL_GLEXT_PROTOTYPES -I"./include" -g3
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system -lGL -llibrary
OBJECTS = build/main.o build/Shader.o build/Application.o build/Util/BufferBuilder.o

all: bin/WoodletJump
bin/WoodletJump: $(OBJECTS)
	$(CXX) -L./bin -Wl,-rpath=./ $(LIBRARIES) -o bin/WoodletJump $(OBJECTS)
build/main.o: src/main.cpp include/Application.h
	$(CXX) $(CFLAGS) -c -o build/main.o src/main.cpp
build/Shader.o: src/Shader.cpp include/Shader.h
	$(CXX) $(CFLAGS) -c -o build/Shader.o src/Shader.cpp
build/Application.o: src/Application.cpp include/Application.h
	$(CXX) $(CFLAGS) -c -o build/Application.o src/Application.cpp
build/Util/BufferBuilder.o: src/Util/BufferBuilder.cpp include/Util/BufferBuilder.h
	$(CXX) $(CFLAGS) -c -o build/Util/BufferBuilder.o src/Util/BufferBuilder.cpp
clean:
	rm build/*.o
