/*************************************************************************
	> File Name: my_cd.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月19日 星期二 08时46分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<linux/limits.h>
#include"my_errno.c"

int main(int argc, char *argv[])
{
    char buf[PATH_MAX + 1];
    //if(argc < 2)
    //{
    //    printf("my_cd <target path> \n");
    //    exit(1);
    //}

    //if(chdir(argv[1]) < 0)
    //my_errno("chdir", __LINE__);
    if(getcwd(buf,512) < 0)
    my_errno("getcwd",__LINE__);

    printf("%s\n",buf);
    return 0;
}

