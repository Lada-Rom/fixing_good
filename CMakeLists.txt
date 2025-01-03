cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(fixing_good LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin.rel)

# Use this snippet *after* PROJECT(xxx):
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE ${CMAKE_BINARY_DIR}/install)
endif()


add_executable(
    ${PROJECT_NAME}
    
    src/app.cpp
    #src/mistral_game.cpp

    include/actor.hpp
    include/player.hpp
	
    include/drawable.hpp
	include/moveable.hpp
	
	include/vector2d.hpp
    include/rect.hpp
    
    include/types.hpp
    include/utils.hpp
)

# INCLUDE headers-only
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# COPY resources (images, musics, etc) to destination
set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources)
target_include_directories(${PROJECT_NAME} PRIVATE ${RESOURCES_PATH})
file(COPY ${RESOURCES_PATH} DESTINATION ${CMAKE_BINARY_DIR})

# ADD dependencies
add_subdirectory(thirdparty/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

add_subdirectory(thirdparty/catch2 ${CMAKE_CURRENT_BINARY_DIR}/catch2 EXCLUDE_FROM_ALL)
add_subdirectory(tests)
# target_link_libraries(tests PRIVATE Catch2::Catch2)
