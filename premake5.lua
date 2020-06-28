workspace "OpenGL"
	architecture "x64"
	startproject "example"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"


include "ext"
include "core"
include "sandbox"