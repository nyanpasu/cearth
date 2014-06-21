#include "login.h"

int
logindb_usercheck(const char *user)
{
        FILE *fp = fopen(LOGINDB_FILE, "r");
        char line[LOGINDB_MAXLINE];

        if (fp==NULL) {
                fprintf(stderr, "Error: Could not open logindb.");
                return -1;
        }

        int success = 0;

        /* while the file is not empty and we're aren't at the end. */
        while(fgets(line, LOGINDB_MAXLINE, fp) != NULL && !feof(fp)) {
                char *userbreak = strchr(line, ';');
                if (userbreak == NULL) {
                        fprintf(stderr, "Error: Invalid logindb.");
                        success =  -1;
                        break;
                }
                if (strcmp(line, user) == 0) {
                        success =  1;
                }
        }

        fclose(fp);
        return success;
}
