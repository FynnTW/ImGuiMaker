project "GLAD"
	kind "StaticLib"
	language "C"
	buildoptions "/MT"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/Glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
	}

	includedirs
	{
		"include"
	}
	
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
