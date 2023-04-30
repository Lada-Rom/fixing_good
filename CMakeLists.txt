cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(fixing_good LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
# main dependencies: SDL2, SDL2-image, SDL2-mixer, SDL2-ttf, SDL2-net, SDL2pp
add_subdirectory(thirdparty)
# own functionality for the game & the designer that isn't presented in 3rdparties libs
add_subdirectory(core)
# custom designer for setting collision areas for objects
add_subdirectory(designer)
# game
add_subdirectory(game)


