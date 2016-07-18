/*************************************************************************
	> File Name: my_create.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月18日 星期一 08时27分18秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>

int main(void)
{
    int fd;

    if((fd = open("./test/test.c",O_CREAT|O_EXCL, S_IRUSR|S_IWUSR)) == -1)
    {
        perror("open");
        exit(1);
    }
    else 
    printf("success\n");
    close(fd);
    return 0;
}
