#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace AtomGfx
{

	namespace Utils
	{

		GLenum TextureFilterToGL(TextureFilter filter)
		{
			switch (filter)
			{
				case TextureFilter::LINEAR:				return GL_LINEAR;
				case TextureFilter::NEAREST:			return GL_NEAREST;
				case TextureFilter::NONE:
				default: break;
			}
			return 0;
		}

		enum class FormatType
		{
			INTERNAL, DATA
		};
		GLenum TextureFormatToGL(TextureFormat format, FormatType formatType)
		{
			switch (format)
			{
				case TextureFormat::RGBA:				return formatType == FormatType::DATA ? GL_RGBA : GL_RGBA8;
				case TextureFormat::RGB:				return formatType == FormatType::DATA ? GL_RGB : GL_RGB8;
				case TextureFormat::RED:				return formatType == FormatType::DATA ? GL_RED : GL_RED;	// 0x1909 = GL_LUMINANCE
				case TextureFormat::RED_INTEGER:		return formatType == FormatType::DATA ? GL_RED_INTEGER : GL_RED_INTEGER;
				case TextureFormat::LUMINANCE_ALPHA:	return formatType == FormatType::DATA ? GL_RG : GL_RG;	// 0x190A = GL_LUMINANCE_ALPHA
				case TextureFormat::NONE:
				default: break;
			}
			return 0;
		}

		GLenum TextureWrapToGL(TextureWrap wrap)
		{
			switch (wrap)
			{
				case TextureWrap::CLAMP:				return 0x2900;		// GL_CLAMP
				case TextureWrap::CLAMP_TO_BORDER:		return GL_CLAMP_TO_BORDER;
				case TextureWrap::CLAMP_TO_EDGE:		return GL_CLAMP_TO_EDGE;
				case TextureWrap::REPEAT:				return GL_REPEAT;
				case TextureWrap::MIRRORED_REPEAT:		return GL_MIRRORED_REPEAT;
				case TextureWrap::NONE:
				default: break;
			}
			return 0;
		}

	}

	OpenGLTexture::OpenGLTexture(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification)
		: Texture(graphicsDevice, filepath, specification), m_RendererId(0)
	{
		int32_t channels;
		stbi_set_flip_vertically_on_load(m_Specification.FlipVertically);
		unsigned char* data = stbi_load(m_FilePath.string().c_str(), &m_Width, &m_Height, &channels, 0);
		if (data)
		{
			m_Specification.Format = channels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;

			glGenTextures(1, &m_RendererId);
			glBindTexture(GL_TEXTURE_2D, m_RendererId);

			glTextureStorage2D(m_RendererId, 1, Utils::TextureFormatToGL(m_Specification.Format, Utils::FormatType::INTERNAL), m_Width, m_Height);

			SetTextureParameters();

			glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, Utils::TextureFormatToGL(m_Specification.Format, Utils::FormatType::DATA), GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererId);
	}

	void OpenGLTexture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::SetTextureParameters()
	{
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, Utils::TextureFilterToGL(m_Specification.MinFilter));
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, Utils::TextureFilterToGL(m_Specification.MagFilter));
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, Utils::TextureWrapToGL(m_Specification.WrapMode));
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, Utils::TextureWrapToGL(m_Specification.WrapMode));
	}

}