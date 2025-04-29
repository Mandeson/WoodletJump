#include <array>
#include <Util/BufferBuilder.h>
#include <Util/TextureRect.h>

BufferBuilder::BufferBuilder() : vertices_{}, indices_{} {
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
}

BufferBuilder::~BufferBuilder() {
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}

void BufferBuilder::addRectangle(Vector2f pos, Vector2f size, const TextureRect& texture_rect) {
    uploaded_ = false;
    std::array<float, (2 + 2) * 4> vertices = {
        pos.x,          pos.y,          texture_rect.s1, texture_rect.t1,
        pos.x + size.x, pos.y,          texture_rect.s2, texture_rect.t1,
        pos.x + size.x, pos.y + size.y, texture_rect.s2, texture_rect.t2,
        pos.x,          pos.y + size.y, texture_rect.s1, texture_rect.t2
    };
    std::array<unsigned int, 3 * 2> indices = {
        indice_index_, indice_index_ + 1, indice_index_ + 2,
        indice_index_ + 2, indice_index_ + 3, indice_index_
    };
    indice_index_ += 4;
    for (float vertice : vertices)
        vertices_.push_back(vertice);
    for (unsigned int indice : indices)
        indices_.push_back(indice);
}

void BufferBuilder::upload(GLenum usage) {
    if (uploaded_)
        return;
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), &vertices_[0], usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], usage);
    uploaded_ = true;
}

void BufferBuilder::bind(GLuint aPosLocation, GLuint aTexCoordLocation) {
    upload(); // ensure the data has been uploaded
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glVertexAttribPointer(aPosLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
            reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(aPosLocation);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glVertexAttribPointer(aTexCoordLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
            reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(aTexCoordLocation);
}

int BufferBuilder::getElementCount() {
    return indices_.size();
}
