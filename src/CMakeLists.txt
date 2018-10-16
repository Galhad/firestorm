file(GLOB_RECURSE SOURCES "*.cpp")

set(STB_DIRECTORY ../external/stb)
file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

add_library(firestorm ${SOURCES} ${STB_HEADERS})

target_include_directories(firestorm PRIVATE ./ ${STB_DIRECTORY})
