/*************************************************************************
	> File Name: my_shell.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月25日 星期一 14时52分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<linux/limits.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#define CMD_NOMAL 1
#define CMD_REOUT 2
#define CMD_REIN 4
#define CMD_PIPE 8
#define CMD_BKGRD 17
#define CMD_CD 7
#define CMD_PWD 13
#define CMD_HISTORY 15
char my_argv[10][256];

void get_input(char *buf);
void display_$(const char *path);
int  explain_input(char *buf);
void testPrint(int len);
int  do_cmd(int flag, int len);

void display_$(const char *path)
{
    printf("\033[01;32mkangkang@ubuntu16.04:\033[00m\033[01;34m%s\033[00m$ ",path);
}

void get_input(char *buf)
{
    int ch,len = 0;
    ch = getchar();
    while(len < 256 && ch != '\n')
    {
        buf[len++] = ch;
        ch = getchar();
    }
    if(len == 256)
    {
        printf("command is too long\n");
        exit(-1);
    }
    buf[len] = '\n';
    buf[len+1] = '\0';
}

int  explain_input(char *buf)
{
    int flag = 0;
    int i,j = 0;
    char *k = &buf[0];
    for(i = 0; buf[i] != '\0'; i++)
    {
        if(buf[i] == ' '|| buf[i] == '\n')
        {
            strncpy(my_argv[j++],k,i-flag);
            my_argv[j-1][i-flag] = '\0';
            flag = i+1;
            k = &buf[i+1];
        }
    }
    return j;
}

void fun(int  a)
{
}



int explian_option(int len)
{
    int flag = 0;
    int i;
    int q = 0;
    for(i = 0; i < len; i++)
    {
        switch(my_argv[i][0])
        {
            case '>':flag += CMD_REOUT;q++;break;
            case '<':flag += CMD_REIN;q++;break;
            case '|':flag += CMD_PIPE;q++;break;
        }
    }
    if( !strcmp(my_argv[len - 1],"&"))
    flag += CMD_BKGRD;
    if(flag == 0)
    return CMD_NOMAL;
    if(q > 1)
    {
        printf("my shell doesn't support many options\n");
        return 0;
    }
    return flag;
}

int  do_cmd(int flag, int len)

{
    char *argvv[len], path[PATH_MAX];
    int i = 0,var = 0, fd,j;
    pid_t pid;
    for(i = 0;i < len; i++)
    {
        argvv[i] = (char *)my_argv[i];
    }
    i = 0;
    argvv[len] = NULL;
    if(strcmp(argvv[0], "cd") == 0)
    {
        chdir(argvv[1]);
        return CMD_CD;
    }
    if(strcmp(argvv[0], "history") == 0){
        argvv[0] = "less";
        argvv[1] = "/home/kangyijie/.bash_history";
        flag = CMD_HISTORY;
    }
    pid = fork();
    wait(&var);
    switch(flag)
    {
        case CMD_NOMAL:
            if(pid == 0)
            {
                if( -1 == execvp(argvv[0],argvv))
                return -1;
                exit(0);
            }
            break;
        case CMD_REOUT:
            if(pid == 0)
            {
                while (strcmp(argvv[i],">") !=0)
                i++;
                argvv[i] = NULL;
                fd = open(argvv[i+1],O_RDWR|O_CREAT,S_IRWXU);
                dup2(fd,1);
                if( -1 == execvp(argvv[0],argvv))
                return -1;
                exit(0);
            }
            break;
        case CMD_REIN:
            if(pid == 0)
            {
                while (strcmp(argvv[i],"<") !=0)
                i++;
                argvv[i] = NULL;
                fd = open(argvv[i+1],O_RDONLY);
                dup2(fd,0);
                if( -1 == execvp(argvv[0],argvv))
                return -1;
                exit(0);
            }
            break;
        case CMD_PIPE:
            if(pid == 0)
            {
                int fd2,g;
                char *argv2[len];
                while (strcmp(argvv[i],"|") !=0)
                {
                i++;
                }
                argvv[i] = NULL;
                for( j = 0; i < len; j++)
                {
                    argv2[j] = argvv[++i];
                }
                argv2[j] = NULL;
                if((g = fork()) == 0)
                {
                    fd2 = open("/tmp/secret",O_RDWR|O_CREAT,S_IRWXU);
                    dup2(fd2,1);
                    if(-1 == (execvp(argvv[0],argvv)))
                    return -1;
                    exit(0);
                }
                fd2 = open("/tmp/secret",O_RDWR);
                dup2(fd2,0);
                if(-1 == execvp(argv2[0],argv2))
                return -1;
                remove("/tmp/secret");
                exit(0);
            }
            break;
        case CMD_HISTORY:
            if(pid == 0)
            {
                if(-1 == execvp(argvv[0], argvv))
                return -1;
                exit(0);
            }
            break;
        default: break;
    }
    
    if(flag == CMD_BKGRD)
    {
        printf("process id %d\n",pid);
        return 0;
    }
    
    
}

                        


int main(int argc, char *argv[])
{
    char path[PATH_MAX + 1],*buf;
    int len,flag,tem;
    buf = (char *)malloc(sizeof(char ) * 256);
    while(1)
    {
    getcwd(path,512);
    memset(buf, 0, 256);
    display_$(path);
    signal(SIGINT, fun);
    get_input(buf);
    if(strcmp(buf,"\n") == 0)
    continue;
    if(strcmp(buf,"quit\n" )  == 0 || strcmp(buf,"exit\n" )  == 0)
        exit(0);
    if((len = explain_input(buf)) == 0)
        continue;
    flag = explian_option(len);
    if( (tem =do_cmd(flag,len)) == -1)
        printf("command is error\n");
    }

    
}
