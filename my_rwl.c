/*************************************************************************
	> File Name: my_rwl.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月18日 星期一 08时54分06秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

void my_errno(const char *err_string, int line)
{
    fprintf(stderr,"line : %d  ",line);
    perror(err_string);
    exit(1);
}

int my_read(int fd)
{
    int len;
    int ret;
    int i ;
    char read_buf[64];

    //获取文件长度并使文件读写指针位于文件起始处
    if(lseek(fd,0,SEEK_END) == -1)
    {
        my_errno("lseek",__LINE__);     //__LINE__指所在源代码的行数
    }
    if((len = lseek(fd, 0,SEEK_CUR)) == -1)
    {
        my_errno("lseek",__LINE__);
    }
    if(lseek(fd, 0, SEEK_SET) == -1)
    {
        my_errno("lseek",__LINE__);
    }

    printf("len: %d\n",len);

    //读数据
    if((ret = read(fd, read_buf, len)) < 0)
    {
        my_errno("read", __LINE__);
    }
    else
    printf("ret:%d\n",ret); //查看实际读取的字节数

    //打印数据
    for(i = 0; i < len; i++)
    {
        printf("%c",read_buf[i]);
    }
    printf("\n");
    return ret;
}

int main(void)
{
    int  fd,t;
    char write_buf[32] = "hello linux!";
    if((fd = open("2.c",O_RDWR|O_CREAT|O_TRUNC,S_IWUSR|S_IRUSR|S_IXUSR)) == -1)
    my_errno("open",__LINE__);
    else
    printf("creat successfully\n");

    //写数据
    if( write(fd, write_buf, strlen(write_buf)) != strlen(write_buf))
    my_errno("write",__LINE__);
    
    my_read(fd);
    
    printf("*----------------------*\n");
    if(lseek(fd, 10, SEEK_END) == -1)
    my_errno("lseek",__LINE__);
    if(write(fd, write_buf, strlen(write_buf)) != strlen(write_buf))
    my_errno("write",__LINE__);
    my_read(fd);
    
    close(fd);
    return 0;
}
    
     


