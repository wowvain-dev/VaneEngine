cmake_minimum_required(VERSION 3.24)
project(VaneEditor LANGUAGES CXX)

message("Loading Vane Editor...")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
)

qt_standard_project_setup()

qt_add_executable(VaneEditor 
#    MACOSX_BUNDLE WIN32
    main.cpp    
)

target_include_directories(VaneEditor
    PRIVATE ${CMAKE_SOURCE_DIR}/Vane
)

target_link_libraries(
    VaneEditor PRIVATE
    Vane
    Qt6::Widgets
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(TOOL_WINDEPLOYQT NAMES windeployqt.debug.bat)
else()
    find_program(TOOL_WINDEPLOYQT NAMES windeployqt)
endif()

add_custom_command(TARGET VaneEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Configuring Qt6 platform..."
        COMMAND ${TOOL_WINDEPLOYQT}
        $<TARGET_FILE:VaneEditor>
        COMMENT "Running windeployqt..."
)

#set_target_properties(VaneEditor PROPERTIES
#    WIN32_EXECUTABLE ON
#    MACOSX_BUNDLE ON
#)

