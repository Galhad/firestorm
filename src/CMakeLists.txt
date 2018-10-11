include_directories(./)

file(GLOB_RECURSE SOURCES "*.cpp")
add_library(firestorm ${SOURCES})
