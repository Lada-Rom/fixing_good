project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    )

set(SOURCES
    main.cpp)

if(MYGAME_VENDORED)
    add_subdirectory(${SUB_DIR_PATH} EXCLUDE_FROM_ALL)
else()
    if(NOT UNIX)
      find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    elseif(UNIX)
      # ask pkg-config to find the *** library and prepare an imported target
      pkg_search_module(SDL2 REQUIRED SDL2 IMPORTED_TARGET)
    endif()
    # 1. Look for a SDL2 package,
    # 2. Look for the SDL2maincomponent and
    # 3. DO NOT fail when SDL2main is not available
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
endif()

# Create your game executable target as usual
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# custom command add imported libs to project-target
PrjAddLibs(${PROJECT_NAME})
