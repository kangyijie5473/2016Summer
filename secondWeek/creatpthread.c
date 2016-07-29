/*************************************************************************
	> File Name: creatpthread.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月28日 星期四 08时15分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int *pthread(void *argv)
{
     //pthread_t newPthid;

    printf("this a new pthread, id is %u\n",pthread_self());
    return NULL;

}


int main(void)
{    
    pthread_t pthid,my;
    int *p;
    my = pthread_self();
    if(pthid = pthread_create(&pthid, NULL, (void *)pthread,NULL) != 0){
        printf("fail \n");
        exit(1);
    }
    pthread_join(my, NULL);
    printf("main pthread ,id is %u\n",pthread_self());
    sleep(1);
    exit(0);
}
