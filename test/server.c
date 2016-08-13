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
#include<fcntl.h>
#include<linux/limits.h>
#include<dirent.h>
#include<time.h>
#define TEXTBUFFER   256
#define ENTRYBUFFER  20

#define _SUCCESS  0
#define _FAIL     -1

#define ONLINE  10
#define ABSENCS 11
#define BAN     12

#define NORMAL  13
#define MANAGER 14

#define SIGNUP 50
#define SIGNIN 51

#define CHAT_ALL 52
#define CHAT_ONE 53
#define FTP      54
#define USRMANGE 55

#define UPFILE   57
#define DOWNFILE 56
#define FRESHFILE 58

#define EOR_NAME 70
#define EOR_PAWD 71

#define BUFFERSIZE 1500
#define LEN 12
typedef struct user_client{
    char name[20];
    char passwd[17];
    int flag;
}userClient;

 struct user_server{
    int fd;
    char name[20];
    short status;
    short privateId;
}userServer[50];

typedef struct Message{
    char name[20];
    char time[35];
    char text[TEXTBUFFER];
}message;
int online_max = 0;
void get_time_message( message *temp);
void *doit();
void check(int conn_fd, userClient *p);
const int lenMessage = sizeof(message);
const int lenUserClient = sizeof(userClient);

void get_time_message( message *temp)
{
    struct tm* newtime;
    char tmpbuf[28];
    time_t lt1;
    time(&lt1);
    newtime=localtime(&lt1);
    strftime(tmpbuf,128,"%Y-%m-%d %A %T",newtime);
    memset(temp -> time, 0, sizeof(temp -> time));
    strcpy(temp -> time, tmpbuf);
    temp -> time[strlen(temp -> time)] = '\0';
    //temp -> time[strlen(temp -> time)+1] = '\0';
    return ;
}

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
    client_addr.sin_port = htons(4508);
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
            pthread_create(&pthid, NULL, &doit, (void *)conn_fd);
        }else{
           continue; 
        }

    }
}
/*
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
     
    return;
}
*/
void send_online_people(int conn_fd)
{
    message *m;
    int i;
    int k = 0;
    m =(message *)malloc(lenMessage);
    memset(m,0,lenMessage);
    for(i = 4; i <= online_max+3 ; i++){
        if(userServer[i].status == CHAT_ALL && k  == 0){
            strcpy(m -> text, userServer[i].name);
            m -> text[strlen(m -> text)] = '\n';
            k++;
        }else if(userServer[i].status == CHAT_ALL && k != 0){
            strcat(m -> text, userServer[i].name);
            //m -> text[strlen(m -> text)] = ""
        }
    }
    m -> text[strlen(m -> text)] = '\0';
    strcpy(m -> name, "people");
    printf("&&&&&&%s\n", m -> text);
    k = send(conn_fd, m, lenMessage, 0);
    printf("%dfinish%s\n", k, m -> name);
    free(m);
    return ;
}


int get_chatall_people(int conn_fd_group[])
{
    int count = 0;
    int i ;
    for(i = 4; i <= online_max +3; i++){
        if(userServer[i].status == CHAT_ALL){
            conn_fd_group[count] = i;
            printf("chat_all is %d\n",i);
            count++;
        }
    }
    return count;
}



void chat_all(int conn_fd)
{
    message *m;
    int conn_fd_group[20];
    int conn_fd_number = 0;
    int j;
    m = (message *)malloc(lenMessage);
    while(1){
        if(read(conn_fd, m, lenMessage)){
            if(strcmp(m -> time, "quit") == 0){
                free(m);
                return;
            }else if(strcmp(m -> time, "fresh") == 0)
            {
                printf("send_online_people\n");
                send_online_people(conn_fd);
                memset(m,0,lenMessage);
            }else{
                conn_fd_number = get_chatall_people(conn_fd_group);
                for(j = 0; j < conn_fd_number ; j++){
                    get_time_message(m);
                    write(conn_fd_group[j], m, lenMessage);
                }
                memset(conn_fd_group, 0, sizeof(conn_fd_group));
                conn_fd_number = 0 ;
                memset(m,0, lenMessage);
            }
             
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
        recv(conn_fd, p, lenUserClient,0);
        switch(p -> flag){
            case UPFILE:{
                fp = fopen(p -> name, "w");
                do{
                    m = (message *)malloc(lenMessage);
                    read(conn_fd, m, lenMessage);
                    if(strcmp(m -> name,"finish") == 0){
                         
                        break;
                    }
                    fwrite(m -> text,strlen(m -> text),1,fp);
                     
                    
                }while(1);
                fclose(fp);
                 
                continue;
            }
            case FRESHFILE:{
                printf("fresh\n");
                m = (message *)malloc(lenMessage);
                get_fresh_file(m);
                write(conn_fd, m, lenMessage);
                 
                continue;
            }
            case DOWNFILE:{
                
                strcat(path, p -> name);
        //        printf("%s\n",path);
          //      printf("%s\n", p -> name);
                fd = open(path, O_RDONLY);
                if(fd < 0){
                    m =(message *)malloc(lenMessage);
                    strcpy(m -> name, "no file");
                    write(conn_fd, m, lenMessage);
                     
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
                 
                continue;
            }
            default:
                 
                return;
        }
    }
}


void check_in(int i, userClient *p)
{
    online_max++;
    userServer[i].status= ONLINE;
    userServer[i].fd = i;
    strcpy(userServer[i].name, p -> name);
    userServer[i].privateId = 0;
    return ;
}




void * doit(int conn_fd)
{
    userClient *p;
    int k;
    p = (userClient *)malloc(lenUserClient);
    k = recv(conn_fd, p, lenUserClient, 0);
    check(conn_fd, p);
    printf("%s %d\n", p -> name, conn_fd);
    check_in(conn_fd, p);
    printf("%s %d\n", userServer[conn_fd].name,userServer[conn_fd].fd);
    memset(p, 0, lenUserClient);
    while(1){
        recv(conn_fd, p, lenUserClient,0);
        switch(p -> flag){
            case CHAT_ALL:{
                userServer[conn_fd].status = CHAT_ALL;
                printf("conn_fd%dstatus %d\n",conn_fd,userServer[conn_fd].status);
                printf("all\n");
                chat_all(conn_fd);
                p = (userClient *)malloc(lenUserClient);
                memset(p, 0, lenUserClient);
                continue;
            }
            case CHAT_ONE:{
                printf("single\n");
                chat_all(conn_fd);
                p = (userClient *)malloc(lenUserClient);
                continue;
            }
            case FTP:{
                printf("ftp\n");
                ftp(conn_fd);
                return;
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
        if(strcmp(p -> name, "1") == 0 || strcmp(p -> name, "kk") == 0){
            if(strcmp(p -> passwd, "1") == 0 ){
                printf("passwd is right\n");
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




