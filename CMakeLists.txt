cmake_minimum_required(VERSION 3.24)
project(VaneEngine)

include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

add_subdirectory(Vane)
add_subdirectory(VaneEditor)
add_subdirectory(Sandbox)
