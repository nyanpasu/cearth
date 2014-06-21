#ifndef _LOGIN_H
#define _LOGIN_H
#include <stdio.h>
#include <regex.h>
#include <string.h>

#include <SDL2/SDL_net.h>

#include "defines.h"
#include "network.h"
#include "config.h"

struct http_header
{
        int response;
};

/* Logs into havenandhearth.com and gets a session cookie */
void loginhttp_getcookie(const char *user);
/* gets /autohaven and gets a token in hexadecimal */
void loginhttp_gettoken();

int logindb_useradd(const char *user);
int logindb_userdel(const char *user);
/* Checks if a user exists in the logindb
 * Returns 0 if the user does not exists;
 * Returns 1 if the user exists but has no cookie.
 * Returns 2 if the user exists and has a cookie.*/
int logindb_usercheck(const char *user);
int logindb_cookieget(const char *user);
int logindb_cookieset(const char *user, char *cookie);
int logindb_cookiedel(const char *user);
#endif
