#pragma once
#include "AtomGfx/Buffer.h"

namespace AtomGfx
{

	class OpenGLBuffer : public Buffer
	{
	public:
		OpenGLBuffer(GraphicsDevice* graphicsDevice, const BufferSpecification& specification);
		virtual ~OpenGLBuffer();
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(uint32_t size, void* data) override;

		virtual uint32_t GetCount() const override
		{
			return m_Specification.Size / m_Specification.DataTypeSize;
		}
	private:
		uint32_t m_RendererId;
	};

}
