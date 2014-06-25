#ifndef _CONFIG_H_
#define _CONFIG_H_

#define LOGINDB_FILE "logindb"
#define LOGINDB_MAX 100
#define LOGINDB_MAXLINE 128
#define LOGIN_COOKIEJAR "cookie"
#define LOGIN_COOKIESIZE 32
#define LOGIN_TOKENSIZE  64
#define LOGIN_URLMAXSIZE 256
/* TODO Having the preceeding spaces in LOGIN_TOKSTRSTART  is retarded.
 * Maybe have the function strip off whitespaces before scanning?
 */
#define LOGIN_TOKSTRSTART "     <property name=\"jnlp.haven.authck\" value=\""

static const char *haven_serv        = "moltke.seatribe.se";
static const char *haven_webauth     = "www.havenandhearth.com";
static const char *haven_tokenlink   = "/portal/autohaven";
static const char *cearth_config_dir = "/.cearth/";
static const char *foo               = "test";

#endif
