file(GLOB_RECURSE SOURCES "*.cpp")

set(STB_DIRECTORY ../../external/stb)
file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

set(STB_DIRECTORY ../../external/stb)
set(SPDLOG_DIRECTORY ../../external/spdlog/include)
set(GLM_DIRECTORY ../external/glm)
set(GLFW_DIRECTORY ../external/glfw)
set(BOX2D_DIRECTORY ../external/Box2D/Box2D)

file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

add_executable(02Physics ${SOURCES} ${STB_HEADERS} )

target_link_libraries(02Physics firestorm glfw vulkan Box2D pthread)
target_include_directories(02Physics PRIVATE ./ ../../src ${STB_DIRECTORY} ${SPDLOG_DIRECTORY} ${GLM_DIRECTORY} ${GLFW_DIRECTORY} ${BOX2D_DIRECTORY})
