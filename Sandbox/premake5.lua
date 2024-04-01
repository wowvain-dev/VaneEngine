project "Sandbox" 
    kind "ConsoleApp"
    cppdialect "C++20"
    
    dependson { "Vane" }

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

    filter "system:Windows"
        -- Copy the DLL to the binary directory of the Sandbox
        prebuildcommands {
            '{COPY} %{wks.location}build\\' .. outputdir .. '\\Vane\\Vane.dll %{wks.location}build\\' .. outputdir .. '\\%{prj.name}' 
        }

    filter "configurations:dbg" 
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:rel"
        defines { "RELEASE", "NDEBUG" }