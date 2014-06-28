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

void g_login     (cearth_logindb * db, const char *user, char **cookie, char **token);
void g_getopt    (int, const char **);
void g_sdlcreate (SDL_Window *, SDL_Renderer *);
void g_sdldestroy(SDL_Window *, SDL_Renderer *);
void g_init      ();

int window_height = 600;
int window_width = 800;

SDL_Renderer *g_renderer;
SDL_Window *g_window;

int main(int argc, const char **argv)
{
        g_getopt(argc, argv);

        /* Initialize libraries and set working dir to ~/.cearth */
        g_init();

        /* Display SDL shit. */
        g_sdlcreate(g_window, g_renderer);

        /* Load resources */
        cearth_resourcedb *resdb;
        resdb = resourcedb_open();

        /* Set up screen and gui elements */
        cearth_screen *scr = cearthscreen_new();
        cearth_gui *gui = cearthgui_new();

        cearthscreen_bindsdl(scr, g_renderer);
        cearthscreen_bindgui(scr, gui);

        g_login(gui);

        /* Begin server context */
        cearth_ctx *ctx = cearthctx_new();
        cearthctx_guibind(ctx, gui);
        cearthctx_setconn(ctx, arg_user, token);
        cearthctx_startread(ctx);
        cearthctx_startwrite(ctx);
        cearthctx_startprcs(ctx);

        cearthscreen_start(scr);

        /* Character selection */
        cearthgui_clear(gui);
        g_charsel(gui);

        /* Game loop */
        cearthgui_clear(gui);
        cearthctx_guibind(ctx, gui);

        /* Disconnect, free memory and shutdown gracefully. */
        cearthctx_disconnect(ctx);
        cearthscreen_stop(scr);
        cearthgui_clear(gui);
        cearthgui_free(gui);
        cearthscreen_free(scr);

        /* DEPRECIATED */
        // /* Login into website and obtain token. */
        // char *cookie, *token;
        // cearth_logindb *logdb = logindb_open();
        // g_login_old(logdb, arg_user, &cookie, &token);

        // logindb_close(logdb);

        g_sdldestroy(g_window, g_renderer);
        utils_lib_deinit();

        return 0;
}


void
g_sdlcreate(SDL_Window *w, SDL_Renderer *r)
{
        g_window = SDL_CreateWindow("Cearth",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window_width,
                                     window_height,
                                     0);
        g_renderer = SDL_CreateRenderer(g_window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED);
}

void
g_sdldestroy(SDL_Window *w, SDL_Renderer *r)
{
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
}

void
g_init()
{
        if (utils_home_init() == 0)
                exit(EXIT_FAILURE);
        utils_lib_init();
}

void
g_getopt(int argc, const char **argv)
{
        /* TODO Use getopt to handle parsing. */
        if (argc > 1) {
                if (strcmp(argv[1],"--version") + strcmp(argv[1],"-v")== 0) {
                        utils_ver_print();
                        return 0;
                }
        }
}

void
g_login_old(cearth_logindb *db, const char *user, char **cookie, char **token)
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
