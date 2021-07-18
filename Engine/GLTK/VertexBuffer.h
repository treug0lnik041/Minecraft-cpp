#pragma once
#include <vector>

#include "GLObject.h"

namespace Engine
{
	namespace gltk
	{
		class VertexBuffer : public glObject
		{
		public:
			VertexBuffer(const void* raw_data, size_t size);
			~VertexBuffer();

		public:
			void bind() const override;
			void unbind() const override;
		};


		struct VertexBufferElements
		{
			unsigned int type;
			unsigned int count;
			bool normalized;

			inline const size_t typeSize() const
			{
				switch (type)
				{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
				}
			}
		};

		class VertexBufferLayout
		{
		private:
			std::vector<VertexBufferElements> m_elements;
			unsigned int m_stride;

		public:
			VertexBufferLayout() : m_stride(0)
			{

			}

		public:
			template<typename _Ty> void push(unsigned int count);

		public:
			inline const std::vector<VertexBufferElements> elements() const
			{
				return this->m_elements;
			}

			inline const unsigned int stride() const
			{
				return this->m_stride;
			}
		};
	}
}

template<typename _Ty>
inline void Engine::gltk::VertexBufferLayout::push(unsigned int count)
{
	static_assert(false);
}

template<>
inline void Engine::gltk::VertexBufferLayout::push<float>(unsigned int count)
{
	this->m_elements.push_back(VertexBufferElements(GL_FLOAT, count, false));
	this->m_stride += sizeof(float) * count;
}

template<>
inline void Engine::gltk::VertexBufferLayout::push<unsigned int>(unsigned int count)
{
	this->m_elements.push_back(VertexBufferElements(GL_UNSIGNED_INT, count, false));
	this->m_stride += sizeof(unsigned int) * count;
}

template<>
inline void Engine::gltk::VertexBufferLayout::push<unsigned char>(unsigned int count)
{
	this->m_elements.push_back(VertexBufferElements(GL_UNSIGNED_BYTE, count, true));
	this->m_stride += sizeof(unsigned char) * count;
}