#pragma once

#include <format>

namespace AtomGfx
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

#define AT_GFX_ENSURE_DEBUG_MESSAGE_CALLBACK AtomGfx::DebugMessageCallback g_DebugMessageCallback
#define AT_GFX_EXTERN_DEBUG_MESSAGE_CALLBACK extern AT_GFX_ENSURE_DEBUG_MESSAGE_CALLBACK

#define AT_GFX_TRACE(...)		g_DebugMessageCallback(AtomGfx::MessageSeverity::Trace, std::format(__VA_ARGS__).c_str())
#define AT_GFX_INFO(...)		g_DebugMessageCallback(AtomGfx::MessageSeverity::Info, std::format(__VA_ARGS__).c_str())
#define AT_GFX_WARN(...)		g_DebugMessageCallback(AtomGfx::MessageSeverity::Warning, std::format(__VA_ARGS__).c_str())
#define AT_GFX_ERROR(...)		g_DebugMessageCallback(AtomGfx::MessageSeverity::Error, std::format(__VA_ARGS__).c_str())
#define AT_GFX_CRITICAL(...)	g_DebugMessageCallback(AtomGfx::MessageSeverity::Critical, std::format(__VA_ARGS__).c_str())

}