#ifndef _CEARTH_RESOURCE_H
#define _CEARTH_RESOURCE_H

/**
 * Holds the infomation on game resources
 * Gets the location from ~/.cearth from initialization.
 * Currently UNIMPLEMENTEd
 *
 */
typedef struct
{
        int restotal;
} cearth_resourcedb;

/**
 * Allocated the memory necessary for holding the resources.
 * Searchs and (probably) loads into memory.
 */
cearth_resourcedb *resourcedb_open();

#endif //#ifdef _RESOURCE_H
