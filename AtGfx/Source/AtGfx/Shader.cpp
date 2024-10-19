#include "AtGfx/Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace AtGfx
{

	Shader* Shader::Create(GraphicsDevice* graphicsDevice, const std::string& filepath)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtGfx::GraphicsAPI::OpenGL:		return new OpenGLShader(graphicsDevice, filepath);
			case AtGfx::GraphicsAPI::Vulkan:
			case AtGfx::GraphicsAPI::DirectX11:
			case AtGfx::GraphicsAPI::DirectX12:
			case AtGfx::GraphicsAPI::None:
			default:
				break;
		}

		return nullptr;
	}

	Shader* Shader::Create(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtGfx::GraphicsAPI::OpenGL:		return new OpenGLShader(graphicsDevice, filepath, name);
			case AtGfx::GraphicsAPI::Vulkan:
			case AtGfx::GraphicsAPI::DirectX11:
			case AtGfx::GraphicsAPI::DirectX12:
			case AtGfx::GraphicsAPI::None:
			default:
				break;
		}

		return nullptr;
	}

	Shader::Shader(GraphicsDevice* graphicsDevice, const std::string& filepath)
		: m_GraphicsDevice(graphicsDevice), m_FilePath(filepath)
	{
		m_Name = GetNameByFilepath(filepath);
	}

	Shader::Shader(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name)
		: m_GraphicsDevice(graphicsDevice), m_FilePath(filepath), m_Name(name)
	{
	}

	std::string Shader::ReadFile(const std::string& filepath)
	{
		FILE* file = fopen(filepath.c_str(), "r");
		if (file == nullptr)
		{
			// error file not found
			return std::string();
		}

		fseek(file, 0L, SEEK_END);
		int64_t size = ftell(file);
		rewind(file);

		char* buffer = new char[size + 1];
		size_t eof = fread(buffer, 1, size, file);
		buffer[eof] = '\0';

		fclose(file);

		return buffer;
	}

	std::vector<std::string> Shader::GetLines(const std::string& source)
	{
		size_t start = 0;
		size_t end = source.find_first_of("\n");

		std::vector<std::string> result;

		while (end <= std::string::npos)
		{
			std::string token = source.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == std::string::npos)
				break;

			start = end + 1;
			end = source.find_first_of("\n", start);
		}

		return result;
	}

	void Shader::PreProcess(const std::string& source, std::string** shaders)
	{
		ShaderType type = ShaderType::UNKNOWN;

		std::vector<std::string> lines = GetLines(source);
		for (uint32_t i = 0; i < lines.size(); i++)
		{
			const char* str = lines[i].c_str();
			if (strstr(str, "#type"))
			{
				if (strstr(str, "vertex"))
				{
					type = ShaderType::VERTEX;
				}
				else if (strstr(str, "fragment") || strstr(str, "pixel"))
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else if (type != ShaderType::UNKNOWN)
			{
				shaders[(int32_t)type]->append(str);
				shaders[(int32_t)type]->append("\n");
			}
		}
	}

	std::string Shader::GetNameByFilepath(const std::string& filepath)
	{
		std::string filename;

		size_t found = filepath.find_last_of("/\\");
		filename = found != std::string::npos ? filepath.substr(found + 1) : filepath;
		found = filename.find_first_of(".");
		filename = found != std::string::npos ? filename.substr(0, found) : filepath;

		return filename;
	}

}