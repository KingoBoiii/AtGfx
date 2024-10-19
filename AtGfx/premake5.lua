project "AtGfx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Include/**.h",
		"Include/**.hpp",
		"Source/**.h",
		"Source/**.hpp",
		"Source/**.cpp",
		
		-- glad (OpenGL extension)
		"%{prj.location}/Vendor/glad/include/glad/glad.h",
		"%{prj.location}/Vendor/glad/include/KHR/khrplatform.h",
		"%{prj.location}/Vendor/glad/src/glad.c",
		
		-- stb-image
		"%{prj.location}/Vendor/stb_image/**.h",
		"%{prj.location}/Vendor/stb_image/**.cpp"
	}
    
    includedirs {
		"Include",
		"%{prj.location}/Vendor/glad/include",
		"%{prj.location}/Vendor/stb_image"
    }

    links {
        "opengl32.lib"
    }

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "AT_GFX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AT_GFX_RELEASE"
		runtime "Release"
		optimize "on"
