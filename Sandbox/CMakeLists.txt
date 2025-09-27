cmake_minimum_required(VERSION 3.20)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
#        ${CMAKE_SOURCE_DIR}/Miriya/vendor/spdlog/include
        ${CMAKE_SOURCE_DIR}/Miriya/src
        ${CMAKE_SOURCE_DIR}/Miriya/include
#        ${CMAKE_SOURCE_DIR}/Miriya/vendor
#        ${CMAKE_SOURCE_DIR}/Miriya/vendor/imgui
#        ${CMAKE_SOURCE_DIR}/Miriya/vendor/Glad
#        ${IncludeDir_glm}
#        ${IncludeDir_entt}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Miriya
)

add_compile_definitions(MIR_PLATFORM_WINDOWS)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            MIR_DEBUG
    )
endif()


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


