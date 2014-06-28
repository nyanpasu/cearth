#ifndef _CEARTH_SCREEN
#define _CEARTH_SCREEN

#include <SDL2/SDL.h>

#include "cearth_gui.h"

/**
 * Contains the necessary elements for rendering and
 * binds together several modules of the cearth project into.
 * Essentially, a neat manager that allows communication between
 * the respective modules.
 */
typedef struct
{
        SDL_Renderer *m_ren;
        cearth_gui *m_gui;
} cearth_screen;

/**
 * Initializes a screen struct and prepares it for use.
 */
cearth_screen *cearthscreen_new();

void cearthscreen_bindsdl(cearth_screen *, SDL_Renderer *);
void cearthscreen_bindgui(cearth_screen *, cearth_gui *);

/**
 * Separates into a new thread that manages the modules it's assigned.
 * NOTE: At this point, bindsdl and bindgui must be called.
 * UNIMPLEMENTED
 */
void cearthscreen_start(cearth_screen *);

#endif //#ifndef _CEARTH_SCREEN
