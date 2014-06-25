#include "cearth_ctx.h"

cearth_ctx *
cearthctx_new(void)
{
        cearth_ctx *ctx = calloc(1, sizeof(cearth_ctx));
        /* Connect to server. */
        return ctx;
}
