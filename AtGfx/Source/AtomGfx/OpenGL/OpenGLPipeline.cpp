#include "OpenGLPipeline.h"

#include <glad/glad.h>

namespace AtomGfx
{

	namespace Utils
	{
		GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
		{
			switch (type)
			{
				case ShaderDataType::Float:    return GL_FLOAT;
				case ShaderDataType::Float2:   return GL_FLOAT;
				case ShaderDataType::Float3:   return GL_FLOAT;
				case ShaderDataType::Float4:   return GL_FLOAT;
				case ShaderDataType::Mat3:     return GL_FLOAT;
				case ShaderDataType::Mat4:     return GL_FLOAT;
				case ShaderDataType::Int:      return GL_INT;
				case ShaderDataType::Int2:     return GL_INT;
				case ShaderDataType::Int3:     return GL_INT;
				case ShaderDataType::Int4:     return GL_INT;
				case ShaderDataType::Bool:     return GL_BOOL;
			}

			//AT_CORE_ERROR(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	OpenGLPipeline::OpenGLPipeline(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification)
		: Pipeline(graphicsDevice, specification), m_RendererId(0)
	{
		glGenVertexArrays(1, &m_RendererId);
	}

	OpenGLPipeline::~OpenGLPipeline()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLPipeline::Bind() const
	{
		glBindVertexArray(m_RendererId);

		uint32_t attribIndex = 0;
		const VertexAttributeLayout& layout = m_Specification.VertexAttributeLayout;
		for (const VertexAttributeElement& element : layout.GetElements())
		{
			auto glBaseType = Utils::ShaderDataTypeToOpenGLBaseType(element.Type);
			glEnableVertexAttribArray(attribIndex);
			if (glBaseType == GL_INT || glBaseType == GL_BOOL)
			{
				glVertexAttribIPointer(attribIndex, element.GetComponentCount(), glBaseType, layout.GetStride(), (const void*)(intptr_t)element.Offset);
			}
			else
			{
				GLboolean normalized = element.Normalized ? GL_TRUE : GL_FALSE;
				glVertexAttribPointer(attribIndex, element.GetComponentCount(), glBaseType, normalized, layout.GetStride(), (const void*)(intptr_t)element.Offset);
			}
			attribIndex++;
		}
	}

	void OpenGLPipeline::Unbind() const
	{
		glBindVertexArray(0);
	}

}