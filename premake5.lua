-- OpenGL-Example
workspace "OpenGL"
	architecture "x64"
	startproject "OpenGL-App"

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

-- Include directories relative to OpenGL-Core
IncludeDir = {}
IncludeDir["glfw3"] = "ext/glfw3/include"
IncludeDir["glad"] = "ext/glad/include"
IncludeDir["imgui"] = "ext/imgui"
IncludeDir["glm"] = "ext/glm"
IncludeDir["stb"] = "ext/stb"
IncludeDir["tinyobjloader"] = "ext/tinyobjloader"

-- Projects
group "Dependencies"
	include "OpenGL-Lib/ext/glfw3"
	include "OpenGL-Lib/ext/glad"
	include "OpenGL-Lib/ext/imgui"
group ""

include "OpenGL-Lib"
include "OpenGL-App"