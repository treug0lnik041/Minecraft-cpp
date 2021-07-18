#include "IndexBuffer.h"

Engine::gltk::IndexBuffer::IndexBuffer(const unsigned int* raw_data, unsigned int count)
{
	glGenBuffers(1, &this->handler);
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), raw_data, GL_STATIC_DRAW);
}

Engine::gltk::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &this->handler);
}

void Engine::gltk::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->handler);
}

void Engine::gltk::IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
