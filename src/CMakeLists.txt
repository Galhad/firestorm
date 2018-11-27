file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

set(STB_DIRECTORY ../external/stb)
set(SPDLOG_DIRECTORY ../external/spdlog/include)
set(GLM_DIRECTORY ../external/glm)
set(GLFW_DIRECTORY ../external/glfw)
set(BOX2D_DIRECTORY ../external/Box2D/Box2D)

file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

add_library(firestorm ${SOURCES} ${STB_HEADERS} )

target_include_directories(firestorm PRIVATE ./ ${STB_DIRECTORY} ${SPDLOG_DIRECTORY} ${GLM_DIRECTORY} ${BOX2D_DIRECTORY} ${GLFW_DIRECTORY})
