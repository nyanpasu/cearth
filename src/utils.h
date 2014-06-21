#ifndef _UTILS_H_
#define _UTILS_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"

/* Checks if cearth_config_dir exists
 * Makes it if doesn't
 * Changes active dir to the cearth_config_dir
 * return 1 on success, 0 on failure. */
int util_home_init();

#endif
