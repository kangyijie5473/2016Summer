/*************************************************************************
	> File Name: my_errno.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月18日 星期一 14时16分42秒
 ************************************************************************/

#include<errno.h>

void my_errno(const char *err_string, int line)
{
    fprintf(stderr,"line : %d  ",line);
    perror(err_string);
    exit(1);
}
