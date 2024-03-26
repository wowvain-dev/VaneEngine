project "Vane"
    kind "SharedLib"
    cppdialect "C++20"
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
        "fmt",
        "SDL2",
    }

    filter "system:Linux"
        links {
            "X11",
            "xcb",
            "X11-xcb",
            "vulkan",
            "SDL2main"
        }

    filter "system:Windows"
        links {
            "vulkan-1"
        }

    filter "configurations:dbg"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:rel" 
        defines { "RELEASE", "NDEBUG" }
        optimize "On"