/*************************************************************************
	> File Name: 389.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 16时02分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *thr_fn1(void)
{
    printf("th1 is returning\n");
    return ((void *)1);
}
void *thr_fn2(void)
{
    printf("th2 is exiting\n");
    pthread_exit((void *) 2);
}

int main(void)
{
    int err;
    pthread_t tid1,tid2;
    void *tret;

    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err != 0){
    }

    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err != 0){
    }

    err = pthread_join(tid1,&tret);
    printf("th1 exit code %ld\n",(long)tret);

    //err = pthread_join(tid2,&tret);
    //printf("th2 exit code %ld\n",(long)tret);
    
}
