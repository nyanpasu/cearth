#ifndef _CEARTH_GUI
#define _CEARTH_GUI
/**
 * FILE SUMMARY:
 * Contains the struct definition for cearth_gui
 * AND the modules cearth_gui can utilize to actually not
 * be an useless struct.
 * Use it with cearth_screen, which actually does the reading
 * and rendering.
 */

typedef struct
{
} cearth_ui;

/**
 * Contains an array of pointers to various ui elements assigned to it.
 * UNIMPLEMENTED
 */
typedef struct
{
        cearth_ui *i;
        int c;
} cearth_gui;

#endif //#ifndef _CEARTH_GUI
