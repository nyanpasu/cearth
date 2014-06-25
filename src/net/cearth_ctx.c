#include "cearth_ctx.h"

cearth_ctx *
cearthctx_new(void)
{
        cearth_ctx *ctx = calloc(1, sizeof(cearth_ctx));
        /* Connect to server. */
        ctx->sk = SDLNet_UDP_Open(0);

        IPaddress ip;
        SDLNet_ResolveHost(&ip, haven_serv, HAVENSERV_PORT);

        SDLNet_UDP_Bind(ctx->sk, -1, ip);
        return ctx;
}

int
cearthctx_connect(cearth_ctx *ctx, const char *usr, const char *tok)
{
}
