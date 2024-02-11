---@diagnostic disable: undefined-global
workspace "EopGuiMaker"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/GLAD/include"
IncludeDir["ImGui"] = "vendor/imgui"

include "vendor/GLFW"
include "vendor/Glad"
include "vendor/imgui"

project "EopGuiMaker"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "gmpch.h"
	pchsource "src/gmpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src/%{prj.name}",
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
		"dwmapi.lib",
		"Glad",
        "ImGui"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GUIMAKER_PLATFORM_WINDOWS",
            "GUIMAKER_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} bin/".. outputdir .."/%{prj.name}/EopGuiMaker.dll" .. " bin/".. outputdir .."/GuiMaker")
        }

    filter "configurations:Debug"
        defines "GUIMAKER_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GUIMAKER_RELEASE"
        optimize "On"
    
    --[[
    filters { "system:windows", "configurations:Release", }
        buildoptions "/MT"
    ]]

project "GuiMaker"
    location "GuiMaker"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
    }

    links 
	{
        "eopGuiMaker",
        "ImGui"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GUIMAKER_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "GUIMAKER_DEBUG"
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "GUIMAKER_RELEASE"
        optimize "On"
        buildoptions "/MD"