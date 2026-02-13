cmake_minimum_required(VERSION 4.2.3)
project(Miriya)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

#option(BOX2D_BUILD_UNIT_TESTS "Build the Box2D unit tests" OFF)
#option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF)
#option(BOX2D_BUILD_DOCS "Build the Box2D documentation" OFF)
#option(BOX2D_USER_SETTINGS "Override Box2D settings with b2UserSettings.h" OFF)
#option(BUILD_SHARED_LIBS "Build Box2D as a shared library" ON)



# Collect source files
file(GLOB_RECURSE MIRIYA_SOURCES
        "src/*.cpp"
        "vendor/stb_image/*.cpp"
        "vendor/glm/glm/*.inl"
#        "vendor/ImGuizmo/ImGuizmo.cpp"
)

file(GLOB_RECURSE MIRIYA_HEADERS
        "src/*.h"
        "src/Events/*h"
        "include/*.h"
        "vendor/stb_image/*.h"
        "vendor/glm/glm/*.hpp"
#        "vendor/ImGuizmo/ImGuizmo.h"
)

# Create the static library
add_library(Miriya STATIC ${MIRIYA_SOURCES} ${MIRIYA_HEADERS})

target_precompile_headers(${PROJECT_NAME} PUBLIC "src/mirpch.h")

add_compile_definitions(MIR_PLATFORM_WINDOWS)
add_compile_definitions(MIR_BUILD_DLL)
add_compile_definitions(MIR_ENABLE_ASSERTS)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/vendor/GLFW/lib/glfw3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

#target_compile_definitions(${PROJECT_NAME} PRIVATE
#        _CRT_SECURE_NO_WARNINGS
#        GLFW_INCLUDE_NONE
#)

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
        vendor
        vendor/GLFW
        ${IncludeDir_Glad}
#        vendor/GLAD/include
#        ${IncludeDir_Box2D}
#        ${IncludeDir_filewatch}
        ${IncludeDir_ImGui}
#        ${IncludeDir_glm}
        vendor/glm
        vendor/stb_image
#        ${IncludeDir_entt}
#        ${IncludeDir_mono}
#        ${IncludeDir_yaml_cpp}
#        ${IncludeDir_ImGuizmo}
#        ${IncludeDir_VulkanSDK}
)

#message("IncludeDir_VulkanSDK: ${IncludeDir_VulkanSDK}")

target_link_libraries(${PROJECT_NAME} PRIVATE
#        box2d
        glad
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/lib/libglfw3dll.a  # use prebuilt
        imgui
#        yaml-cpp
        # ${Library_mono}
)


if(MSVC)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_WinSock}
                ${Library_WinMM}
                ${Library_WinVersion}
                ${Library_BCrypt}
                opengl32.lib
        )
    endif()

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:/EHsc>
    )

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DEBUG)
        target_compile_options(${PROJECT_NAME} PRIVATE /Od /Zi)
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_ShaderC_Debug}
                ${Library_SPIRV_Cross_Debug}
                ${Library_SPIRV_Cross_GLSL_Debug}
        )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_RELEASE)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_ShaderC_Release}
                ${Library_SPIRV_Cross_Release}
                ${Library_SPIRV_Cross_GLSL_Release}
        )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DIST)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_ShaderC_Release}
                ${Library_SPIRV_Cross_Release}
                ${Library_SPIRV_Cross_GLSL_Release}
        )
    endif()
else ()

    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_WinSock}
                ${Library_WinMM}
                ${Library_WinVersion}
                ${Library_BCrypt}
                opengl32.lib
        )
    endif()

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DEBUG)
        #    target_link_libraries(${PROJECT_NAME} PRIVATE
        #            ${Library_ShaderC_Debug}
        #            ${Library_SPIRV_Cross_Debug}
        #            ${Library_SPIRV_Cross_GLSL_Debug}
        #    )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_RELEASE)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        #    target_link_libraries(${PROJECT_NAME} PRIVATE
        #            ${Library_ShaderC_Release}
        #            ${Library_SPIRV_Cross_Release}
        #            ${Library_SPIRV_Cross_GLSL_Release}
        #    )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DIST)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        #    target_link_libraries(${PROJECT_NAME} PRIVATE
        #            ${Library_ShaderC_Release}
        #            ${Library_SPIRV_Cross_Release}
        #            ${Library_SPIRV_Cross_GLSL_Release}
        #    )
    endif()

endif ()