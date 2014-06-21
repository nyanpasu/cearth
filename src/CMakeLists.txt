CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
PROJECT(cearth)

CONFIGURE_FILE (
          "version.h.in"
          "version.h"
          )
# Add the binary tree to the search path for include files
# to find version.h
include_directories("${PROJECT_BINARY_DIR}")
 
ADD_EXECUTABLE(${PROJECT_NAME}
        main.c
        utils.c
        #login.c
        )
 
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_net REQUIRED SDL2_net)
PKG_SEARCH_MODULE(SDL2_image REQUIRED SDL2_image)
PKG_SEARCH_MODULE(LIBCURL REQUIRED libcurl)
#FIND_PACKAGE(SDL_image)
#FIND_PACKAGE(SDL_net)

INCLUDE_DIRECTORIES(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_image_INCLUDE_DIRS}
        ${SDL2_net_INCLUDE_DIRS}
        )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_image_LIBRARIES}
        ${SDL2_net_LIBRARIES}
        ${LIBCURL_LIBRARIES}
        )
