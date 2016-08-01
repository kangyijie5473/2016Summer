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
#define BUFFERSIZE 1500
#define LEN 12
int main(void)
{
    int socket_fd,conn_fd,ret,client_len;
    char buffer[32], recv_buffer[BUFFERSIZE],send_buffer[BUFFERSIZE] = "success";
    unsigned long int address = 0;
    struct sockaddr_in server_addr;
    struct in_addr in;

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
    }
    
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4507);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0){
        perror("send");
    }
    if(listen(socket_fd, LEN) < 0){
        perror("listen");
    }
    client_len = sizeof(struct sockaddr_in);
    if((conn_fd = accept(socket_fd, (struct sockaddr *)&server_addr, &client_len)) < 0){
        perror("accept");
    }
    if((ret = recv(conn_fd, recv_buffer, sizeof(recv_buffer), 0)) < 0){
        perror("recv");
    }else{
    //printf("%d\n",ret);
        recv_buffer[ret] = '\0';
        if((strcmp(recv_buffer,"kangyijie")) == 0){
            
        }
        //printf("%s",recv_buffer);
        //fgets(send_buffer, BUFFERSIZE, stdin);
        send(conn_fd,send_buffer, BUFFERSIZE, 0);
    }

    close(socket_fd);
    close(conn_fd);
    //printf("%d",recv_buffer[0]);
}

