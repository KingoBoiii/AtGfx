#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace AtGfx
{

	namespace Utils
	{

		GLenum GetBufferBindingTargetByType(BufferType bufferType)
		{
			switch (bufferType)
			{
				case AtGfx::BufferType::VertexBuffer:		return GL_ARRAY_BUFFER;
				case AtGfx::BufferType::IndexBuffer:		return GL_ELEMENT_ARRAY_BUFFER;
				case AtGfx::BufferType::None:
				default: break;
			}

			return GL_NONE;
		}

		GLenum GetBufferUsageByUsage(BufferUsage bufferUsage)
		{
			switch (bufferUsage)
			{
				case AtGfx::BufferUsage::StreamDraw:		return GL_STREAM_DRAW;
				case AtGfx::BufferUsage::StreamRead:		return GL_STREAM_READ;
				case AtGfx::BufferUsage::StreamCopy:		return GL_STREAM_COPY;
				case AtGfx::BufferUsage::StaticDraw:		return GL_STATIC_DRAW;
				case AtGfx::BufferUsage::StaticRead:		return GL_STATIC_READ;
				case AtGfx::BufferUsage::StaticCopy:		return GL_STATIC_COPY;
				case AtGfx::BufferUsage::DynamicDraw:		return GL_DYNAMIC_DRAW;
				case AtGfx::BufferUsage::DynamicRead:		return GL_DYNAMIC_READ;
				case AtGfx::BufferUsage::DynamicCopy:		return GL_DYNAMIC_COPY;
				case AtGfx::BufferUsage::None:
				default: break;
			}

			return GL_NONE;
		}

	}

	OpenGLBuffer::OpenGLBuffer(GraphicsDevice* graphicsDevice, const BufferSpecification& specification)
		: Buffer(graphicsDevice, specification), m_RendererId(0)
	{
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(Utils::GetBufferBindingTargetByType(m_Specification.Type), m_RendererId);
		glBufferData(Utils::GetBufferBindingTargetByType(m_Specification.Type), m_Specification.Size, m_Specification.InitialData, Utils::GetBufferUsageByUsage(m_Specification.Usage));
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenGLBuffer::Bind() const
	{
		glBindBuffer(Utils::GetBufferBindingTargetByType(m_Specification.Type), m_RendererId);
	}

	void OpenGLBuffer::Unbind() const
	{
		glBindBuffer(Utils::GetBufferBindingTargetByType(m_Specification.Type), 0);
	}

	void OpenGLBuffer::SetData(uint32_t size, void* data)
	{
		glBindBuffer(Utils::GetBufferBindingTargetByType(m_Specification.Type), m_RendererId);
		glBufferSubData(Utils::GetBufferBindingTargetByType(m_Specification.Type), 0, size, data);
	}

}