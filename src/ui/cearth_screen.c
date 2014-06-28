#include "cearth_screen.h"


cearth_screen *
cearthscreen_new()
{
        cearth_screen *scr;
        scr = calloc(1, sizeof(cearth_screen));

        return scr;
}

void
cearthscreen_bindsdl(cearth_screen *s, SDL_Renderer *r)
{
        s->m_ren = r;
}

void
cearthscreen_bindgui(cearth_screen *s, cearth_gui *g)
{
        s->m_ren = g;
}

void
cearthscreen_start(cearth_screen *)
{
}
