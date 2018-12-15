cmake_minimum_required(VERSION 3.11)
project(firestorm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)
add_compile_definitions(DEBUG)

set(OpenGL_GL_PREFERENCE GLVND)
set(BOX2D_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)

if (WIN32)
    set(VULKAN_SDK_DIRECTORY "E:\\Dev\\VulkanSDK\\Windows\\1.1.92.1")
    include_directories(${VULKAN_SDK_DIRECTORY}\\Include)
    link_directories(${VULKAN_SDK_DIRECTORY}\\Lib)
endif(WIN32)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(external/spdlog)
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/Box2D/Box2D)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/texture.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/bg.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/tiles_spritesheet.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/p1_spritesheet.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
