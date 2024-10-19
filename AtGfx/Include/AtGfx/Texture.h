#pragma once
#include "AtGfx/GraphicsDevice.h"

#include "Bindable.h"

#include <filesystem>

namespace AtGfx
{

	enum class TextureWrap
	{
		NONE = 0,
		REPEAT,
		CLAMP,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class TextureFilter
	{
		NONE = 0,
		LINEAR,
		NEAREST
	};

	enum class TextureFormat
	{
		NONE = 0,
		RGB,
		RGBA,
		RED,
		RED_INTEGER,
		LUMINANCE_ALPHA
	};

	struct TextureSpecification
	{
		TextureFormat Format;
		TextureFilter Filter;
		TextureFilter MinFilter;
		TextureFilter MagFilter;
		TextureWrap WrapMode;
		bool FlipVertically = true;

		TextureSpecification()
		{
			Format = TextureFormat::RGBA;
			Filter = TextureFilter::LINEAR;

			MinFilter = TextureFilter::LINEAR;
			MagFilter = TextureFilter::NEAREST;

			WrapMode = TextureWrap::REPEAT;
		}
	};

	class Texture : public Internal::Bindable
	{
	public:
		static Texture* Create(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification = TextureSpecification());
	public:
		virtual ~Texture() = default;
	public:
		virtual void Bind() const override
		{
			Bind(0);
		}
		virtual void Bind(uint32_t slot) const = 0;
	protected:
		Texture(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification);
	protected:
		GraphicsDevice* m_GraphicsDevice = nullptr;
		std::filesystem::path m_FilePath;
		int32_t m_Width;
		int32_t m_Height;
		TextureSpecification m_Specification;
	};

}