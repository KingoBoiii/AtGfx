#pragma once
#include "GraphicsDevice.h"
#include "Bindable.h"

#include <vector>
#include <string>
#include <filesystem>

namespace AtGfx
{

	class Shader : public Internal::Bindable
	{
	public:
		static Shader* Create(GraphicsDevice* graphicsDevice, const std::string& name);
		static Shader* Create(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath);
		static Shader* Create(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const std::string& name);
		static Shader* Create(GraphicsDevice* graphicsDevice, const char* vertexShaderSource, const char* fragmentShaderSource, const std::string& name);
	public:
		virtual ~Shader() = default;
	public:
		virtual void SetInt(const std::string& name, int32_t value) const = 0;
		virtual void SetVec4(const std::string& name, float v0, float v1, float v2, float v3) const = 0;
		virtual void SetMat4(const std::string& name, const float* matrix) const = 0;
	protected:
		Shader(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const std::string& name);
	protected:
		std::string ReadFile(const std::filesystem::path& filepath);
		std::vector<std::string> GetLines(const std::string& source);
		void PreProcess(const std::string& source, std::string** shaders);
	protected:
		GraphicsDevice* m_GraphicsDevice = nullptr;
		std::string m_Name;
		std::filesystem::path m_FilePath;
	private:
		enum class ShaderType
		{
			UNKNOWN = -1,
			VERTEX,
			FRAGMENT
		};
	};

}