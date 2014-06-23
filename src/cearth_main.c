#include <stdio.h>
#include <regex.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include <curl/curl.h>

#include "utils.h"
#include "config.h"
#include "login.h"
#include "version.h"

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

void print_ver();
void initialize_libs();

int main(int argc, const char **argv)
{
        /* TODO Use getopt to handle parsing. */
        if (argc > 1) {
                if (strcmp(argv[1],"--version") + strcmp(argv[1],"-v")== 0) {
                        print_ver();
                        return 0;
                }
        } else {
                printf("Usage: %s <username>\n", argv[0]);
                return 0;
        }
        const char *arg_user = argv[1];
        if (util_home_init() == 0)
                exit(EXIT_FAILURE);
        initialize_libs();

        /* TEST: Logging into havenandhearth.com */
        struct cearth_logindb db;
        logindb_open(&db);
        loginhttp_getcookie(arg_user);
        logindb_close(&db);

        return 0;
}

void
print_ver()
{
        printf("Cearth: The open source Haven and Hearth client. Ver. %d.%d.%d\n",
                        VERSION_MAJOR,
                        VERSION_MINOR,
                        VERSION_PATCH);
}

void
initialize_libs()
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
