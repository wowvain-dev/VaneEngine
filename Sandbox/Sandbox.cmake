add_executable("Sandbox"
  "Sandbox/main.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL dbg)
  add_dependencies("Sandbox"
    "Vane"
  )
  set_target_properties("Sandbox" PROPERTIES
    OUTPUT_NAME "Sandbox"
    ARCHIVE_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneSystems/Engine/build/dbg-linux-x64/Sandbox"
    LIBRARY_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneSystems/Engine/build/dbg-linux-x64/Sandbox"
    RUNTIME_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneSystems/Engine/build/dbg-linux-x64/Sandbox"
  )
endif()
target_include_directories("Sandbox" PRIVATE
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneSystems/Engine/vendor/x64-linux/include>
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneSystems/Engine/Vane>
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneSystems/Engine/Vane/include>
)
target_compile_definitions("Sandbox" PRIVATE
  $<$<CONFIG:dbg>:DEBUG>
  $<$<CONFIG:dbg>:_DEBUG>
)
target_link_directories("Sandbox" PRIVATE
  $<$<CONFIG:dbg>:/home/wowvain/repos/VaneSystems/Engine/vendor/x64-linux/lib>
)
target_link_libraries("Sandbox"
  $<$<CONFIG:dbg>:Vane>
)
target_compile_options("Sandbox" PRIVATE
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:dbg>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL dbg)
  set_target_properties("Sandbox" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL rel)
  add_dependencies("Sandbox"
    "Vane"
  )
  set_target_properties("Sandbox" PROPERTIES
    OUTPUT_NAME "Sandbox"
    ARCHIVE_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneSystems/Engine/build/rel-linux-x64/Sandbox"
    LIBRARY_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneSystems/Engine/build/rel-linux-x64/Sandbox"
    RUNTIME_OUTPUT_DIRECTORY "/home/wowvain/repos/VaneSystems/Engine/build/rel-linux-x64/Sandbox"
  )
endif()
target_include_directories("Sandbox" PRIVATE
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneSystems/Engine/vendor/x64-linux/include>
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneSystems/Engine/Vane>
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneSystems/Engine/Vane/include>
)
target_compile_definitions("Sandbox" PRIVATE
  $<$<CONFIG:rel>:RELEASE>
  $<$<CONFIG:rel>:NDEBUG>
)
target_link_directories("Sandbox" PRIVATE
  $<$<CONFIG:rel>:/home/wowvain/repos/VaneSystems/Engine/vendor/x64-linux/lib>
)
target_link_libraries("Sandbox"
  $<$<CONFIG:rel>:Vane>
)
target_compile_options("Sandbox" PRIVATE
  $<$<AND:$<CONFIG:rel>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:rel>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:rel>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL rel)
  set_target_properties("Sandbox" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()