project(corelib LANGUAGES CXX)
add_library(${PROJECT_NAME})
add_subdirectory(wrappers)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  SDL2::SDL2
  SDL2_image::SDL2_image
  #SDL2_ttf::SDL2_ttf
  #SDL2_mixer::SDL2_mixer
  #SDL2_net::SDL2_net
)
if(WIN32 AND MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
