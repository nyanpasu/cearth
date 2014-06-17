#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include "login.h"

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

int main(int argc, char **argv)
{
        char fail = 0;
        fail += SDL_Init(SDL_INIT_EVERYTHING);
        fail += SDLNet_Init();

        if (fail) {
                printf("Something could not initialize properly.\n");
                return 0;
        }

        return 0;
}
