-- defines the Premake file for the C++ Lib

configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    includeDir = {}

    includeDir["Glad"] = "Library/Glad/include"
    includeDir["stb"] = "Library/stb"
    includeDir["GLFW"] = "Library/GLFW/include"
    includeDir["glm"] = "Library/glm"
    
    --includes the premake files
    include "Library/GLFW"
    include "Library/Glad"
    include "Library/stb"

project "Glfix"
    kind "StaticLib"
    language "C"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    pchheader "gpch.h"
    pchsource "src/gpch.c"

    files 
    {
        "includes/**.h",
        "src/**.c",
    }
    
    includedirs
    {
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        "%{includeDir.glm}",
        "%{includeDir.stb}",
        "includes"
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

    flags
    {
        "MultiProcessorCompile"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build"
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