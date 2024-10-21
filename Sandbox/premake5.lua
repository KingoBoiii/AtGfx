project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.cpp",
		"Source/**.h",
		"%{prj.location}/Vendor/glad/src/**.c",
		"%{prj.location}/Vendor/glad/include/**.h",
		"%{prj.location}/Vendor/imgui/**.h",
		"%{prj.location}/Vendor/imgui/**.cpp",
		"%{prj.location}/Vendor/glm/**.h",
		"%{prj.location}/Vendor/glm/**.hpp",
		"%{prj.location}/Vendor/glm/**.inl",
		"%{prj.location}/Vendor/glm/**.cpp",
		"%{prj.location}/Vendor/glm/**.cppm"
	}
	
	includedirs {
		"Source",
		"%{wks.location}/AtGfx/Include",
		"%{prj.location}/Vendor/glfw/include",
		"%{prj.location}/Vendor/glad/include",
		"%{prj.location}/Vendor/imgui",
		"%{prj.location}/Vendor/glm"
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