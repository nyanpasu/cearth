#include "cearth_ctx.h"

cearth_ctx *
cearthctx_new(void)
{
        cearth_ctx *ctx = calloc(1, sizeof(cearth_ctx));
        /* Connect to server. */
        ctx->sk = SDLNet_UDP_Open(0);

        IPaddress ip;
        SDLNet_ResolveHost(&ip, haven_serv, HAVENSERV_PORT);

        SDLNet_UDP_Bind(ctx->sk, -1, &ip);
        return ctx;
}

int
cearthctx_connect(cearth_ctx *ctx, const char *usr, const char *tok)
{
        /* Convert tok from hex to binary */
        unsigned char tok_b[LOGIN_TOKENSIZE / 2];
        for (int i = 0; i < LOGIN_TOKENSIZE / 2; i++) {
                sscanf(i * 2 + tok, "%hhx", tok_b + 1);
        }

        /* The auth packet */
        buf_addint8   ( &ctx->b_in, MSG_SESS);
        buf_addint16  ( &ctx->b_in, 1);
        buf_addstring ( &ctx->b_in, "Haven");
        buf_addint16  ( &ctx->b_in, PVER);
        buf_addstring ( &ctx->b_in, usr);
        buf_addbytes  ( &ctx->b_in, tok_b);

        ctx_send(ctx);
        return 0;
}

void
buf_init(cearth_buf *b)
{
        b->rpos = 0;
        b->wpos = 0;
        memset(b->data, 0, 65535);
}

void
buf_addint8(cearth_buf *b, Uint8 i)
{
        int pos = b->wpos;
        char *dest = b->data;
        memcpy(dest + pos, &i, 1);
        b->wpos++;
}

void
buf_addint16(cearth_buf *b, Uint16 i)
{
        int pos = b->wpos;
        char *dest = b->data;
        memcpy(dest + pos, &i, 2);
        b->wpos += 2;
}

void
buf_addint32(cearth_buf *b, Uint32 i)
{
        int pos = b->wpos;
        char *dest = b->data;
        memcpy(dest + pos, &i, 4);
        b->wpos += 4;
}

void
buf_addstring(cearth_buf *b, const char *c)
{
        int pos = b->wpos;
        char *dest = b->data;
        memcpy(dest + pos, c, strlen(c) + 1);
        b->wpos += strlen(c) + 1;
}

void
buf_addbytes(cearth_buf *b, const unsigned char *c)
{
        int pos = b->wpos;
        char *dest = b->data;
        memcpy(dest + pos, c, strlen(c) + 1);
        b->wpos += strlen(c) + 1;
}

