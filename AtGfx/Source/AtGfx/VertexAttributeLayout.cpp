#include "AtGfx/VertexAttributeLayout.h"

namespace AtGfx
{

	VertexAttributeLayout::VertexAttributeLayout(std::initializer_list<VertexAttributeElement> elements)
		: m_Elements(elements), m_Stride(0)
	{
		CalculateOffsetAndStride();
	}

	void VertexAttributeLayout::CalculateOffsetAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

}
