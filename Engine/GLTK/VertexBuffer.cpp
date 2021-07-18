#include "VertexBuffer.h"

Engine::gltk::VertexBuffer::VertexBuffer(const void* raw_data, size_t size)
{
	glGenBuffers(1, &this->handler);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, raw_data, GL_STATIC_DRAW);
}

Engine::gltk::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->handler);
}

void Engine::gltk::VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->handler);
}

void Engine::gltk::VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
