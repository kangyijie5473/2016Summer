/*************************************************************************
	> File Name: my_signal.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 15时04分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void fun(int  a)
{
    printf("recv signal\n");
}


int main(void)
{
    signal(SIGINT, fun);
    while(1);
    return 0;
}
