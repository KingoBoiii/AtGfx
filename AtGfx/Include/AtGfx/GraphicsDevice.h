#pragma once
#include "AtGfx/GraphicsAPI.h"
#include "AtGfx/DebugMessage.h"

#include <cstdint>

namespace AtGfx
{

	class Pipeline;
	class Buffer;

	struct GraphicsDeviceSpecification
	{
		void* (*GLGetAddressProc)(const char* name);
		DebugMessageCallback MessageCallback;
	};

	class GraphicsDevice
	{
	public:
		static GraphicsDevice* Create(GraphicsAPI graphicsAPI, GraphicsDeviceSpecification specification);
	public:
		virtual void Initialize() = 0;
		virtual void Deinitialize() = 0;

		virtual void Clear(float r, float g, float b, float a = 1.0f) const = 0;
		virtual void Draw(Pipeline* pipeline, Buffer* vertexBuffer, uint32_t vertexCount = 0) const = 0;
		virtual void DrawIndexed(Pipeline* pipeline, Buffer* vertexBuffer, Buffer* indexBuffer, uint32_t indexCount = 0) const = 0;

		GraphicsAPI GetGraphicsAPI() const
		{
			return m_GraphicsAPI;
		}
	protected:
		GraphicsDevice(GraphicsAPI graphicsAPI, GraphicsDeviceSpecification specification);
		virtual ~GraphicsDevice() = default;
	protected:
		GraphicsAPI m_GraphicsAPI = GraphicsAPI::None;
		GraphicsDeviceSpecification m_Specification;
	};

}