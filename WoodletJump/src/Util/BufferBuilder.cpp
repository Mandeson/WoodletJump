#include <array>
#include <Util/BufferBuilder.h>
#include <Util/TextureRect.h>
#include <Logger.h>

BufferBuilderBase::BufferBuilderBase() : vertices_{}, indices_{} {
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
}

BufferBuilderBase::~BufferBuilderBase() {
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}

void BufferBuilderBase::clear() {
    indice_index_ = 0;
    vertices_.clear();
    indices_.clear();
}

void BufferBuilderBase::upload(GLenum usage) {
    if (uploaded_)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);

    int size = indices_.size();
    if (size != 0) {
        if (size > allocated_size_) {
            glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float),
                    reinterpret_cast<void *>(&vertices_[0]), usage);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int),
                    reinterpret_cast<void *>(&indices_[0]), usage);
            allocated_size_ = size;
        } else {
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_.size() * sizeof(float),
                    reinterpret_cast<void *>(&vertices_[0]));
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices_.size() * sizeof(unsigned int),
                    reinterpret_cast<void *>(&indices_[0]));
        }
    }
    uploaded_ = true;
}

void BufferBuilderBase::reset(GLuint aPosLocation, GLuint aSecondAttribLocation) {  
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aPosLocation);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aSecondAttribLocation);
}

int BufferBuilderBase::getElementCount() {
    return indices_.size();
}

void TextureBufferBuilder::addRectangle(Vector2f pos, Vector2f size, const TextureRect& texture_rect) {
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

void TextureBufferBuilder::bind(GLuint aPosLocation, GLuint aTexCoordLocation) {
    if (!uploaded_) {
        Logger::log(Logger::MessageType::kWarning, "BufferBuilder: trying to bind a"
            " buffer that is not yet uploaded. Uploading with GL_DYNAMIC_DRAW...");
        upload(GL_DYNAMIC_DRAW); // ensure the data has been uploaded
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glVertexAttribPointer(aPosLocation, 2, GL_FLOAT, GL_FALSE, (2 + 2) * sizeof(float),
            reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(aPosLocation);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glVertexAttribPointer(aTexCoordLocation, 2, GL_FLOAT, GL_FALSE, (2 + 2) * sizeof(float),
            reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(aTexCoordLocation);
}

void TextureBufferBuilder::reset(GLuint aPosLocation, GLuint aTexCoordLocation) {
    BufferBuilderBase::reset(aPosLocation, aTexCoordLocation);
}

void ColorBufferBuilder::addRectangle(Vector2f pos, Vector2f size, Color color) {
    uploaded_ = false;
    ColorF color_f = color.normalize();
    std::array<float, (2 + 4) * 4> vertices = {
        pos.x,          pos.y,          color_f.r, color_f.g, color_f.b, color_f.a,
        pos.x + size.x, pos.y,          color_f.r, color_f.g, color_f.b, color_f.a,
        pos.x + size.x, pos.y + size.y, color_f.r, color_f.g, color_f.b, color_f.a,
        pos.x,          pos.y + size.y, color_f.r, color_f.g, color_f.b, color_f.a
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

void ColorBufferBuilder::addGradient(Vector2f pos, Vector2f size, Color color_a, Color color_b) {
    uploaded_ = false;
    ColorF color_a_f = color_a.normalize();
    ColorF color_b_f = color_b.normalize();
    std::array<float, (2 + 4) * 4> vertices = {
        pos.x,          pos.y,          color_a_f.r, color_a_f.g, color_a_f.b, color_a_f.a,
        pos.x + size.x, pos.y,          color_a_f.r, color_a_f.g, color_a_f.b, color_a_f.a,
        pos.x + size.x, pos.y + size.y, color_b_f.r, color_b_f.g, color_b_f.b, color_b_f.a,
        pos.x,          pos.y + size.y, color_b_f.r, color_b_f.g, color_b_f.b, color_b_f.a,
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

void ColorBufferBuilder::bind(GLuint aPosLocation, GLuint aColorLocation) {
    if (!uploaded_) {
        Logger::log(Logger::MessageType::kWarning, "BufferBuilder: trying to bind a"
            " buffer that is not yet uploaded. Uploading with GL_DYNAMIC_DRAW...");
        upload(GL_DYNAMIC_DRAW); // ensure the data has been uploaded
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glVertexAttribPointer(aPosLocation, 2, GL_FLOAT, GL_FALSE, (2 + 4) * sizeof(float),
            reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(aPosLocation);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glVertexAttribPointer(aColorLocation, 4, GL_FLOAT, GL_FALSE, (2 + 4) * sizeof(float),
            reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(aColorLocation);
}

void ColorBufferBuilder::reset(GLuint aPosLocation, GLuint aColorLocation) {
    BufferBuilderBase::reset(aPosLocation, aColorLocation);
}
