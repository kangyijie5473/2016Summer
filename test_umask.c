/*************************************************************************
	> File Name: test_umask.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月18日 星期一 20时17分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void)
{
    umask(0);
    if((creat("example",S_IRWXU|S_IRWXO|S_IRWXG)) < 0)
    {
        perror("creat");
        exit(1);
    }
    umask(S_IRWXO);
    if((creat("example1",S_IRWXU|S_IRWXO|S_IRWXG)) < 0)
    {
        perror("creat");
        exit(1);
    }
}
