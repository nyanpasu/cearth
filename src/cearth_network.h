#ifndef _NETWORK_H
#include <string.h>
#include <stdint.h>

#include <SDL2/SDL_net.h>

struct blob {
        int size;
        unsigned char data[65535]; // TODO put data on the heap
};

/* sets b.size to 0 */
void blob_init(struct blob *b);

void blob_add_int8(struct blob *b, int8_t i);
void blob_add_str(struct blob *b, char *str);

#define _NETWORK_H
#endif
