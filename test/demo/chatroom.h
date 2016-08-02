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
#define TEXTBUFFER 256
#define ENTRYBUFFER 20
#define _SUCCESS 0
#define _FAIL -1
#define ONLINE 10
#define ABSENCS 11
#define BAN 12
#define NORMAL 13
#define MANAGER 14

typedef struct user_client{
    char name[20];
    char passwd[17];
}userClinet;

typedef struct user_server{
    char name[20];
    short status;
    short identity;
    struct user_server *next;
}userServer;

struct user_server *pHead = NULL;

typedef struct Message{
    char name[20];
    char time[28];
    char text[TEXTBUFFER];
}message;

void get_time_message(struct messsage *temp)
#endif
