#ifndef _H_CTX_
#define _H_CTX_
#include <SDL/SDL_net.h>

#include "cearth_network.h"
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

        int state;
} cearth_ctx;

/* Makes a new context and connects to the
 * server defined in cearth_config.h
 * Remember: A connection is automatically established.
 */
cearth_ctx *cearthctx_new(void);
/*
 * Attempts to auth with the server and connect.
 * Returns error value.
 * Returns 0 on success.
 */
int cearthctx_connect(cearth_ctx *ctx, const char *usr, const char *tok);

/*
 * Internal commands.
 */
void ctx_send();
void ctx_recv();

void buf_addint8(cearth_buf *, Uint8);
void buf_addint16(cearth_buf *, Uint16);
void buf_addint32(cearth_buf *, Uint32);
void buf_addstring(cearth_buf *, const char *);
void buf_addbytes(cearth_buf *, const unsigned char *);

void buf_init(cearth_buf *);
#endif //#ifndef _H_CTX_
