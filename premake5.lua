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
LibraryDir = {}
Library = {}

group "Dependencies" 
group ""

include "AtGfx"
include "Sandbox"

