#pragma once
#include "GLObject.h"

namespace Engine
{
	namespace gltk
	{
		class IndexBuffer : public glObject
		{
		private:
			unsigned int count;
		public:
			IndexBuffer(const unsigned int* raw_data, unsigned int count);
			~IndexBuffer();

		public:
			void bind() const override;
			void unbind() const override;
		};
	}
}