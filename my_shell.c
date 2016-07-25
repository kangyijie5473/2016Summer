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
#include <termio.h>
#define CMD_NOMAL 1
#define CMD_REOUT 2
#define CMD_REIN 4
#define CMD_PIPE 8
#define CMD_BKGRD 17

typedef struct commandName{
    char name[25];
    struct commandName *next;
}cmdname;

char my_argv[10][256];

int getch(void)
{
         struct termios tm, tm_old;
         int fd = 0, ch;
     
         if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
                                                return -1;
                                           }
     
         tm_old = tm;
         cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
         if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
                                                         return -1;
                                                    }
     
         ch = getchar();
         if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
                                                             return -1;
                                                        }
        
         return ch;
}

void display_$(const char *path)
{
    printf("kangkang@ubuntu16.04:%s$ ",path);
}

cmdname *readCmdName(void)
{
    cmdname *pHead,*pEnd,*pNew;
    DIR *dir;
    struct dirent *ptr;
    char path[] = "/bin";
    pNew =(cmdname *)malloc(sizeof(cmdname));
    pEnd = pHead = pNew;
    pNew -> next = NULL;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return NULL; 
    }
    chdir(path);
    while((ptr = readdir(dir)) != NULL)
    {
        if(ptr -> d_name[0] == '.')
        continue;
        pNew = (cmdname *)malloc(sizeof(cmdname));
        pEnd -> next = pNew;
        pEnd = pEnd -> next;
        strcpy(pNew -> name,ptr -> d_name);
        pNew -> next = NULL;
    }
    return pHead;
}
/*
void testPrint(cmdname *pHead)
{
    cmdname *pTemp = pHead -> next;
    while(pTemp != NULL)
    {
    puts(pTemp -> name);
    pTemp = pTemp -> next;
    }
}

void get_input(char *buf cmdname *pHead)
{
    cmdname *pTemp ;
    int ch,len = 0;
    if(( buf[len++] = ch = getch()) == '\t')
    {
*/
    
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

void testPrint(int len)
{
    int i ;
    for(i = 0;i < len; i++)
    printf("argv[%d] =%s",i,my_argv[i]);
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
            case '<':flag += CMD_REIN;break;
            case '|':flag += CMD_PIPE;break;
        }
    }
    if( !strcmp(my_argv[len - 1],"&"))
    flag += CMD_BKGRD;
    if(flag == 0)
    return CMD_NOMAL;
    if(q > 1)
    {
        printf("my shell doesn't support many options\n");
        exit(1);
    }
    return flag;
}

void do_cmd(int flag, int len)
{
    // char cmd[256] = "/bin";
    //strcat(cmd,my_argv[0]);
    char *argvv[len];
    int i ;
    pid_t pid;
    for(i = 0;i < len; i++)
    argvv[i] = (char *)my_argv[i];
    pid = fork();
    switch(flag)
    {
        case CMD_NOMAL:
            if(pid == 0)
            {
                execvp(my_argv[0],argvv);
                exit(0);
            }
            exit(0);
    }
}
                        





int main(int argc, char *argv[])
{
    char path[PATH_MAX + 1],*buf;
    int len,flag;
    cmdname *pHead;
    
    buf = (char *)malloc(sizeof(char ) * 256);

    //getcwd(path,512);
   // pHead = readCmdName();
   // chdir(path);

    while(1)
    {
    memset(buf, 0, 256);
    display_$(path);
    get_input(buf);
    len = explain_input(buf);
    flag = explian_option(len);
    do_cmd(flag,len);
    }
    
}
