add_executable("VaneEditor"
  "VaneEditor/main.cpp"
  "VaneEditor/window.cxx"
  "VaneEditor/window.hxx"
)
if(CMAKE_BUILD_TYPE STREQUAL dbg)
  set_target_properties("VaneEditor" PROPERTIES
    OUTPUT_NAME "VaneEditor"
    ARCHIVE_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneEngine/build/dbg-linux-x64/VaneEditor"
    LIBRARY_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneEngine/build/dbg-linux-x64/VaneEditor"
    RUNTIME_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneEngine/build/dbg-linux-x64/VaneEditor"
  )
endif()
target_include_directories("VaneEditor" PRIVATE
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneEngine/vendor/x64-linux/include>
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneEngine/Vane>
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneEngine/Vane/include>
)
target_compile_definitions("VaneEditor" PRIVATE
)
target_link_directories("VaneEditor" PRIVATE
)
target_link_libraries("VaneEditor"
)
target_compile_options("VaneEditor" PRIVATE
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL dbg)
  set_target_properties("VaneEditor" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL rel)
  set_target_properties("VaneEditor" PROPERTIES
    OUTPUT_NAME "VaneEditor"
    ARCHIVE_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneEngine/build/rel-linux-x64/VaneEditor"
    LIBRARY_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneEngine/build/rel-linux-x64/VaneEditor"
    RUNTIME_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneEngine/build/rel-linux-x64/VaneEditor"
  )
endif()
target_include_directories("VaneEditor" PRIVATE
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneEngine/vendor/x64-linux/include>
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneEngine/Vane>
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneEngine/Vane/include>
)
target_compile_definitions("VaneEditor" PRIVATE
)
target_link_directories("VaneEditor" PRIVATE
)
target_link_libraries("VaneEditor"
)
target_compile_options("VaneEditor" PRIVATE
  $<$<AND:$<CONFIG:rel>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:rel>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:rel>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL rel)
  set_target_properties("VaneEditor" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()