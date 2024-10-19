#include "OpenGLGraphicsDevice.h"

#include "AtGfx/Pipeline.h"
#include "AtGfx/Buffer.h"

#include <glad/glad.h>

namespace AtGfx
{

	AT_GFX_ENSURE_DEBUG_MESSAGE_CALLBACK;

	static void OpenGLMessageCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         AT_GFX_CRITICAL("[OpenGL]: {}", message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       AT_GFX_ERROR("[OpenGL]: {}", message); return;
			case GL_DEBUG_SEVERITY_LOW:          AT_GFX_WARN("[OpenGL]: {}", message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: AT_GFX_TRACE("[OpenGL]: {}", message); return;
			default: break;
		}

		AT_GFX_ERROR("Unknown severity level!");
	}

	OpenGLGraphicsDevice::OpenGLGraphicsDevice(GraphicsDeviceSpecification specification)
		: GraphicsDevice(GraphicsAPI::OpenGL, specification)
	{
	}

	OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
	{
	}

	void OpenGLGraphicsDevice::Initialize()
	{
		g_DebugMessageCallback = m_Specification.MessageCallback;

		if (m_Specification.GLGetAddressProc == nullptr)
		{
			AT_GFX_CRITICAL("Trying to initialize graphics device with no GLGetAddressProc specified.");
			return;
		}

		int status = gladLoadGLLoader((GLADloadproc)m_Specification.GLGetAddressProc);
		if (status == GL_FALSE)
		{
			AT_GFX_ERROR("Failed to load 'glad' library!");
		}

		AT_GFX_TRACE("OpenGL Info:");
		AT_GFX_TRACE("| Vendor: {}", (char*)glGetString(GL_VENDOR));
		AT_GFX_TRACE("| Renderer: {}", (char*)glGetString(GL_RENDERER));
		AT_GFX_TRACE("| Version: {}", (char*)glGetString(GL_VERSION));

#ifdef AT_GFX_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

#ifdef AT_GFX_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		KE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "AtGfx requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLGraphicsDevice::Deinitialize()
	{
	}

	void OpenGLGraphicsDevice::Draw(Pipeline* pipeline, Buffer* vertexBuffer, uint32_t vertexCount) const
	{
		if (!vertexBuffer->IsBufferType(BufferType::VertexBuffer))
		{
			AT_GFX_WARN("Trying to invoke draw call, only with VertexBuffer, with incorrect buffer type. Ignoring draw call.");
			return;
		}

		uint32_t count = vertexCount;
		if (count == 0)
		{
			count = vertexBuffer->GetCount();
		}

		pipeline->Bind();
		vertexBuffer->Bind();

		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void OpenGLGraphicsDevice::DrawIndexed(Pipeline* pipeline, Buffer* vertexBuffer, Buffer* indexBuffer, uint32_t indexCount) const
	{
		if (!vertexBuffer->IsBufferType(BufferType::VertexBuffer))
		{
			AT_GFX_WARN("Trying to invoke indexed draw call, with incorrect buffer type for IndexBuffer. Ignoring draw call.");
			return;
		}

		if (!indexBuffer->IsBufferType(BufferType::IndexBuffer))
		{
			AT_GFX_WARN("Trying to invoke indexed draw call, with incorrect buffer type for IndexBuffer. Ignoring draw call.");
			return;
		}

		uint32_t count = indexCount;
		if (count == 0)
		{
			count = indexBuffer->GetCount();
		}

		pipeline->Bind();
		vertexBuffer->Bind();
		indexBuffer->Bind();

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

}