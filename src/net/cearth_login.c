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

                       char* name = strtok(line, " -,.;");
                       char* cookie = strtok(NULL, " -,.;");
                       char* token = strtok(NULL, " -,.;");

                       /* Allocate memory for the data */
                       char* m1 = malloc(strlen(name  ));
                       char* m2 = malloc(strlen(cookie));
                       char* m3 = malloc(strlen(token ));
                       strcpy(m1, name);
                       strcpy(m2, cookie);
                       strcpy(m3, token);

                       db->user[db->n].name    = m1;
                       db->user[db->n].cookie  = m2;
                       db->user[db->n].token   = m3;
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
                fprintf(fp, "%s;%s;%s\n", db->user[i].name, db->user[i].cookie, db->user[i].token);

                free(db->user[i].name);
                free(db->user[i].cookie);
                free(db->user[i].token);
        }

        free(db);
}

int
logindb_useradd(cearth_logindb *db, const char *user)
{
        char *newname   = calloc(strlen(user)+1, 1);
        char *newcookie = calloc(LOGIN_COOKIESIZE, 1);
        char *newtoken  = calloc(LOGIN_TOKENSIZE , 1)

        strcpy(newname, user);

        db->n++;
        db->user[db->n-1].name   = newname;
        db->user[db->n-1].cookie = newcookie;
        db->user[db->n-1].token  = newtoken;

        return 0;
}

int
logindb_usercheck(cearth_logindb *db, const char *user)
{
        if (db->n == 0)
                return 0;

        for (int i = 0; i < db->n; ++i) {
                if (strcmp(db->name[i].name, user) == 0) {
                        int success = 1;
                        if (strlen(db->name[i].cookie) > 0)
                                success = 2;
                        if (strlen(db->name[i].token) > 0)
                                success = 3;

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
                if (strcmp(db->user[i].name, user) == 0)
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
        return db->user.cookie[n];
}

void
loginhttp_tokenget(cearth_logindb *db, const char *user)
{
        char url[LOGIN_URLMAXSIZE] = {0};
        char cookie[LOGIN_MAXLINE] = {0};
        FILE *buf = tmpfile();

        int n = logindb_userget(db, user);
        char * user_cookie = db->user[b].cookie;

        strcat(url, haven_webauth);
        strcat(url, haven_tokenlink);

        strcat(cookie, "hsess=");
        strcat(cookie, user_cookie);
        
        CURL *c = curl_easy_init();
        curl_easy_setopt(c, CURLOPT_URL, url);
        curl_easy_setopt(c, CURLOPT_COOKIE, cookie);
        curl_easy_setopt(c, CURLOPT_WRITEDATA, buf);

        curl_easy_perform(c);

        curl_easy_cleanup(c);

        /* Parse tmp file */
        fseek(buf, 0, SEEK_SET);
        char *tok[LOGIN_TOKENSIZE] = {0};
        while(!feof(buf)) {
                /* Finding the token string */
                fscanf(buf, LOGIN_TOKSTRSTART"%s", tok);
        }

        printf("TEST: Token from http: %s\n", tok);

        fclose(buf);
        strcpy(db->user[n].token, tok);
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
        strcpy(db->name[n].cookie, cookie);

        return 0;
}
