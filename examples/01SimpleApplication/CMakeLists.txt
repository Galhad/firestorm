file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(01SimpleApplication ${SOURCES} ${STB_HEADERS})

target_link_libraries(01SimpleApplication ${LINK_LIBRARIES})
target_include_directories(01SimpleApplication PRIVATE ${INCLUDE_DIRECTORIES})
