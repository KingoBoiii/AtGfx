#pragma once
#include "AtGfx/GraphicsDevice.h"

namespace AtGfx
{

	class OpenGLGraphicsDevice : public GraphicsDevice
	{
	public:
		OpenGLGraphicsDevice(GraphicsDeviceSpecification specification);
		virtual ~OpenGLGraphicsDevice();
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;

		virtual void Draw(Pipeline* pipeline, Buffer* vertexBuffer, uint32_t vertexCount = 0) const override;
		virtual void DrawIndexed(Pipeline* pipeline, Buffer* vertexBuffer, Buffer* indexBuffer, uint32_t indexCount = 0) const override;
	};

}
