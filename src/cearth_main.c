#include <stdio.h>
#include <regex.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include <curl/curl.h>

#include "cearth_utils.h"
#include "cearth_config.h"
#include "cearth_login.h"
#include "cearth_version.h"

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

int main(int argc, const char **argv)
{
        /* TODO Use getopt to handle parsing. */
        if (argc > 1) {
                if (strcmp(argv[1],"--version") + strcmp(argv[1],"-v")== 0) {
                        utils_print_ver();
                        return 0;
                }
        } else {
                printf("Usage: %s <username>\n", argv[0]);
                return 0;
        }

        const char *arg_user = argv[1];

        /* NOTE: Lines that are commented out are prototypes */
        /* Initialize libraries and set working dir to ~/.cearth */
        if (utils_home_init() == 0)
                exit(EXIT_FAILURE);

        utils_lib_init();
        /* Load resources */
        cearth_resourcedb *resdb;
        resdb = resourcedb_open();
        /* Login into website and obtain token. */
        cearth_logindb *logdb;
        char *cookie, *token;
        logdb = logindb_open();
        int check = logindb_usercheck(logdb, arg_user);
        switch(check) {
                case 0:
                        logindb_useradd(logdb, arg_user);
                        break;
                case 1:
                        loginhttp_cookieget(logdb, arg_user);
                case 2:
                        token = logindb_tokenget(logdb, arg_user);
                        break;
                default:
                        break;
        }
        logindb_close(logindb);
        /* Attempt login into game servers */
        cearth_ctx *ctx;
        ctx = cearthctx_new();
        cearthctx_connect(ctx, token);
        /* Set up screen and gui elements */
        cearth_screen *scr cearthscreen_new();
        cearth_gui *gui = cearthgui_new();
        cearthgui_bind(gui, ctx);
        cearthscreen_bindsdl(scr, g_renderer);
        cearthscreen_bindgui(scr, gui);
        cearthscreen_start(scr);
        /* Character selection */
        /* Game loop */
        /* Disconnect, free memory and shutdown gracefully. */
        cearthctx_disconnect(ctx);
        cearthgui_free(gui);
        cearthscreen_stop(scr);
        cearthscreen_free(scr);

        utils_lib_deinit();

        return 0;
}
