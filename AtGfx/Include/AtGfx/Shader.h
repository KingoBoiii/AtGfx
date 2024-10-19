#pragma once
#include "GraphicsDevice.h"
#include "Bindable.h"

#include <vector>
#include <string>

namespace AtGfx
{

	class Shader : public Internal::Bindable
	{
	public:
		static Shader* Create(GraphicsDevice* graphicsDevice, const std::string& filepath);
		static Shader* Create(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name);
	public:
		virtual ~Shader() = default;
	public:
		virtual void SetInt(const std::string& name, int32_t value) const = 0;
		virtual void SetMat4(const std::string& name, const float* matrix) const = 0;
	protected:
		Shader(GraphicsDevice* graphicsDevice, const std::string& filepath);
		Shader(GraphicsDevice* graphicsDevice, const std::string& filepath, const std::string& name);
	protected:
		std::string ReadFile(const std::string& filepath);
		std::vector<std::string> GetLines(const std::string& source);
		void PreProcess(const std::string& source, std::string** shaders);
		std::string GetNameByFilepath(const std::string& filepath);
	protected:
		GraphicsDevice* m_GraphicsDevice = nullptr;
		std::string m_Name;
		std::string m_FilePath;
	private:
		enum class ShaderType
		{
			UNKNOWN = -1,
			VERTEX,
			FRAGMENT
		};
	};

}