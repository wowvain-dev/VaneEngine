cmake_minimum_required(VERSION 3.24)
project(Sandbox)

message("Loading Sandbox...")


add_executable(Sandbox
    main.cpp
)

target_include_directories(Sandbox
    PRIVATE ${CMAKE_SOURCE_DIR}/Vane
)

target_link_libraries(Sandbox PRIVATE
    Vane
)
cmake_minimum_required(VERSION 3.24)
project(Sandbox)

message("Loading Sandbox...")


add_executable(Sandbox
    main.cpp
)

target_include_directories(Sandbox
    PRIVATE ${CMAKE_SOURCE_DIR}/Vane
)

target_link_libraries(Sandbox PRIVATE
    Vane
)