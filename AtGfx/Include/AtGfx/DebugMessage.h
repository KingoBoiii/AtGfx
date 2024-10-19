#pragma once

#include <format>

namespace AtGfx
{

	enum class MessageSeverity
	{
		None = -1,
		Trace = 1,
		Info,
		Warning,
		Error,
		Critical
	};

	typedef void(*DebugMessageCallback)(MessageSeverity severity, const char* message);

#define AT_GFX_ENSURE_DEBUG_MESSAGE_CALLBACK AtGfx::DebugMessageCallback g_DebugMessageCallback
#define AT_GFX_EXTERN_DEBUG_MESSAGE_CALLBACK extern AT_GFX_ENSURE_DEBUG_MESSAGE_CALLBACK

#define AT_GFX_TRACE(...)		g_DebugMessageCallback(AtGfx::MessageSeverity::Trace, std::format(__VA_ARGS__).c_str())
#define AT_GFX_INFO(...)		g_DebugMessageCallback(AtGfx::MessageSeverity::Info, std::format(__VA_ARGS__).c_str())
#define AT_GFX_WARN(...)		g_DebugMessageCallback(AtGfx::MessageSeverity::Warning, std::format(__VA_ARGS__).c_str())
#define AT_GFX_ERROR(...)		g_DebugMessageCallback(AtGfx::MessageSeverity::Error, std::format(__VA_ARGS__).c_str())
#define AT_GFX_CRITICAL(...)	g_DebugMessageCallback(AtGfx::MessageSeverity::Critical, std::format(__VA_ARGS__).c_str())

}