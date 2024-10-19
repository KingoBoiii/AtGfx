#pragma once
#include "AtGfx/GraphicsDevice.h"

#include "Bindable.h"

namespace AtGfx
{

	enum class BufferType
	{
		None = -1,
		VertexBuffer = 0x0001,

		IndexBuffer = 0x0002,
		ElementBuffer = IndexBuffer,
	};

	enum class BufferUsage
	{
		None = -1,
		StreamDraw = 0x0001,
		StreamRead = 0x0002,
		StreamCopy = 0x0003,

		StaticDraw = 0x0010,
		StaticRead = 0x0020,
		StaticCopy = 0x0030,

		DynamicDraw = 0x0100,
		DynamicRead = 0x0200,
		DynamicCopy = 0x0300,
	};

	struct BufferSpecification
	{
		BufferType Type;
		uint32_t Size;
		BufferUsage Usage;
		void* InitialData;
		uint32_t DataTypeSize;

		template<typename T>
		static BufferSpecification CreateVertexBufferSpecification(uint32_t size, BufferUsage usage, T* initialData = nullptr)
		{
			return { BufferType::VertexBuffer, size, usage, initialData, sizeof(T) };
		}

		template<typename T>
		static BufferSpecification CreateIndexBufferSpecification(uint32_t size, BufferUsage usage, T* initialData = nullptr)
		{
			return { BufferType::IndexBuffer, size, usage, initialData, sizeof(T) };
		}
	};

	class Buffer : public Internal::Bindable
	{
	public:
		static Buffer* Create(GraphicsDevice* graphicsDevice, const BufferSpecification& specification);
	public:
		~Buffer() = default;

		template<typename T>
		void SetData(uint32_t size, T* data)
		{
			SetData(size, (void*)data);
		}
		virtual void SetData(uint32_t size, void* data) = 0;

		virtual uint32_t GetCount() const = 0;
		bool IsBufferType(BufferType bufferType) const
		{
			return m_Specification.Type == bufferType && m_Type == bufferType;
		}
	protected:
		Buffer(GraphicsDevice* graphicsDevice, const BufferSpecification& specification);
	protected:
		GraphicsDevice* m_GraphicsDevice = nullptr;
		BufferSpecification m_Specification;
		BufferType m_Type = BufferType::None;
	};

}
