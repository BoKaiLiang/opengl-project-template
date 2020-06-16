project "OpenGL-App"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin/intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../OpenGL-Lib/ext/spdlog/include",
		"../OpenGL-Lib/src",
		"../OpenGL-Lib/ext",
		"../OpenGL-Lib/%{IncludeDir.glm}",
		"../OpenGL-Lib/%{IncludeDir.glad}",
		"../OpenGL-Lib/%{IncludeDir.imgui}",
		"../OpenGL-Lib/%{IncludeDir.tinyobjloader}"
	}

	links
	{
		"OpenGL-Lib"
	}
	filter "system:windows"
		systemversion "latest"


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
        optimize "on"
