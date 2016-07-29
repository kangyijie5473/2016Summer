/*************************************************************************
	> File Name: oncerun.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 08时29分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
    printf(" fun run is running, pthread id is %u\n",pthread_self());

}



void *thread1(void *argv)
{
    printf("curret pthread id is %u\n",pthread_self());
    pthread_once(&once,run);
    printf("thread1 end\n");

}

void *thread2(void *argv)
{
    printf("curret pthread id is %u\n",pthread_self());
    pthread_once(&once,run);
    printf("thread2 end\n");
}



int main(void)
{
    pthread_t thid1,thid2;

    pthread_create(&thid1, NULL, thread1, NULL);
    pthread_create(&thid2, NULL, thread2, NULL);

    sleep(3);
    printf(" main pthread  is exit\n");
    exit(0);
}
