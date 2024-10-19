#pragma once
#include "AtomGfx/Shader.h"

#include <unordered_map>
#include <cstdint>

namespace AtomGfx
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(GraphicsDevice* graphicsDevice, const std::string& filepath);
		OpenGLShader(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name);
		virtual ~OpenGLShader();
	public:
		virtual void SetInt(const std::string& name, int32_t value) const override;
		virtual void SetMat4(const std::string& name, const float* matrix) const override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t CreateShader(const char* source, uint32_t type);
		uint32_t CreateShaderProgram(uint32_t vertexShader, uint32_t fragmentShader);

		void CreateShaderProgram();
		void DeleteShaderProgram();

		void GetActiveUniforms();
	private:
		uint32_t m_RendererId = 0;
		std::string m_VertexSource;
		std::string m_FragmentSource;
		std::unordered_map<std::string, int32_t> m_UniformLocations;
	};

}
