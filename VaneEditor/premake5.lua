project "VaneEditor"
    kind "ConsoleApp"
    cppdialect "C++20"

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

        -- Shaders
        "Resources/Shaders/**.glsl",
        "Resources/Shaders/**.glslh",
        "Resources/Shaders/**.hlsl",
        "Resources/Shaders/**.hlslh",
        "Resources/Shaders/**.slh",
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
        "vane",
    }

    filter "system:Linux"
        links {
            "X11",
            "xcb",
            "X11-xcb"
        }

    filter "system:Windows"
        -- postbuildcommands {
        --     '{COPY} %{wks.location}build\\' .. outputdir .. '\\Vane\\Vane.dll %{wks.location}build\\' .. outputdir .. '\\%{prj.name}' 
        -- }

    filter "configurations:dbg"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:rel"
        defines { "RELEASE", "NDEBUG" }