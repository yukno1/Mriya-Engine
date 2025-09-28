cmake_minimum_required(VERSION 3.20)
project(Miriya)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
file(GLOB_RECURSE MIRIYA_SOURCES
        "src/Miriya/*.cpp"
#         "${CMAKE_SOURCE_DIR}/Sandbox/src/Sandbox.cpp"
#        "vendor/stb_image/*.cpp"
#        "vendor/glm/glm/*.inl"
#        "vendor/ImGuizmo/ImGuizmo.cpp"
)

file(GLOB_RECURSE MIRIYA_HEADERS
        "src/Miriya/*.h"
        "include/*.h"
        "src/Miriya/Events/*.h"
#        "vendor/stb_image/*.h"
#        "vendor/glm/glm/*.hpp"
#        "vendor/ImGuizmo/ImGuizmo.h"
)

# Create the dynamic library
add_library(Miriya SHARED ${MIRIYA_SOURCES} ${MIRIYA_HEADERS})

add_compile_definitions(MIR_PLATFORM_WINDOWS)
add_compile_definitions(MIR_BUILD_DLL)

# Set include directories
#target_include_directories(Miriya
#        PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#        $<INSTALL_INTERFACE:include>
#        PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/src
#        ${CMAKE_SOURCE_DIR}/Miriya/vendor/spdlog/include
#)
target_include_directories(${PROJECT_NAME} PRIVATE
        src
        vendor/spdlog/include
#        ${IncludeDir_Box2D}
#        ${IncludeDir_filewatch}
#        ${IncludeDir_GLFW}
#        ${IncludeDir_Glad}
#        ${IncludeDir_ImGui}
#        ${IncludeDir_glm}
#        ${IncludeDir_stb_image}
#        ${IncludeDir_entt}
#        ${IncludeDir_mono}
#        ${IncludeDir_yaml_cpp}
#        ${IncludeDir_ImGuizmo}
#        ${IncludeDir_VulkanSDK}
)


#message("IncludeDir_VulkanSDK: ${IncludeDir_VulkanSDK}")
#
#target_link_libraries(${PROJECT_NAME} PRIVATE
#        box2d
#        glfw
#        glad
#        imgui
#        yaml-cpp
#        opengl32.lib
#        # ${Library_mono}
#)
#
#if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
#    target_link_libraries(${PROJECT_NAME} PRIVATE
#            ${Library_WinSock}
#            ${Library_WinMM}
#            ${Library_WinVersion}
#            ${Library_BCrypt}
#    )
#endif()

#target_compile_options(${PROJECT_NAME} PRIVATE
#        $<$<COMPILE_LANGUAGE:CXX>:/EHsc>
#)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DEBUG)
#    target_compile_options(${PROJECT_NAME} PRIVATE /Od /Zi)
#    target_link_libraries(${PROJECT_NAME} PRIVATE
#            ${Library_ShaderC_Debug}
#            ${Library_SPIRV_Cross_Debug}
#            ${Library_SPIRV_Cross_GLSL_Debug}
#    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_RELEASE)
#    target_compile_options(${PROJECT_NAME} PRIVATE /O2)
#    target_link_libraries(${PROJECT_NAME} PRIVATE
#            ${Library_ShaderC_Release}
#            ${Library_SPIRV_Cross_Release}
#            ${Library_SPIRV_Cross_GLSL_Release}
#    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DIST)
#    target_compile_options(${PROJECT_NAME} PRIVATE /O2)
#    target_link_libraries(${PROJECT_NAME} PRIVATE
#            ${Library_ShaderC_Release}
#            ${Library_SPIRV_Cross_Release}
#            ${Library_SPIRV_Cross_GLSL_Release}
#    )
endif()