## https://github.com/google/googletest/blob/main/docs/quickstart-cmake.md
include(FetchContent)

### TODO
### SDL2 -> SDL3 soon ... ###
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG ac13ca9ab691e13e8eebe9684740ddcb0d716203
  OVERRIDE_FIND_PACKAGE
)
#FetchContent_MakeAvailable(SDL2)
# The following will automatically forward through to FetchContent_MakeAvailable()
find_package(SDL2)

### TODO
### SDL2_image -> SDL3_image soon ... ###
FetchContent_Declare(
  SDL2_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG d3c6d5963dbe438bcae0e2b6f3d7cfea23d02829
  OVERRIDE_FIND_PACKAGE
)
# START ADDITION
set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS TRUE)
# END ADDITION
#FetchContent_MakeAvailable(SDL2_image)
find_package(SDL2_image)

### TODO
### SDL2_ttf -> SDL3_ttf soon ... ###
FetchContent_Declare(
  SDL2_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG 89d1692fd8fe91a679bb943d377bfbd709b52c23
  OVERRIDE_FIND_PACKAGE
)
# START ADDITION
set(SDL2TTF_VENDORED ON)
set(SDL2TTF_INSTALL OFF)
set(BUILD_SHARED_LIBS TRUE)
# END ADDITION
#FetchContent_MakeAvailable(SDL2_ttf)
find_package(SDL2_ttf)

### TODO
### SDL2_mixer -> SDL3_mixer soon ... ###
FetchContent_Declare(
  SDL2_mixer
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
  GIT_TAG 6103316427a8479e5027e41ab9948bebfc1c3c19
  OVERRIDE_FIND_PACKAGE
)
set(SDL2MIXER_VENDORED ON)
set(SDL2MIXER_INSTALL OFF)
#linker error on Windows + MinGW. Cannot link FLAC because of "undefined reference __stack_chk_fail()"
if(WIN32 AND MINGW)
	add_compile_options(-fno-stack-protector)
    set(WITH_STACK_PROTECTOR OFF CACHE BOOL "" FORCE)
endif()
set(BUILD_SHARED_LIBS TRUE)
#FetchContent_MakeAvailable(SDL2_mixer)
find_package(SDL2_mixer)

### TODO
### SDL2_net -> SDL3_net soon ... ###
FetchContent_Declare(
  SDL2_net
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_net.git
  GIT_TAG 669e75b84632e2c6cc5c65974ec9e28052cb7a4e
  OVERRIDE_FIND_PACKAGE
)
set(SDL2NET_INSTALL OFF)
set(BUILD_SHARED_LIBS TRUE)
#FetchContent_MakeAvailable(SDL2_mixer)
find_package(SDL2_net)

### SDL2pp ###
FetchContent_Declare(
  SDL2pp
  GIT_REPOSITORY https://github.com/libSDL2pp/libSDL2pp.git
  GIT_TAG cc198c9a5657048bee67ece82de620b2d5661084
)
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
set(SDL2PP_WITH_MIXER YES)
FetchContent_MakeAvailable(SDL2pp)
