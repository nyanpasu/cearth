#include "network.h"

void
blob_init(blob *b)
{
        b->size = 0;
}

void
blob_add_int8(blob *b, int8_t i)
{
        b->data[b->size] = i;
        b->size++;
}

void
blob_add_str(blob *b, char *str)
{
        int len = strlen(str);
        strcpy((char *)b->data+b->size, str);
        b->size += len;
}

