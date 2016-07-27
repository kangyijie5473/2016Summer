/*************************************************************************
	> File Name: fork3.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月21日 星期四 09时50分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    switch(pid)
    {
        case 0:
        while(1)
        {
            printf("傻瓜你关不掉我\n");
            sleep(3);
        }
        case -1:
            perror("process creation failed\n");
            exit(1);
        default:
            printf("I am parent process,my pid is %d\n",getpid());
            exit(0);
    }
    return 0;
}
