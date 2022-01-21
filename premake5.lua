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


include "external"
include "core"
include "sandbox"