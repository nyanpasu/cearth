CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
PROJECT(cearth)

CONFIGURE_FILE (
          "cearth_version.h.in"
          "cearth_version.h"
          )

# Add the binary tree to the search path for include files
# to find version.h
include_directories("${PROJECT_BINARY_DIR}")
 
ADD_EXECUTABLE(${PROJECT_NAME}
               cearth_main.c
           net/cearth_login.c
           net/cearth_ctx.c
           net/cearth_network.c
           res/cearth_resourcedb.c
          game/cearth_object.c
          game/cearth_widget.c
          game/cearth_game.c
         utils/cearth_utils.c
            ui/cearth_gui.c
            ui/cearth_screen.c
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
