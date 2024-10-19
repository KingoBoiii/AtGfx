project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.cpp",
		"Source/**.h"
	}
	
	includedirs {
		"%{wks.location}/AtGfx/Include",
		"%{prj.location}/Vendor/glfw/include"
    }

	links {
		"AtGfx",
		"%{prj.location}/Vendor/glfw/lib-vc2022/glfw3.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"