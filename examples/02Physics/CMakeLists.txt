file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(02Physics ${SOURCES} ${STB_HEADERS})

target_link_libraries(02Physics ${LINK_LIBRARIES})
target_include_directories(02Physics PRIVATE ${INCLUDE_DIRECTORIES})
