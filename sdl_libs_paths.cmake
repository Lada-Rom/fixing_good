if(WIN32 AND MINGW)
  message(STATUS "WIN32 AND MINGW")
  set(SDL2_DIR
      "D:\\Artem\\Desktop\\pet_prjs\\gamedev\\SDL2-2.26.3\\cmake")
  set(SDL2_image_DIR
      "D:\\Artem\\Desktop\\pet_prjs\\gamedev\\SDL2_image-2.6.3\\cmake")
  set(SDL2_ttf_DIR
      "D:\\Artem\\Desktop\\pet_prjs\\gamedev\\SDL2_ttf-2.20.2\\cmake")
  set(SDL2_mixer_DIR
      "D:\\Artem\\Desktop\\pet_prjs\\gamedev\\-\\cmake")
  set(SDL2_gfx_DIR
      "D:\\Artem\\Desktop\\pet_prjs\\gamedev\\-\\cmake")
  set(SDL2_net_DIR
      "D:\\Artem\\Desktop\\pet_prjs\\gamedev\\-\\cmake")
elseif(WIN32 AND MSVC)
  message(STATUS "WIN32 AND MSVC")
  set(SDL2_DIR
	"D:\\Projects\\LIBRARIES\\SDL2-devel-2.26.4-VC\\cmake")
  set(SDL2_image_DIR
	"D:\\Projects\\LIBRARIES\\SDL2_image-devel-2.6.3-VC\\cmake")
  set(SDL2_ttf_DIR
    "D:\\Projects\\LIBRARIES\\SDL2_ttf-devel-2.20.2-VC\\cmake")
  set(SDL2_mixer_DIR
    "D:\\Projects\\LIBRARIES\\SDL2_mixer-devel-2.6.3-VC\\cmake")
  set(SDL2_gfx_DIR
    "D:\\Projects\\LIBRARIES\\-\\cmake")
  set(SDL2_net_DIR
    "D:\\Projects\\LIBRARIES\\-\\cmake")
elseif(UNIX)
  # https://enccs.github.io/cmake-workshop/dependencies/
  find_package(PkgConfig REQUIRED)
  if(NOT PkgConfig_FOUND)
    message(FATAL_ERROR "PkgConfig not found")
  endif()
endif()
