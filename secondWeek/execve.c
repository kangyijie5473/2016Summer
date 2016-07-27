/*************************************************************************
	> File Name: execve.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月23日 星期六 08时57分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[], char ** environ)
{
    pid_t pid;
    int stat_val;
    printf("exec example\n");
    pid = fork();
    switch(pid)
    {
    case -1:
        perror("process creation failed\n");
        exit(1);
    case 0:
        printf("child process is running\n");
        printf("my pid is %d,my parent pid is %d\n",getpid(),getppid());
        printf("uid is %d,gid is %d\n",getuid(),getgid());
        execve("processimage",argv,environ);
        printf("process never go to here\n");
        exit(0);
    default:
        printf("parent process is running\n");
        break;
    }
    wait(&stat_val);
    exit(0);
}
