#include <SFML/OpenGL.hpp>
#include <WoodletJump.h>

WoodletJump::WoodletJump() {
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void WoodletJump::render() {
    glClear(GL_COLOR_BUFFER_BIT);
}
