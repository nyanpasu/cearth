#ifndef _NETWORK_H
#define _NETWORK_H
#include <SDL2/SDL_net.h>

#define PVER         2

#define MSG_SESS     0
#define MSG_REL      1
#define MSG_ACK      2
#define MSG_BEAT     3
#define MSG_MAPREQ   4
#define MSG_MAPDATA  5
#define MSG_OBJDATA  6
#define MSG_OBJACK   7
#define MSG_CLOSE    8
#define OD_REM       0
#define OD_MOVE      1
#define OD_RES       2
#define OD_LINBEG    3
#define OD_LINSTEP   4
#define OD_SPEECH    5
#define OD_LAYERS    6
#define OD_DRAWOFF   7
#define OD_LUMIN     8
#define OD_AVATAR    9
#define OD_FOLLOW    10
#define OD_HOMING    11
#define OD_OVERLAY   12
#define OD_AUTH      13
#define OD_HEALTH    14
#define OD_BUDDY     15
#define OD_END       255
#define SESSERR_AUTH 1
#define SESSERR_BUSY 2
#define SESSERR_CONN 3
#define SESSERR_PVER 4
#define SESSERR_EXPR 5

#endif
