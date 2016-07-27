/*************************************************************************
	> File Name: fcntl_access.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月18日 星期一 14时30分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include"my_errno.c"

int main(void)
{
    int ret;
    int access_mode;
    int fd;
    if((fd = open("3.c",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU) ) == -1)
        my_errno("open",__LINE__);
    
    //设置文件打开方式
    if((ret = fcntl(fd, F_SETFL, O_APPEND)) < 0)
        my_errno("fcntl",__LINE__);

    //获取文件打开方式
    if((ret = fcntl(fd, F_GETFL, 0)) < 0)
        my_errno("fcntl",__LINE__);
    
    access_mode = ret & O_ACCMODE; // O_ACCMODE是值为3的掩码此处为了取得ret后两位的值
    
    if(access_mode == O_RDONLY)
    printf("3.c access_mode is readonly");
    else if(access_mode == O_WRONLY)
    printf("3.c access_mode is writeonly");
    else if(access_mode == O_RDWR)
    printf("3.c access_mode is read&write");
    
    if(ret & O_APPEND)
    printf(" ,append");
    if(ret & O_NONBLOCK)
    printf(" , nonblock");
    if(ret & O_SYNC)
    printf(" ,sync");
    printf("\n");
    return 0;
}
