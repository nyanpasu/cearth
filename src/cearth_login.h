#ifndef _LOGIN_H
#define _LOGIN_H
#include <stdio.h>
#include <regex.h>
#include <string.h>

#include <SDL2/SDL_net.h>
#include <curl/curl.h>

#include "cearth_defines.h"
#include "cearth_network.h"
#include "cearth_config.h"

typedef struct
{
        int n;
        char *name[LOGINDB_MAX];
        char *cookie[LOGINDB_MAX];
        char *token[LOGINDB_MAX];
} cearth_logindb;

/* Logs into havenandhearth.com and gets a session cookie */
void loginhttp_getcookie(const char *user);
/* gets /autohaven and gets a token in hexadecimal */
void loginhttp_gettoken(const char *user, const char *cookie);

int logindb_useradd(cearth_logindb *, char *user);
int logindb_userdel(cearth_logindb *, char *user);
/*
 * Checks if a user exists in the logindb
 * Returns 0 if the user does not exists;
 * Returns 1 if the user exists but has no cookie.
 * Returns 2 if the user exists and has a cookie.
 */
int logindb_usercheck(cearth_logindb *, char *user);
int logindb_cookieget(cearth_logindb *, char *user);
int logindb_cookieset(cearth_logindb *, char *user, char *cookie);
int logindb_cookiedel(cearth_logindb *, char *user);

/*
 * Opens LOGINDB_FILE and loads it into the appropriate struct.
 * @returns pointer to loaded logindb.
 */
cearth_logindb *logindb_open(cearth_logindb *);
/*
 * Saves updated logindb to LOGINDB_FILE and frees memory.
 * This must be called when cearth is done with logindb.
 */
void logindb_close(cearth_logindb *);
#endif
