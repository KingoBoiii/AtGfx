#include "OpenGLShader.h"

#include <glad/glad.h>

namespace AtomGfx
{

	AT_GFX_EXTERN_DEBUG_MESSAGE_CALLBACK;

	OpenGLShader::OpenGLShader(GraphicsDevice* graphicsDevice, const std::string& filepath)
		: Shader(graphicsDevice, filepath)
	{
		CreateShaderProgram();
	}

	OpenGLShader::OpenGLShader(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name)
		: Shader(graphicsDevice, filepath, name)
	{
		CreateShaderProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		DeleteShaderProgram();
	}

	void OpenGLShader::SetInt(const std::string& name, int32_t value) const
	{
		auto it = m_UniformLocations.find(name);
		if (it == m_UniformLocations.end())
		{
			AT_GFX_WARN("Uniform name '{}' does not exist on Shader", name);
			return;
		}

		int32_t location = it->second;
		glUniform1i(location, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const float* matrix) const
	{
		auto it = m_UniformLocations.find(name);
		if (it == m_UniformLocations.end())
		{
			AT_GFX_WARN("Uniform name '{}' does not exist on Shader", name);
			return;
		}

		int32_t location = it->second;
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	uint32_t OpenGLShader::CreateShader(const char* source, uint32_t type)
	{
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		int32_t compileStatus;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(shader, 1024, &log_length, message);
			// Write the error to a log
			AT_GFX_ERROR("SHADER_COMPILATION\n{}", message);
		}

		return shader;
	}

	uint32_t OpenGLShader::CreateShaderProgram(uint32_t vertexShader, uint32_t fragmentShader)
	{
		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetProgramInfoLog(program, 1024, &log_length, message);
			// Write the error to a log
			AT_GFX_ERROR("PROGRAM_LINKING\n{}", message);
		}

		return program;
	}

	void OpenGLShader::CreateShaderProgram()
	{
		std::string shaderFileContent = ReadFile(m_FilePath);
		std::string* shaderSources[2] = { &m_VertexSource, &m_FragmentSource };
		PreProcess(shaderFileContent, shaderSources);

		uint32_t vertexShader = CreateShader(m_VertexSource.c_str(), GL_VERTEX_SHADER);
		uint32_t fragmentShader = CreateShader(m_FragmentSource.c_str(), GL_FRAGMENT_SHADER);

		m_RendererId = CreateShaderProgram(vertexShader, fragmentShader);

		GetActiveUniforms();
	}

	void OpenGLShader::DeleteShaderProgram()
	{
		glDeleteProgram(m_RendererId);
		m_RendererId = 0;
	}

	void OpenGLShader::GetActiveUniforms()
	{
		int32_t activeUniformCount;
		glGetProgramiv(m_RendererId, GL_ACTIVE_UNIFORMS, &activeUniformCount);
		m_UniformLocations.reserve(activeUniformCount);

		char name[128];
		int32_t length;
		int32_t size;
		uint32_t type;
		for (int32_t i = 0; i < activeUniformCount; i++)
		{
			glGetActiveUniform(m_RendererId, i, sizeof(name), &length, &size, &type, name);
			int32_t location = glGetUniformLocation(m_RendererId, name);
			m_UniformLocations[name] = location;
		}
		
		AT_GFX_INFO("Shader loaded with {} active uniforms", activeUniformCount);
	}

}