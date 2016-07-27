/*************************************************************************
	> File Name: processingimage.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月23日 星期六 08时51分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[], char ** environ)
{
    int i ;
    printf("I am process imagine\n");
    printf("my pid is %d,my parent pid is %d\n",getpid(),getppid());
    printf("uid is %d, gid is %d",getuid(),getgid());

    for(i = 0; i < argc; i++)
    {
        printf("argv[%d],%s\n",i,argv[i]);
    }
    //return 0;
}
