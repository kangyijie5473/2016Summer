/*************************************************************************
	> File Name: test_address.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 11时34分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(void)
{
    char buffer[32];
    int ret = 0 ,host = 0, network = 0;
    unsigned long int address = 0;
    struct in_addr in;

    in.s_addr = 0;

    printf("please input your address\n");
    fgets(buffer, 31, stdin);
    buffer[31] = '\0';

    if( (ret= inet_aton(buffer, &in)) == 0 ){
        printf("inet_aton: \t inavild address\n");
    }else {
        printf("inet_aton: \t0x%lx\n", in.s_addr);
    }
    
    if((address = inet_addr(buffer)) == INADDR_NONE){
        printf("inet_aton: \t inavild address\n");
    }else{
        printf("inet_addr: \t0x%lx\n",address);
    }

    if((address = inet_network(buffer)) == -1){
        printf("inavild address\n");
    }else {
        printf("inet_work: \t0x%lx\n",address);
    }

    if()

}
