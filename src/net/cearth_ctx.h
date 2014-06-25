#ifndef _H_CTX_
#define _H_CTX_
#include <SDL/SDL_net.h>

#include "cearth_network.h"
#include "../config/cearth_config.h"

typedef struct
{
        UDPSocket *sk;

        /* TODO plan out how buffers are managed and used.
         * Maybe have buffers used exclusively for recv and send,
         * and have all the packets copied into separate arbitrary
         * buffers.
         */
        void b_in[65535];
        void b_out[65535];

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
#endif //#ifndef _H_CTX_
