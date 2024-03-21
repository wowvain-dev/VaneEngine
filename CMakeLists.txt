cmake_minimum_required(VERSION 3.24)
project(VaneEngine)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Vane)
add_subdirectory(VaneEditor)
add_subdirectory(Sandbox)
