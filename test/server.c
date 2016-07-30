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
#define BUFFERSIZE 1500
#define LEN 12
int main(void)
{
    int socket_fd,conn_fd,ret;
    char buffer[32], recv_buffer[BUFFERSIZE];
    unsigned long int address = 0;
    struct sockaddr_in server_addr;
    struct in_addr in;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4507);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    listen(socket_fd, LEN);
    conn_fd = accept(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    ret = recv(conn_fd, recv_buffer, 2, 0);
    recv_buffer[ret] = '\0';
    puts(recv_buffer);
    //printf("%d",recv_buffer[0]);
}

