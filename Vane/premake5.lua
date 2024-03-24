project "Vane"
    kind "SharedLib"
    language "C++"

    targetdir ("../build/" .. outputdir .. "/%{prj.name}")
    objdir ("../build-objs/" .. outputdir .. "/%{prj.name}")

    files { 
        "**.h",
        "**.hpp",
        "**.hxx",
        "**.c",
        "**.cc",
        "**.cpp",
        "**.cxx",
        "**.ixx"
     }

    defines { "VEXPORT" }

    includedirs { 
        "../vendor/" .. triplet .. '/include/',
    }

    libdirs {
        "../vendor/" .. triplet .. '/lib',
        os.getenv("VULKAN_SDK") .. '/lib',
    }

    links {
        "vulkan",
        "fmt",
        "SDL2:static",
        "SDL2main:static",
    }

    filter "configurations:dbg"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:rel" 
        defines { "RELEASE", "NDEBUG" }
        optimize "On"