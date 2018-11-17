file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

set(STB_DIRECTORY ../external/stb)
set(SPDLOG_DIRECTORY ../external/spdlog/include)

file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")
file(GLOB_RECURSE SPDLOG_HEADERS "${SPDLOG_DIRECTORY}/*.h")

add_library(firestorm ${SOURCES} ${STB_HEADERS} ${SPD_HEADERS})

target_include_directories(firestorm PRIVATE ./ ${STB_DIRECTORY} ${SPD_DIRECTORY})
