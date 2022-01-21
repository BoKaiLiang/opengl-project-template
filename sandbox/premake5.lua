-- Application
project "example"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin/intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"example/**.h",
		"example/**.cpp"
	}

	includedirs
	{
		"../external/glad/include",
		"../external/glfw3/include",
		"../external/glm",
		"../external/imgui",
		"../external/stb",
		"../core"
	}

	links
	{
		"core"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
        optimize "on"