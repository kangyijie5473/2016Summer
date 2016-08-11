/*************************************************************************
	> File Name: chatroom.h
	> Author: Jack Kang
	> Mail: xiyoulinux.kangyijie@gmail.com
	> Created Time: 2016年08月02日 星期二 16时12分16秒
 ************************************************************************/

#ifndef _CHATROOM_H
#define _CHATROOM_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BUFFERSIZE 256
#define TEXTBUFFER   256
#define ENTRYBUFFER  20

#define _SUCCESS  0
#define _FAIL     -1

#define ONLINE  10
#define ABSENCS 11
#define BAN     12

#define NORMAL  13
#define MANAGER 14

#define SIGNUP 50
#define SIGNIN 51

#define CHAT_ALL 52
#define CHAT_ONE 53
#define FTP      54
#define USRMANGE 55
#define DOWNFILE 56
#define UPFILE   57
#define FRESHFILE 58

#define EOR_NAME 70
#define EOR_PAWD 71

typedef struct user_client{
    char name[20];
    char passwd[17];
    int flag;
}userClient;

typedef struct user_server{
    char name[20];
    short status;
    short identity;
    struct user_server *next;
}userServer;

struct user_server *pHead = NULL, *pEnd = NULL;

typedef struct Message{
    char name[20];
    char time[35];
    char text[TEXTBUFFER];
}message;

void get_time_message( message *temp);
#endif
