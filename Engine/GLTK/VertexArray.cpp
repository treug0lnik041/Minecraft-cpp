#include "VertexArray.h"

Engine::gltk::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->handler);
}

Engine::gltk::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->handler);
}

void Engine::gltk::VertexArray::addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	this->bind();
	vbo.bind();
	const auto& elements = layout.elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride(), (const void*)offset);

		offset += element.count * element.typeSize();
	}
}

void Engine::gltk::VertexArray::bind() const
{
	glBindVertexArray(this->handler);
}

void Engine::gltk::VertexArray::unbind() const
{
	glBindVertexArray(0);
}
