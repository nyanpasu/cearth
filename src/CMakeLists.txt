CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
PROJECT(cearth)

CONFIGURE_FILE (
          "version.h.in"
          "version.h"
          )
# Add the binary tree to the search path for include files
# to find version.h
include_directories("${PROJECT_BINARY_DIR}")
 
ADD_EXECUTABLE(${PROJECT_NAME} main.c login.c)
 
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
FIND_PACKAGE(SDL_image)
FIND_PACKAGE(SDL_net)

INCLUDE_DIRECTORIES(
        ${SDL2_INCLUDE_DIRS}
        ${SDLIMAGE_INCLUDE_DIRS}
        ${SDLNET_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL_IMAGE_LIBRARIES}
        ${SDL_NET_LIBRARIES})