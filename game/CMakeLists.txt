project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    )

set(SOURCES
    game.cpp
	)

# Create game executable target as usual
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  SDL2::SDL2
  SDL2_image::SDL2_image
  SDL2_ttf::SDL2_ttf
  SDL2_mixer::SDL2_mixer
  SDL2_net::SDL2_net
)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

###corelib
#target_link_libraries(${PROJECT_NAME} PRIVATE corelib)
#target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/core")

###SDL2pp
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2pp::SDL2pp)
