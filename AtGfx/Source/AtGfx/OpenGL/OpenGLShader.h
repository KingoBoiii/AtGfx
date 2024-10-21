#pragma once
#include "AtGfx/Shader.h"

#include <unordered_map>
#include <cstdint>

namespace AtGfx
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(GraphicsDevice* graphicsDevice, const std::string& filepath);
		OpenGLShader(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name);
		OpenGLShader(GraphicsDevice* graphicsDevice, const char* vertexShaderSource, const char* fragmentShaderSource, const std::string& name);
		virtual ~OpenGLShader();
	public:
		virtual void SetInt(const std::string& name, int32_t value) const override;
		virtual void SetVec4(const std::string& name, float v0, float v1, float v2, float v3) const override;
		virtual void SetMat4(const std::string& name, const float* matrix) const override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t CreateShader(const char* source, uint32_t type);
		uint32_t CreateShaderProgram(uint32_t vertexShader, uint32_t fragmentShader);

		void CreateShaderProgram(bool preProcess = true);
		void DeleteShaderProgram();

		void GetActiveUniforms();
	private:
		uint32_t m_RendererId = 0;
		std::string m_VertexSource;
		std::string m_FragmentSource;
		std::unordered_map<std::string, int32_t> m_UniformLocations;
	};

}
