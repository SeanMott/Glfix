workspace "Glfix"
    architecture "x86"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}

includeDir["Glad"] = "Library/Glad/include"
includeDir["stb"] = "Library/stb"
includeDir["GLFW"] = "Library/GLFW/include"
includeDir["glm"] = "Library/glm"

--includes the premake files
include "Library/GLFW"
include "Library/Glad"
include "Library/stb"

--Glfix lib
project "Glfix"
    location "Glfix"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    pchheader "gpch.h"
    pchsource "%{prj.name}/src/gpch.c"

    files 
    {
        "%{prj.name}/includes/**.h",
        "%{prj.name}/src/**.c",
    }
    
    includedirs
    {
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        --"%{includeDir.glm}",
        "%{includeDir.stb}",
        "%{prj.name}/includes"
    }
    
    links
    {
        "StbImage",
        "Glad",
        "GLFW",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_STATIC",
        "GLFW_INCLUDE_NONE",
        --"GLM_FORCE_RADIANS",
        --"GLM_FORCE_DEPTH_ZERO_TO_ONE",
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }

        files 
        {
            --"%{prj.name}/src/**.h",
            --"%{prj.name}/src/**.c",
            --include window platform code
        }
    
    filter "configurations:Debug"
        defines "GLFIX_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "GLFIX_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "GLFIX_DIST"
        optimize "On"

--Openglfix test app
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }
    
    includedirs
    {
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        "%{includeDir.glm}",
        --"%{includeDir.stb}",
        "%{prj.name}/src",
        "Glfix/includes"
    }
    
    links
    {
        "Glfix"
        --"StbImage",
        --"Glad",
        --"GLFW",
        --"opengl32.lib"
    }

    defines
    {
        "GLFW_STATIC",
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
    
    filter "configurations:Debug"
        defines "GLFIX_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "GLFIX_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "GLFIX_DIST"
        optimize "On"