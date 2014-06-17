#ifndef _LOGIN_H
#define _LOGIN_H
#include <stdio.h>
#include <SDL2/SDL_net.h>

#include "defines.h"
#include "network.h"

/* Performs auth with server and gets the token. */
void get_token(unsigned const char token[64], const char *user, const char*pass);

/* Sends username to server pre auth */
void login_send_user(const char *user);

/* Sends password to server pre auth */
void login_send_pass(const char *pass);

#endif
