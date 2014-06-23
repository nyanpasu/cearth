#ifndef _UTILS_H_
#define _UTILS_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <curl/curl.h>

#include "../config/cearth_config.h"
#include "cearth_version.h"

/* Checks if cearth_config_dir exists
 * Makes it if doesn't
 * Changes active dir to the cearth_config_dir
 * return 1 on success, 0 on failure. */
int utils_home_init();
void utils_lib_init();
void utils_lib_deinit();
void utils_ver_print();

#endif
