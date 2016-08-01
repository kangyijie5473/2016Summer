/*************************************************************************
	> File Name: test_socket_c.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 17时08分51秒
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

int main(void)
{
    int socket_fd,temp;
    char buffer[32] = "123.206.65.225", send_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];
    //char buffer[32] = "127.0.0.1", send_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];
    unsigned long int address = 0;
    struct sockaddr_in server_addr;
    struct in_addr in;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4507);
    
    //fgets(buffer, 31, stdin);
    //buffer[31] = '\0';
    fgets(send_buffer, BUFFERSIZE, stdin);

    inet_aton(buffer, &server_addr.sin_addr);

    if(connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0){
        perror("connect");
    }
    
    if((temp =send(socket_fd, send_buffer,BUFFERSIZE, 0)) < 0){
        perror("send");
    }
    //recv(socket_fd, recv_buffer, sizeof(recv_buffer), 0);
    //puts(recv_buffer);
        //printf("%d\n",temp);
    close(socket_fd);
}

