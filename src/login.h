#ifndef _LOGIN_H
#define _LOGIN_H
#include <stdio.h>
#include <SDL2/SDL_net.h>

/* Performs auth with server and gets the token. */
void get_token(unsigned const char token[64], const char *user, const char*pass);

#endif
