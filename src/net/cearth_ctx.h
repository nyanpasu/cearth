#ifndef _H_CTX_
#define _H_CTX_
#include <SDL2/SDL_net.h>

#include "cearth_network.h"
#include "../ui/cearth_gui.h"
#include "../config/cearth_config.h"

typedef struct
{
        int rpos;
        int wpos;
        unsigned char data[65535];
} cearth_buf;

typedef struct
{
        UDPsocket sk;

        /* TODO plan out how buffers are managed and used.
         * Maybe have buffers used exclusively for recv and send,
         * and have all the packets copied into separate arbitrary
         * buffers.
         */
        cearth_buf b_in;
        cearth_buf b_out;

        cearth_gui *gui;

        int state;
} cearth_ctx;

/* Makes a new context and connects to the
 * server defined in cearth_config.h
 * Remember: A connection is automatically established.
 */
cearth_ctx *cearthctx_new(void);
void cearthctx_setconn(cearth_ctx *ctx, const char *user, const char *token);
void cearthctx_startread(cearth_ctx *ctx);
void cearthctx_startwrite(cearth_ctx *ctx);
void cearthctx_startprcs(cearth_ctx *ctx);

/*
 * Attempts to auth with the server and connect.
 * Returns error value.
 * Returns 0 on success.
 */
int cearthctx_connect(cearth_ctx *ctx, const char *usr, const char *tok);


/*
 * INTERNAL COMMANDS.
 */
void ctx_send();
void ctx_recv();

void buf_addint8(cearth_buf *, Uint8);
void buf_addint16(cearth_buf *, Uint16);
void buf_addint32(cearth_buf *, Uint32);
void buf_addstring(cearth_buf *, const char *);
void buf_addbytes(cearth_buf *, const unsigned char *);

Uint8 read_int8(cearth_buf *b);
Uint16 read_int16(cearth_buf *b);
Uint32 read_int32(cearth_buf *b);
char *read_string(cearth_buf *b);
unsigned char *read_bytes(cearth_buf *b);

void buf_init(cearth_buf *);
#endif //#ifndef _H_CTX_
