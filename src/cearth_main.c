#include <stdio.h>
#include <regex.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include <curl/curl.h>

#include "config/cearth_config.h"
#include "utils/cearth_utils.h"
#include "res/cearth_resource.h"
#include "ui/cearth_screen.h"
#include "ui/cearth_gui.h"
#include "net/cearth_login.h"
#include "net/cearth_ctx.h"

void g_login(cearth_logindb * db, const char *user, char **cookie, char **token);

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

int main(int argc, const char **argv)
{
        /* TODO Use getopt to handle parsing. */
        if (argc > 1) {
                if (strcmp(argv[1],"--version") + strcmp(argv[1],"-v")== 0) {
                        utils_ver_print();
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

        /* Display SDL shit. */
        g_window = SDL_CreateWindow("Cearth",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window_width,
                                     window_height,
                                     0);
        g_renderer = SDL_CreateRenderer(g_window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED);

        /* Load resources */
        cearth_resourcedb *resdb;
        resdb = resourcedb_open();

        /* Set up screen and gui elements */
        cearth_screen *scr = cearthscreen_new();
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

        /* Login into website and obtain token. */
        char *cookie, *token;
        cearth_logindb *logdb = logindb_open();
        g_login(logdb, arg_user, &cookie, &token);

        /* Attempt login into game servers */
        cearth_ctx *ctx = cearthctx_new();
        cearthctx_connect(ctx, arg_user, token);

        logindb_close(logdb);
        utils_lib_deinit();

        return 0;
}


void
g_login(cearth_logindb *db, const char *user, char **cookie, char **token)
{
        int check = logindb_usercheck(db, user);
        switch(check) {
                case 0:
                        logindb_useradd(db, user);
                case 1:
                        loginhttp_cookieget(db, user);
                case 2:
                        *cookie = logindb_cookieget(db, user);
                        loginhttp_tokenget(db, user);
                case 3:
                        *cookie = logindb_cookieget(db, user);
                        *token  = logindb_tokenget(db, user);
                        break;
                default:
                        break;
        }
}
