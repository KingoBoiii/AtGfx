#pragma once
#include "ShaderDataType.h"

#include <string>
#include <vector>

namespace AtGfx
{

	struct VertexAttributeElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		VertexAttributeElement() = delete;
		VertexAttributeElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3;
				case ShaderDataType::Mat4:    return 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			//AT_CORE_ERROR(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class VertexAttributeLayout
	{
	public:
		VertexAttributeLayout() = delete;
		VertexAttributeLayout(std::initializer_list<VertexAttributeElement> elements);
	public:
		uint32_t GetStride() const
		{
			return m_Stride;
		}
		const std::vector<VertexAttributeElement>& GetElements() const
		{
			return m_Elements;
		}

		std::vector<VertexAttributeElement>::iterator begin()
		{
			return m_Elements.begin();
		}
		std::vector<VertexAttributeElement>::iterator end()
		{
			return m_Elements.end();
		}
		std::vector<VertexAttributeElement>::const_iterator begin() const
		{
			return m_Elements.begin();
		}
		std::vector<VertexAttributeElement>::const_iterator end() const
		{
			return m_Elements.end();
		}
	private:
		void CalculateOffsetAndStride();
	private:
		std::vector<VertexAttributeElement> m_Elements;
		uint32_t m_Stride = 0;
	};

}