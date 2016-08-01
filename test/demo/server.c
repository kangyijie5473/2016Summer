/*************************************************************************
	> File Name: server.c
	> Author: Jack Kang
	> Mail: xiyoulinux.kangyijie@gmail.com
	> Created Time: 2016年08月01日 星期一 15时06分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

/*错误处理函数*/
void my_errno(const char *err_string, int line)
{
    fprintf(stderr, "line : %d",line);
    perror("err_string");
    exit(1);
}



