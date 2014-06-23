#include "cearth_utils.h"

int
util_home_init()
{
        int success = 0;
        char path[128];
        strcpy(path, getenv("HOME"));
        strcat(path, cearth_config_dir);

        mkdir(path, 0755);
        success = chdir(path);

        if (success == -1) {
                fprintf(stderr, "Error: Failed to open and create config dir.\n");
                return 0;
        }

        return 1;
}
