#include "cearth_ctx.h"

cearth_ctx *
cearthctx_new(void)
{
        cearth_ctx *ctx = calloc(1, sizeof(cearth_ctx));
        /* Connect to server. */
        ctx->sk = SDLNet_UDP_Open(0);

        IPaddress ip;
        SDLNet_ResolveHost(&ip, haven_serv, HAVENSERV_PORT);

        int success = SDLNet_UDP_Bind(ctx->sk, -1, &ip);
        /* TEST */
        printf("Success: %d\n", success);
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

	printf ("%d\n", ctx->b_in.data);

        ctx_send(ctx);

        /* TEST */
        while(1) {
                /* TODO write ctx_recv */
                UDPpacket pack;
                pack.channel = -1;
                pack.data = ctx->b_out.data;
                pack.maxlen = 65535;
                int recv = SDLNet_UDP_Recv(ctx->sk, &pack);
                if (recv) {
                        printf("I got something!!!\n");
                }
        }
        return 0;
}

void
ctx_send(cearth_ctx *ctx)
{
        UDPpacket pack;
        pack.channel = -1;
        pack.data = ctx->b_in.data;
        pack.len = ctx->b_in.wpos;

        SDLNet_UDP_Send(ctx->sk, pack.channel, &pack);
}

void
buf_init(cearth_buf *b)
{
        b->rpos = 0;
        b->wpos = 0;
        memset(b->data, 0, 65535);
}

Uint8 read_int8(cearth_buf *b)
{
	Uint8 i;
	memcpy(&i, b->data + b->rpos, 1);
	b->rpos++;
	return i;
}

void
buf_addint8(cearth_buf *b, Uint8 i)
{
        int pos = b->wpos;
        unsigned char *dest = b->data;
        memcpy(dest + pos, &i, 1);
        b->wpos++;
}

Uint16 read_int16(cearth_buf *b){
	Uint16 i;
	memcpy(&i, b->data + b->rpos, 2);
	b->rpos += 2;
	return i;
}

void
buf_addint16(cearth_buf *b, Uint16 i)
{
        int pos = b->wpos;
        unsigned char *dest = b->data;
        memcpy(dest + pos, &i, 2);
        b->wpos += 2;
}

Uint32 read_int32(cearth_buf *b){
	Uint32 i;
	memcpy(&i, b->data + b->rpos, 4);
	b->rpos += 4;
	return i;
}

void
buf_addint32(cearth_buf *b, Uint32 i)
{
        int pos = b->wpos;
        unsigned char *dest = b->data;
        memcpy(dest + pos, &i, 4);
        b->wpos += 4;
}

char *read_string(cearth_buf *b){
	char* c;
	memcpy(c, b->data + b->rpos, strlen((const char *) (b->data + b->rpos)) + 1);
	b->rpos += strlen((const char *) (b->data + b->rpos)) + 1;
	return c;
}

void
buf_addstring(cearth_buf *b, const char *c)
{
        int pos = b->wpos;
        unsigned char *dest = b->data;
        memcpy(dest + pos, c, strlen(c) + 1);
        b->wpos += strlen(c) + 1;
}

unsigned char *read_bytes(cearth_buf *b){
	unsigned char *c;
	memcpy(c, b->data + b->rpos, strlen((const char *) (b->data + b->rpos)) + 1);
	 b->rpos += strlen((const char *) (b->data + b->rpos)) + 1;
	return c;
}

void
buf_addbytes(cearth_buf *b, const unsigned char *c)
{
        int pos = b->wpos;
        unsigned char *dest = b->data;
        memcpy(dest + pos, c, strlen((const char *)c));
        b->wpos += strlen((const char *)c);
}

