#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <openssl/ssl.h>

#include "login.h"
#include "config.h"

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

void print_ver();
void initialize_libs();

int main(int argc, char **argv)
{
        print_ver();
        initialize_libs();

        SSL_CTX *ctx = SSL_CTX_new(SSLv3_method());

        if (ctx)
        {
                printf("werkd.\n");
        }

        SSL_CTX_free(ctx);

        return 0;
}

void
print_ver()
{
        printf("Cearth: The open source Haven and Hearth client. Ver. %d.%d.%d\n",
                        @CEARTH_VERSION_MAJOR@,
                        @CEARTH_VERSION_MINOR@,
                        @CEARTH_VERSION_PATCH@);
}

void
initialize_libs()
{
        char fail = 0;

        SSL_library_init();
        fail += SDL_Init(SDL_INIT_EVERYTHING);
        fail += SDLNet_Init();

        if (fail) {
                printf("Something could not initialize properly.\n");
                exit(0);
        }
}
