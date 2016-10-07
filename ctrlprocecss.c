/*************************************************************************
	> File Name: ctrlprocecss.c
	> Author: Jack Kang
	> Mail: kangyijie@xiyoulinx.org
	> Created Time: 2016年10月07日 星期五 14时00分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(void)
{
    int n;
    char buf[1024];

    while(1){
        if(n = read(0, buf, 1024)){
            buf[n] = '\0';
            printf("ctrlprocecss receive %s\n",buf);

            if(!strcmp(buf, "exit")){
                exit(0);
            }

            if(!strcmp(buf, "getpid")){
                printf("new pid is %d\n",getpid());
                sleep(3);
                exit(0);
            }
        }
    }
}
