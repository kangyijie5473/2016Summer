/*************************************************************************
	> File Name: fcntl_lock.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月18日 星期一 15时50分50秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include"my_errno.c"

//锁的设置或释放函数
int lock_set(int fd, struct flock *lock)
{
    if((fcntl(fd, F_SETLK, lock)) == 0)
    {
        if(lock -> l_type == F_RDLCK)
            printf("set read lock pid is %d\n",getpid());
        else if(lock -> l_type == F_WRLCK)
            printf("set write lock pid is %d\n",getpid());
        else if(lock -> l_type == F_UNLCK)
            printf("release lock pid is %d\n",getpid());
    }
    else {
        perror("lock operation fail\n");
        return -1;
    }

    return 0;
}

//测试锁能否被设置

int lock_test(int fd, struct flock *lock)
{
    if((fcntl(fd, F_GETLK, lock)) == 0)
    {
        if(lock -> l_type == F_UNLCK)
        {
            printf("lock can be set in fd\n");
            return 0;
        }
        else{
            if(lock -> l_type == F_RDLCK)
            printf("can't set lock pid is %d",getpid());
            else if(lock -> l_type == F_WRLCK)
            printf("can't set lock pid is %d",getpid());
            return -2;
        }
    }
    else {
        perror("get incompatible locks fail");
        return -1;
    }
}


int main(void)
{
    int fd,tem;
    int ret;
    struct flock lock;
    char read_buf[32];

    //打开或创建文件
    if((fd = open("4.c",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU)) == -1)
    {
        my_errno("open", __LINE__);
    }
    if((write(fd,"test lock",10)) != 10)
    {
        my_errno("write",__LINE__);
    }

    //初始化lock结构
    memset(&lock, 0, sizeof(struct flock));
    lock.l_start = SEEK_SET;
    lock.l_whence = 0;
    lock.l_len = 0;

    //设置读锁
    lock.l_type = F_RDLCK;
    if(lock_test(fd,&lock) == 0)
    {   
        lock.l_type = F_RDLCK;
        lock_set(fd,&lock);
    }

    //读数据
    lseek(fd,0,SEEK_SET);
    if((ret = read(fd,read_buf,10)) < 0)
    {
        my_errno("read",__LINE__);
    }
    read_buf[ret] = '\0';
    printf("%s\n",read_buf);

    //等待任意键
    getchar();

    //设置写锁
    lock.l_type = F_WRLCK;
    if((tem = lock_test(fd, &lock)) == 0)
    {
        printf("%d\n",tem);
        lock.l_type = F_WRLCK;
        tem = lock_set(fd,&lock);
    }

    //释放锁
    lock.l_type = F_UNLCK;
    lock_set(fd, &lock);
    close(fd);
    printf("%d\n",tem);
    return 0 ;
}
