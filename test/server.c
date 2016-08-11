/*************************************************************************
	> File Name: test_socket.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 16时29分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include"chatroom.h"
#include<fcntl.h>
#include<linux/limits.h>
#include<dirent.h>
#include"timetest.c"
//#define BUFFERSIZE 1500
#define LEN 12
int conn_fd_group[20];
int conn_fd_number = 0;
void *doit();
void check(int conn_fd, userClient *p);
const int lenMessage = sizeof(message);
const int lenUserClient = sizeof(userClient);

void get_fresh_file(message *m)
{
    DIR *dir;
    char path[] = "Source";
    struct dirent *ptr;
    char *p = m -> text;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return ;
               
    }
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr -> d_name, ".") == 0 | strcmp(ptr -> d_name, "..") == 0)
        continue;
        strcpy(p ,ptr -> d_name);
        p[strlen(p)] = '\n';
        p = p + strlen(p);
    }
    closedir(dir);
    return ;
}
int main(void)
{
    int socket_fd,conn_fd,ret,client_len;
    char buffer[32], recv_buffer[BUFFERSIZE],send_buffer[BUFFERSIZE] = "success";
    unsigned long int address = 0;
    struct sockaddr_in client_addr;
    struct in_addr in;
    pthread_t pthid;

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
    }

    int optval=1;
    if(setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
    {
        perror("setsockopt");
    }
    
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(4507);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(socket_fd, (struct sockaddr *)&client_addr, sizeof(struct sockaddr_in)) < 0){
        perror("send");
    }
    if(listen(socket_fd, LEN) < 0){
        perror("listen");
    }
    client_len = sizeof(struct sockaddr_in);
    while(1){
        if((conn_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len)) > 0){
            conn_fd_group[conn_fd_number++] = conn_fd;
            printf("***%d****\n",conn_fd_group[conn_fd_number-1]);
            pthread_create(&pthid, NULL, &doit, (void *)conn_fd);
        }else{
           continue; 
        }

    }
}
void send_history(int conn_fd)
{
    int fd,num;
    message *m;
    fd = open("history",O_RDONLY);
    m = (message *)malloc(lenMessage);
    while(1){
        memset(m,0,lenMessage);
        if((num = read(fd, m -> text, sizeof(m -> text))) == 0){
            break;
        }
        strcpy(m -> name, " ");
        printf("%s",m -> text);
        write(conn_fd, m , lenMessage);
    }
    memset(m,0,lenMessage);
    strcpy(m -> name, "finish");
    write(conn_fd, m , lenMessage);
    free(m);
    return;
}
void chat_all(int conn_fd)
{
    message *m;
    int j;
    FILE *fp;
    fp = fopen("history","a+");
    m = (message *)malloc(lenMessage);
    while(1){
        if(read(conn_fd, m, lenMessage)){
            if(strcmp(m -> text, "quit") == 0){
                printf("%s\n",m -> text);
                return;
            }else if(strcmp(m -> text, "history") == 0){
                send_history(conn_fd);
            }else{
                
                for(j = 0; j < conn_fd_number ; j++){
                    get_time_message(m);
                    fwrite( m, lenMessage, 1,fp);
                    write(conn_fd_group[j], m, lenMessage);
                }
            }
            printf("%s\n",m -> text);
            free(m);
            continue;
        }

    }
}
void ftp(int conn_fd)
{
    FILE *fp;
    int i,fd,num;
    char path[] = "./Source/";
    userClient *p;
    message *m;
    while(1){
        p = (userClient *)malloc(lenUserClient);
        read(conn_fd, p, lenUserClient);
        switch(p -> flag){
            case UPFILE:{
                fp = fopen(p -> name, "w");
                do{
                    m = (message *)malloc(lenMessage);
                    read(conn_fd, m, lenMessage);
                    if(strcmp(m -> name,"finish") == 0){
                        free(m);
                        break;
                    }
                    fwrite(m -> text,strlen(m -> text),1,fp);
                    free(m);
                    
                }while(1);
                fclose(fp);
                free(p);
                continue;
            }
            case FRESHFILE:{
                printf("fresh\n");
                m = (message *)malloc(lenMessage);
                get_fresh_file(m);
                write(conn_fd, m, lenMessage);
                free(m);
                continue;
            }
            case DOWNFILE:{
                
                strcat(path, p -> name);
                printf("%s\n",path);
                printf("%s\n", p -> name);
                fd = open("./Source/Benz", O_RDONLY);
                if(fd < 0){
                    m =(message *)malloc(lenMessage);
                    strcpy(m -> name, "no file");
                    write(conn_fd, m, lenMessage);
                    free(m);
                    continue;
                }
                m = (message *)malloc(lenMessage);
                while(1){
                    memset(m -> text, 0, sizeof(m -> text));
                    if((num = read(fd, m -> text, sizeof(m -> text))) == 0){
                        break;
                    }
                    m -> text[strlen(m -> text)] = '\0';
                    strcpy(m -> name, " ");
                    printf("%s\n",m -> text);
                    write(conn_fd, m, lenMessage);
                }
                m = (message *)malloc(lenMessage);
                strcpy(m -> name,"finish");
                write(conn_fd,m, lenMessage);
                free(m);
                continue;
            }
            default:
                free(p);
                return;
        }
    }
}

void * doit(int conn_fd)
{
    userClient *p;
    int k;
    p = (userClient *)malloc(lenUserClient);
    k = recv(conn_fd, p, lenUserClient, 0);
    printf("fd %d name %s passwd %s\n",conn_fd,p -> name, p -> passwd);
    check(conn_fd, p);
    while(1){
        recv(conn_fd, p, lenUserClient, 0);
        switch(p -> flag){
            case CHAT_ALL:{
                printf("all\n");
                chat_all(conn_fd);
                free(p);
                p = (userClient *)malloc(lenUserClient);
                continue;
            }
            case CHAT_ONE:{
                printf("single\n");
                chat_all(conn_fd);
                free(p);
                p = (userClient *)malloc(lenUserClient);
                continue;
            }
            case FTP:{
                printf("ftp\n");
                ftp(conn_fd);
                return NULL;
            }
            case USRMANGE:{
                printf("USRMANGE\n");
                continue;
            }
            default: 
                printf("exit\n");
                exit(0);
        }
    }
        
}
void check(int conn_fd, userClient *p)
{
    char s[] = "success";
    if(p -> flag == SIGNIN){
        if(strcmp(p -> name, "kang") == 0 || strcmp(p -> name, "kk") == 0){
            if(strcmp(p -> passwd, "kk1997") == 0 ){
                printf("passwd is right");
                write(conn_fd, s, strlen(s)+1);
                //exit(0);
            }else{
                printf("name is right passwd is error");
                //send(conn_fd, f, 4, 0);
                exit(1);
            }
        }else{
            printf("name is error");
            //send(conn_fd, f, 4, 0);
            exit(1);
        }
    }else{
        exit(1);
    }
}




