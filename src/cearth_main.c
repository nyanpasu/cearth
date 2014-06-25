#include <stdio.h>
#include <regex.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include <curl/curl.h>

#include "config/cearth_config.h"
#include "utils/cearth_utils.h"
#include "net/cearth_login.h"

void g_login(const char *user);

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
        // /* Load resources */
        // cearth_resourcedb *resdb;
        // resdb = resourcedb_open();

        /* Login into website and obtain token. */
        cearth_logindb *logdb = logindb_open();
        char *cookie, *token;
        g_login(db, arg_user, cookie, token);
        /* TEST */
        printf("Token: %s\n", token);
        logindb_close(logdb);
        //////////////////////  
        //  UNIMPLEMENTED
        ////////////////////// 
        //  /* Attempt login into game servers */
        //  cearth_ctx *ctx;
        //  ctx = cearthctx_new();
        //  cearthctx_connect(ctx, token);
        //  /* Set up screen and gui elements */
        //  cearth_screen *scr cearthscreen_new();
        //  cearth_gui *gui = cearthgui_new();
        //  cearthgui_bind(gui, ctx);
        //  cearthscreen_bindsdl(scr, g_renderer);
        //  cearthscreen_bindgui(scr, gui);
        //  cearthscreen_start(scr);
        //  /* Character selection */
        //  /* Game loop */
        //  /* Disconnect, free memory and shutdown gracefully. */
        //  cearthctx_disconnect(ctx);
        //  cearthgui_free(gui);
        //  cearthscreen_stop(scr);
        //  cearthscreen_free(scr);

        utils_lib_deinit();

        return 0;
}


void
g_login(cearth_logindb *db, const char *user, char *cookie, char *token)
{
        int check = logindb_usercheck(db, arg_user);
        switch(check) {
                case 0:
                        printf("1\n");
                        logindb_useradd(db, user);
                case 1:
                        printf("2\n");
                        loginhttp_cookieget(db, user);
                case 2:
                        printf("3\n");
                        cookie = logindb_cookieget(db, user);
                        loginhttp_tokenget(db, user);
                case 3:
                        printf("4\n");
                        cookie = logindb_cookieget(db, user);
                        token  = logindb_tokenget(db, user);
                        break;
                default:
                        break;
        }

}
