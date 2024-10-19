#pragma once

#include <cstdint>

namespace AtomGfx
{

	enum class ShaderDataType
	{
		None = -1,
		Float	= 0x0001,
		Float2	= 0x0002,
		Float3	= 0x0003,
		Float4	= 0x0004,

		Int		= 0x0010,
		Int2	= 0x0020,
		Int3	= 0x0030,
		Int4	= 0x0040,
		Bool	= 0x0050,

		Mat3	= 0x0100,
		Mat4	= 0x0200,
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		//AT_CORE_ERROR(false, "Unknown ShaderDataType!");
		return 0;
	}

}
