#pragma once
#include "GLObject.h"
#include "VertexBuffer.h"

namespace Engine
{
	namespace gltk
	{
		class VertexArray : public glObject
		{
		public:
			VertexArray();
			~VertexArray();

		public:
			void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);

		public:
			void bind() const override;
			void unbind() const override;
		};
	}
}