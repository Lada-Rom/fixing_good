# MUST HAVE 3.19 or higher version
# check https://cmake.org/cmake/help/latest/module/FindSDL.html#imported-targets
cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 11)
project(fixing_good)

# Create an option to switch between a system sdl library and a vendored sdl library
option(MYGAME_VENDORED "Use vendored libraries" OFF)


# import path to sdl libs
include(sdl_libs_paths.cmake)
# import function PrjAddLibs
include(utils.cmake)


add_subdirectory(core)
add_subdirectory(designer)
add_subdirectory(game)
