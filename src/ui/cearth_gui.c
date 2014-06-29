#include "cearth_gui.h"

cearth_gui *
cearthgui_new(void)
{
        cearth_gui *g;
        g = calloc(1, sizeof(cearth_gui));

        g->i = calloc(1, sizeof(cearth_ui));
        g->c = 0;

        return g;
}
