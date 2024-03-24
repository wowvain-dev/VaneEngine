project "Sandbox" 
    kind "ConsoleApp"

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
        "**.ixx",
    }

    includedirs {
        "../vendor/" .. triplet .. '/include/',
        "../Vane/",
        "../Vane/include/"
    }

    libdirs {
        "../vendor/" .. triplet .. '/lib'
    }

    links {
        "vane"
    }

    filter "configurations:dbg" 
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:rel"
        defines { "RELEASE", "NDEBUG" }