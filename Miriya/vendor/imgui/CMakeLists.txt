cmake_minimum_required(VERSION 3.20)
project(ImGui)

set(IMGUI_DIR "${PROJECT_SOURCE_DIR}")
file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp) # ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} "${CMAKE_SOURCE_DIR}/Miriya/vendor")
