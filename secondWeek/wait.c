/*************************************************************************
	> File Name: wait.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月23日 星期六 09时39分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>

int main(void)
{
    pid_t pid;
    char *msg;
    int k;
    int exit_code;

    printf("study how to get exit code\n");
    pid = fork();
    switch(pid)
    {
    case 0:
        msg = "child process is running\n";
        k =5;
        exit_code = 1024;
        break;
    case -1:
        perror("process creation failed\n");
        exit(1);
    default:
        exit_code = 0;
        break;
    }

    if(pid != 0)
    {
        int stat_val;
        pid_t child_pid;

        child_pid =wait(&stat_val);

        printf("child process has existed,pid is %d\n",child_pid);
        if(WIFEXITED(stat_val))
        {
            printf("child exit with code %d\n",WEXITSTATUS(stat_val));
        }
        else {
            printf("child exit abnormally\n");
        }
    }
    else {
        while(k-- > 0)
        {
            puts(msg);
            sleep(1);
        }
    }
    exit(exit_code);
}

