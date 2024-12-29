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


add_subdirectory(thirdparty/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL EXCLUDE_FROM_ALL)

add_executable(
    ${PROJECT_NAME}
    
    src/app.cpp
    #src/mistral_game.cpp

    include/actor.hpp
    include/player.hpp
	
    include/drawable.hpp
	include/moveable.hpp
	
	include/vector2d.hpp
)

set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${RESOURCES_PATH})

file(COPY ${RESOURCES_PATH} DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
