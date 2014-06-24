#include "cearth_login.h"

cearth_logindb*
logindb_open(void)
{
        cearth_logindb *db = calloc(sizeof(cearth_logindb), 1);

        FILE *fp = fopen(LOGINDB_FILE, "r+");
        if (fp == NULL)
                return NULL;

        char line[LOGINDB_MAXLINE];
        fgets(line, LOGINDB_MAXLINE, fp);

        while (!feof(fp)) {
               if (strlen(line) > 0) { /* If line is not blank */
                       if(line[0] == '#') { /* Ignore lines that start with # as comments. */
                               fgets(line, LOGINDB_MAXLINE, fp);
                               continue;
                       }

                       char *cookie = strchr(line, ';') + 1;
                       int namelen = cookie - line - 1;
                       int cookielen = strlen(cookie); 
                       if (cookie[cookielen] == '\n') {
                               cookie[cookielen] = 0;
                       }

                       /* +1 for the NULL char. */
                       char *name      = calloc(namelen + 1, sizeof(char));
                       char *cookienew = calloc(LOGIN_COOKIESIZE, sizeof(char));
                       /* TODO Use strtok */
                       memcpy(name, line, namelen);
                       memcpy(cookienew, cookie, cookielen);
                       
                       db->user->name  [db->n] = name;
                       db->user->cookie [db->n] = cookienew;
                       db->n++;
               }
               fgets(line, LOGINDB_MAXLINE, fp);
        }

        fclose(fp);
        return db;
}

void
logindb_close(cearth_logindb *db)
{
        FILE *fp = fopen(LOGINDB_FILE, "w+");

        if (fp == NULL) {
                perror("Couldn't open LOGINDB_FILE\n");
                return;
        }

        for (int i = 0; i < db->n; ++i)
        {
                fputs(db->name[i], fp);
                fputc(';', fp);
                fputs(db->cookie[i], fp);
                fputc('\n', fp);

                free(db->name[i]);
                free(db->cookie[i]);
        }

        free(db);
}

int
logindb_useradd(cearth_logindb *db, const char *user)
{
        char *newname   = calloc(strlen(user)+1, 1);
        char *newcookie = calloc(LOGIN_COOKIESIZE, 1);

        strcpy(newname, user);

        db->n++;
        db->name[db->n-1] = newname;
        db->cookie[db->n-1] = newcookie;

        return 0;
}

int
logindb_usercheck(cearth_logindb *db, const char *user)
{
        if (db->n == 0)
                return 0;

        for (int i = 0; i < db->n; ++i)
        {
                if (strcmp(db->name[i], user) == 0)
                {
                        int success = 1;
                        if (strlen(db->cookie[i]) > 0)
                                success = 2;
                        return success;
                }
        }

        return 0;
}

int
logindb_userget(cearth_logindb *db, const char *user)
{
        if (db->n == 0)
                return -1;

        for (int i = 0; i < db->n; ++i)
        {
                if (strcmp(db->name[i], user) == 0)
                {
                        return i;
                }
        }

        return -1;
}

char *
logindb_cookieget(cearth_logindb *db, const char *user)
{
        int n = logindb_userget(db, user);
        return db->cookie[n];
}


char *
loginhttp_tokenget(const char *user, const char *cookie)
{
        printf("TOKENGET IS UNIMPLEMENTED. Args: user: %s, cookie: %s", user, cookie);
        return("KEK!");
}

/* TODO store tokens in logindb as well. */
char *
logindb_tokenget(cearth_logindb *db, const char *user, const char *cookie)
{
        printf("TOKENGET IS UNIMPLEMENTED. Args: user: %s, cookie: %s", user, cookie);
        return("KEK!");
}

void
loginhttp_cookieget(cearth_logindb *db, const char *user)
{
        int check = logindb_usercheck(db, user); /* You can't trust outside data! */
        switch(check) {
                case 1:
                        break;
                case 0:
                case 2:
                default:
                        return;
        }
        /*
         * Obtain password from stdin
         * TODO Make password input hidden like in sudo/github login
         */
        printf("Password for user '%s': ", user);
        char password[24] = {0};
        fgets(password, 24, stdin);
        /* Replace trailing newline with NULL */
        size_t nl = strlen(password) - 1;
        if (password[nl] == '\n')
                password[nl] = '\0';

        CURL *handle = curl_easy_init();

        /* Set up post request */
        char postdata[128] = {0};
        strcat(postdata, "r=/portal/&username=");
        strcat(postdata, user);
        strcat(postdata, "&password=");
        strcat(postdata, password);

        /* Set up HTTP connection */
        char loginurl[128] = {0};
        strcat(loginurl, haven_webauth);
        strcat(loginurl, "/portal/sec/login");
        curl_easy_setopt(handle, CURLOPT_URL, loginurl);
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, postdata);
        curl_easy_setopt(handle, CURLOPT_COOKIEJAR, LOGIN_COOKIEJAR);

        curl_easy_perform(handle);
        curl_easy_cleanup(handle);

        /* Read cookie if it exists. */
        FILE *fp = fopen(LOGIN_COOKIEJAR, "w+");
        if (!fp) {
                perror("cearth_login");
                return;
        }
        char cookie[33];
        while(!feof(fp)) {
                char line[LOGINDB_MAXLINE];
                fgets(line, LOGINDB_MAXLINE, fp);
                sscanf(line, "www.havenandhearth.com\tFALSE\t/\tFALSE\t0\thsess\t%s", cookie);
        }

        fclose(fp);
        remove(LOGIN_COOKIEJAR);

        logindb_cookieset(db, user, cookie);
}

int
logindb_cookieset(cearth_logindb *db, const char *user, const char *cookie)
{
        /* Invalid logindb */
        if (db->n == 0)
                return -1;
        /* Invalid cookie  */
        if (strlen(cookie) != LOGIN_COOKIESIZE)
                return -1;

        int n = logindb_userget(db, user);
        strcpy(db->cookie[n], cookie);

        return 0;
}
