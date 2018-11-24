file(GLOB_RECURSE SOURCES "*.cpp")

set(STB_DIRECTORY ../../external/stb)
file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

set(STB_DIRECTORY ../../external/stb)
set(SPDLOG_DIRECTORY ../../external/spdlog/include)
set(GLM_DIRECTORY ../external/glm)

file(GLOB_RECURSE STB_HEADERS "${STB_DIRECTORY}/*.h")

add_executable(01SimpleApplication ${SOURCES} ${STB_HEADERS} )

target_link_libraries(01SimpleApplication firestorm glfw vulkan pthread)
target_include_directories(01SimpleApplication PRIVATE ./ ../../src ${STB_DIRECTORY} ${SPDLOG_DIRECTORY} ${GLM_DIRECTORY})
