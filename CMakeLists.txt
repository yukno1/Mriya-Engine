cmake_minimum_required(VERSION 3.20)
project(Miriya)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

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
#add_subdirectory(Hazel/vendor/Box2D)
#add_subdirectory(Hazel/vendor/GLFW)
#add_subdirectory(Hazel/vendor/Glad)
#add_subdirectory(Hazel/vendor/imgui)
#add_subdirectory(Hazel/vendor/yaml-cpp)


# core
add_subdirectory(Miriya)
# Tools
# add_subdirectory(Hazelnut)
# Misc
add_subdirectory(Sandbox)



