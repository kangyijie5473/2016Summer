/*************************************************************************
	> File Name: timetest.c
	> Author: Jack Kang
	> Mail: xiyoulinux.kangyijie@gmail.com
	> Created Time: 2016年08月02日 星期二 16时43分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"chatroom.h"
void get_time_message( message *temp)
{
    struct tm* newtime;
    char tmpbuf[28];
    time_t lt1;
    time(&lt1);
    newtime=localtime(&lt1);
    strftime(tmpbuf,128,"%Y-%m-%d %A %T",newtime);
    strcpy(temp -> time, tmpbuf);
    return ;
}

