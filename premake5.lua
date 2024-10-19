workspace "AtGfx"
	architecture "x86_64"
	startproject "Sandbox"

	configurations { 
		"Debug",
		"Release"
	}

    flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir['glad'] = "%{wks.location}/AtGfx/Vendor/glad/include";
IncludeDir['stb_image'] = "%{wks.location}/AtGfx/Vendor/stb_image";

LibraryDir = {}
Library = {}

include "AtGfx"
include "Sandbox"

