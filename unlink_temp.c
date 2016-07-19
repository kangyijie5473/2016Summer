/*************************************************************************
	> File Name: unlink_temp.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月19日 星期二 08时18分02秒
 ************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include"my_errno.c"

int main(void)
{
    int fd;
    char read_buf[32];
    if((fd = open("temp",O_RDWR|O_CREAT|O_TRUNC, S_IRWXU)) == -1)
    my_errno("open",__LINE__);
    if(unlink("temp") == -1)
    my_errno("unlink",__LINE__);
    if(write(fd, "hello5473", 10) < 0)
    my_errno("write", __LINE__);
    if(lseek(fd, 0, SEEK_SET) < 0)
    my_errno("lseek", __LINE__);
    if(read(fd, read_buf, 10) < 0)
    my_errno("read",__LINE__);
    printf("%s\n",read_buf);
    return 0;
}

