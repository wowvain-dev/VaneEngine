-- if __ACTION__ ~= "clean" then
--     os.execute('vcpkg install --x-buildtrees-root=' .. os.getenv("VCPKG_BTREE") .. ' --x-install-root=./vendor')
-- end 

workspace "VaneWorkspace"
    configurations { "dbg", "rel" }
    architecture "x64"
    startproject "VaneEditor"
    cppdialect "C++20"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-x64"

    vcpkgRoot = os.getenv("VCPKG_ROOT")
    triplet = os.getenv("VCPKG_DEFAULT_TRIPLET")
    externalBuildTreeRoot = os.getenv("VCPKG_BTREE")

    if os.host() == "windows" then 
        triplet = triplet or "x64-windows"
        externalBuildTreeRoot = externalBuildTreeRoot or "C:/vcpkg_build_trees"
        vcpkgRoot = vcpkgRoot or os.getenv("USERPROFILE") .. "/vcpkg"
    elseif os.host() == "linux" then 
        triplet = triplet or "x64-linux"
        externalBuildTreeRoot = externalBuildTreeRoot or "/tmp/vcpkg_build_trees"
        vcpkgRoot = vcpkgRoot or os.getenv("HOME") .. "/vcpkg"
    elseif os.host() == "macos" then
        triplet = triplet or "x64-osx"
        externalBuildTreeRoot = externalBuildTreeRoot or "/tmp/vcpkg_build_trees"
        vcpkgRoot = vcpkgRoot or os.getenv("HOME") .. "/vcpkg"
    end

    include "Vane"
    include "VaneEditor"
    include "Sandbox"

    newaction {
        trigger = "fetch",
        description = "Fetches the vcpkg dependencies into the vendor/ folder.",
        execute = function ()
            os.execute('vcpkg install --x-buildtrees-root=' .. os.getenv("VCPKG_BTREE") .. ' --x-install-root=./vendor')
        end
    }

    newaction {
        trigger = "clean",
        description = "Cleans the build and configuration files.",
        execute = function ()
            print("Cleaning the build...")
            os.rmdir("./build")
            os.rmdir("./build-objs")
            os.remove("Makefile")
            os.remove("**/Makefile")
            os.remove("CMakeLists.txt")
            os.remove("**/CMakeLists.txt")
            os.remove("**.sln")
            os.remove("**.vcxproj")
            os.remove("**.vcxproj.filters")
            os.remove("**.vcxproj.user")
        end
    }

    function runexec(config, exec)
        if os.host() == "windows" then 
            os.execute("./build/" .. config .. "-windows-x64/" .. exec .. "/" .. exec ".exe")
        elseif os.host() == "linux" then 
            os.execute("./build/" .. config .. "-linux-x64/" .. exec .. "/" .. exec)
        end
    end

    newaction {
        trigger = "run",
        description = "Runs the default config",
        execute = function ()
            runexec("dbg", "Sandbox")
        end
    }

    newaction {
        trigger = "dbg-sandbox",
        description = "Run the sandbox target.",
        execute = function ()
            runexec("dbg", "Sandbox")
        end 
    }