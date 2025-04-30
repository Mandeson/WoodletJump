CXX = g++
CFLAGS = -Wall -DGL_GLEXT_PROTOTYPES -I"./include" -g3
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system -lGL -llibrary
OBJECTS = build/main.o build/WoodletJump.o build/Shader.o build/Application.o build/Util/BufferBuilder.o build/Util/TextureRect.o build/Renderer/SpriteRenderer.o build/Sprite.o

all: bin/WoodletJump
bin/WoodletJump: $(OBJECTS)
	$(CXX) -L./bin -Wl,-rpath=./ $(LIBRARIES) -o bin/WoodletJump $(OBJECTS)
build/main.o: src/main.cpp include/Application.h
	$(CXX) $(CFLAGS) -c -o build/main.o src/main.cpp
build/WoodletJump.o: src/WoodletJump.cpp include/WoodletJump.h
	$(CXX) $(CFLAGS) -c -o build/WoodletJump.o src/WoodletJump.cpp
build/Shader.o: src/Shader.cpp include/Shader.h
	$(CXX) $(CFLAGS) -c -o build/Shader.o src/Shader.cpp
build/Application.o: src/Application.cpp include/Application.h
	$(CXX) $(CFLAGS) -c -o build/Application.o src/Application.cpp
build/Util/BufferBuilder.o: src/Util/BufferBuilder.cpp include/Util/BufferBuilder.h
	$(CXX) $(CFLAGS) -c -o build/Util/BufferBuilder.o src/Util/BufferBuilder.cpp
build/Util/TextureRect.o: src/Util/TextureRect.cpp include/Util/TextureRect.h
	$(CXX) $(CFLAGS) -c -o build/Util/TextureRect.o src/Util/TextureRect.cpp
build/Renderer/SpriteRenderer.o: src/Renderer/SpriteRenderer.cpp include/Renderer/SpriteRenderer.h
	$(CXX) $(CFLAGS) -c -o build/Renderer/SpriteRenderer.o src/Renderer/SpriteRenderer.cpp
build/Sprite.o: src/Sprite.cpp include/Sprite.h
	$(CXX) $(CFLAGS) -c -o build/Sprite.o src/Sprite.cpp
clean:
	rm build/*.o
