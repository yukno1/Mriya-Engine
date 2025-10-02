cmake_minimum_required(VERSION 3.20)
project(Miriya)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif ()

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Dependencies.cmake in modules folder
#include(Dependencies)

set(CMAKE_GENERATOR_PLATFORM x64)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Dependencies
#add_subdirectory(Miriya/vendor/Box2D)
#add_subdirectory(Miriya/vendor/GLFW)
add_subdirectory(Miriya/vendor/GLAD)
add_subdirectory(Miriya/vendor/imgui)
#add_subdirectory(Miriya/vendor/yaml-cpp)

# core
add_subdirectory(Miriya)
# Tools
# add_subdirectory(Hazelnut)
# Misc
add_subdirectory(Sandbox)



