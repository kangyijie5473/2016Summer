/*************************************************************************
	> File Name: fork.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月20日 星期三 17时21分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if(0 == getpid())
    {
        sleep(3);
    printf("father is %d\n",getppid());
    }

    /*
    pid_t pid;
    pid = fork();
    wait();
    getchar();
    switch(pid)
    {
        case 0 :printf("child process is running, Curpid is %d,parentpid is %d",pid,getppid());break;
        case -1: printf("fail \n");break;
        default: printf("parent process is running,childpid is %d,parentpid is %d",pid,getpid());break;
    }*/
    exit(0);
}
