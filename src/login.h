#ifndef _LOGIN_H
#define _LOGIN_H
#include <stdio.h>
#include <regex.h>
#include <string.h>

#include <SDL2/SDL_net.h>
#include <curl/curl.h>

#include "defines.h"
#include "network.h"
#include "config.h"

struct cearth_logindb
{
        int n;
        char *name[LOGINDB_MAX];
        char *cookie[LOGINDB_MAX];
        char *token[LOGINDB_MAX];
};

/* Logs into havenandhearth.com and gets a session cookie */
void loginhttp_getcookie(const char *user);
/* gets /autohaven and gets a token in hexadecimal */
void loginhttp_gettoken(const char *user, const char *cookie);

int logindb_useradd(struct cearth_logindb *, char *user);
int logindb_userdel(struct cearth_logindb *, char *user);
/*
 * Checks if a user exists in the logindb
 * Returns 0 if the user does not exists;
 * Returns 1 if the user exists but has no cookie.
 * Returns 2 if the user exists and has a cookie.
 */
int logindb_usercheck(struct cearth_logindb *, char *user);
int logindb_cookieget(struct cearth_logindb *, char *user);
int logindb_cookieset(struct cearth_logindb *, char *user, char *cookie);
int logindb_cookiedel(struct cearth_logindb *, char *user);

int logindb_open(struct cearth_logindb *);
int logindb_close(struct cearth_logindb *);
#endif
