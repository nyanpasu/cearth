#ifndef _LOGIN_H
#define _LOGIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL_net.h>
#include <curl/curl.h>

#include "../config/cearth_defines.h"
#include "../config/cearth_config.h"
#include "../net/cearth_network.h"

typedef struct
{
        int n;
        cearth_loginuser *user;
} cearth_logindb;

typedef struct
{
        char *name[LOGINDB_MAX];
        char *cookie[LOGINDB_MAX];
        char *token[LOGINDB_MAX];
} cearth_loginuser;

/* Logs into havenandhearth.com and gets a session cookie */
void loginhttp_cookieget(cearth_logindb *, const char *user);
/* gets /autohaven and gets a token in hexadecimal */
char * loginhttp_tokenget(const char *user, const char *cookie);

int logindb_useradd(cearth_logindb *, const char *user);
int logindb_userdel(cearth_logindb *, const char *user);
/*
 * Checks if a user exists in the logindb
 * Returns 0 if the user does not exists;
 * Returns 1 if the user exists but has no cookie.
 * Returns 2 if the user exists and has a cookie.
 */
int logindb_usercheck(cearth_logindb *, const char *user);
int logindb_userget  (cearth_logindb *, const char *user);
int logindb_cookieset(cearth_logindb *, const char *user, const char *cookie);
int logindb_cookiedel(cearth_logindb *, const char *user);
char * logindb_cookieget(cearth_logindb *, const char *user);
/*
 * Requires user to have an assigned cookie or it will return NULL.
 * Retrieves hexadecimal cookie using logindb_tokenget
 * and returns a pointer to it.
 */
char * logindb_tokenget(cearth_logindb *, const char *user, const char *cookie);

/*
 * Opens LOGINDB_FILE and loads it into the appropriate struct.
 * @returns pointer to loaded logindb.
 */
cearth_logindb *logindb_open(void);
/*
 * Saves updated logindb to LOGINDB_FILE and frees memory.
 * This must be called when cearth is done with logindb.
 */
void logindb_close(cearth_logindb *);
#endif
