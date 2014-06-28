#include "cearth_resourcedb.h"

cearth_resourcedb *
resourcedb_open()
{
        cearth_resourcedb *db;
        db = calloc(1, sizeof(cearth_resourcedb));

        return db;
}
