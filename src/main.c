#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include "login.h"
#include "config.h"
#include "version.h"

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

void print_ver();
void initialize_libs();

int main(void)
{
        print_ver();
        initialize_libs();

        IPaddress ipaddress;
        SDLNet_ResolveHost(&ipaddress, haven_authserv, 1871);

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
                printf("Something could not initialize properly.\n");
                exit(0);
        }
}
