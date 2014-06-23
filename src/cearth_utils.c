#include "cearth_utils.h"

int
utils_home_init()
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

void
utils_print_ver()
{
        printf("Cearth: The open source Haven and Hearth client. Ver. %d.%d.%d\n",
                        VERSION_MAJOR,
                        VERSION_MINOR,
                        VERSION_PATCH);
}

void
utils_lib_init()
{
        char fail = 0;

        fail += SDL_Init(SDL_INIT_EVERYTHING);
        fail += SDLNet_Init();

        if (fail) {
                fprintf(stderr, "An SDL library failed to initialize properly.\n");
                exit(EXIT_FAILURE);
        }

        curl_global_init(CURL_GLOBAL_ALL);
}
