os.execute('vcpkg install --x-buildtrees-root=' .. os.getenv("VCPKG_BTREE") .. ' --x-install-root=./vendor')

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