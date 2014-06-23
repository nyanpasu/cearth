#include "login.h"

int
logindb_open(struct cearth_logindb *db)
{
        db->n = 0;
        memset(db->name, 0, 100);
        memset(db->cookie, 0, 100);

        FILE *fp = fopen(LOGINDB_FILE, "r+");
        if (fp == NULL)
                return -1;

        char line[LOGINDB_MAXLINE];
        fgets(line, LOGINDB_MAXLINE, fp);

        while (!feof(fp)) {
               if (strlen(line) > 0) {
                       if(line[0] == '#') { // Simple comments.
                               fgets(line, LOGINDB_MAXLINE, fp);
                               continue;
                       }

                       char *cookie = strchr(line, ';') + 1;
                       int namelen = cookie - line - 1;
                       int cookielen = strlen(cookie) - 1;

                       /* +1 for the NULL char. */
                       char *name      = (char*)malloc(namelen + 1);
                       char *cookienew = (char*)malloc(cookielen + 1);
                       memset(name, '\0', namelen + 1);
                       memset(cookienew, '\0', cookielen + 1);
                       memcpy(name, line, namelen);
                       memcpy(cookienew, cookie, cookielen);
                       
                       db->name[db->n] = name;
                       db->cookie[db->n] = cookienew;
                       db->n++;
               }
               fgets(line, LOGINDB_MAXLINE, fp);
        }

        fclose(fp);
        return 1;
}

int
logindb_close(struct cearth_logindb *db)
{
        FILE *fp = fopen(LOGINDB_FILE, "w+");

        if (fp == NULL) {
                printf("Couldn't open LOGINDB_FILE\n");
                return 0;
        }

        for (int i = 0; i < db->n; ++i)
        {
                fputs(db->name[i], fp);
                fputc(';', fp);
                fputs(db->cookie[i], fp);
                fputc('\n', fp);
        }

        return 1;
}

int
logindb_useradd(struct cearth_logindb *db, char *user)
{
        char *newname = (char *)malloc(strlen(user)+1);
        char* newcookie = (char *)malloc(1);

        strcpy(newname, user);
        *newcookie = '\0';

        db->n++;
        db->name[db->n-1] = newname;
        db->cookie[db->n-1] = newcookie;

        return 0;
}

int
logindb_usercheck(struct cearth_logindb *db, char *user)
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

void
loginhttp_gettoken(const char *user, const char *cookie)
{
        printf("Connecting to %s to get token for user '%s'...\n", haven_webauth, user);
        CURL *handle = curl_easy_init();
}

void
loginhttp_getcookie(const char *user)
{
        /* Obtain password from stdin
         * TODO Make password input hidden like in sudo/github login
         */
        printf("Password for user '%s': ", user);
        char password[24] = {0};
        fgets(password, 24, stdin);
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

        curl_easy_perform(handle);

        /* Read cookie if it exists. */
        struct curl_slist *cookies = NULL;
        curl_easy_getinfo(handle, CURLINFO_COOKIELIST, cookies);

        if (cookies == NULL) {
                fprintf(stderr, "loginhttp_getcookie: Failed to obtain cookies.\n");
        } else {
                printf("First cookie: %s", cookies->data);
        }

        curl_easy_cleanup(handle);
}
