project(corelib LANGUAGES CXX)
add_library(${PROJECT_NAME})
add_subdirectory(wrappers)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
PrjAddLibs(${PROJECT_NAME})
