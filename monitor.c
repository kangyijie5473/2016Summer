/*************************************************************************
	> File Name: monitor.c
	> Author: Jack Kang
	> Mail: kangyijie@xiyoulinx.org
	> Created Time: 2016年10月07日 星期五 13时51分09秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<wait.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char ** argv, char ** env)
{
    int fd[2];
    pid_t pid;
    int stat_val;

    if(argc  < 2){
        printf("wrong parameters\n");
        exit(1);
    }
    if(pipe(fd))
    {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    switch(pid){
        case -1 :
            printf("fork failed\n");
            exit(1);
        case 0:
            close(0); //error 
            dup(fd[0]);
            execve("b.out",(void *)argv,env);
            exit(0);
        default:
            close(fd[0]);
            write(fd[1], argv[1], strlen(argv[1]));
            break;
    }
    wait(&stat_val);
    exit(0);
}
