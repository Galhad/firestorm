cmake_minimum_required(VERSION 3.12)
project(firestorm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(external/spdlog)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/texture.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/bg.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/tiles_spritesheet.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ./resources/p1_spritesheet.png DESTINATION ${CMAKE_BINARY_DIR}/resources)
