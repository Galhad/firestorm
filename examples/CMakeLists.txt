LIST(APPEND INCLUDE_DIRECTORIES "./")
LIST(APPEND INCLUDE_DIRECTORIES "../../src")
LIST(APPEND INCLUDE_DIRECTORIES "../../external/stb")
LIST(APPEND INCLUDE_DIRECTORIES "../../external/spdlog/include")
LIST(APPEND INCLUDE_DIRECTORIES "../../external/glm")
LIST(APPEND INCLUDE_DIRECTORIES "../../external/glfw/include")
LIST(APPEND INCLUDE_DIRECTORIES "../../external/Box2D/Box2D")

LIST(APPEND LINK_LIBRARIES "firestorm")
LIST(APPEND LINK_LIBRARIES "glfw")
LIST(APPEND LINK_LIBRARIES "Box2D")

if (WIN32)
    LIST(APPEND LINK_LIBRARIES "vulkan-1")
else (WIN32)
    LIST(APPEND LINK_LIBRARIES "vulkan")
    LIST(APPEND LINK_LIBRARIES "pthread")
endif (WIN32)


set(STB_DIRECTORY ../../external/stb)
file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

add_subdirectory(./01SimpleApplication)
add_subdirectory(./02Physics)