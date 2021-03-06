/*************************************************************************
	> File Name: linfun.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月22日 星期五 15时10分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<linux/limits.h>
#include<dirent.h>
#include"my_errno.c"
#include<pwd.h>
#include<grp.h>
#include"my_ls.h"

int my_readir_rln(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    bubble_sort(i);
    change_mode_t(i);
    print_n(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_rl(dir_name[tem]);
    }
    return 0;
}

int my_readir_arlnu(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((strcmp(ptr -> d_name,".") == 0) || (strcmp(ptr -> d_name,"..") == 0))
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    change_mode_t(i);
    print_n(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_arlnu(dir_name[tem]);
    }
    return 0;
}

int my_readir_arln(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((strcmp(ptr -> d_name,".") == 0) || (strcmp(ptr -> d_name,"..") == 0))
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    bubble_sort(i);
    print_n(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_arl(dir_name[tem]);
    }
    return 0;
}
int my_readir_simple_ru(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    print_simple(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_simple_ru(dir_name[tem]);
    }
    return 0;
}
int my_readir_simple_r(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    bubble_sort_simple(i);
    print_simple(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_simple_ar(dir_name[tem]);
    }
    return 0;
}

int my_readir_simple_aru(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((strcmp(ptr -> d_name,".") == 0) || (strcmp(ptr -> d_name,"..") == 0))
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    print_simple(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_simple_aru(dir_name[tem]);
    }
    return 0;
}

int my_readir_arlu(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((strcmp(ptr -> d_name,".") == 0) || (strcmp(ptr -> d_name,"..") == 0))
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    change_mode_t(i);
    print(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_arlu(dir_name[tem]);
    }
    return 0;
}
int my_readir_simple_ar(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((strcmp(ptr -> d_name,".") != 0) && (strcmp(ptr -> d_name,"..") != 0))
        {
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;
        }
        else continue;
    }
    bubble_sort_simple(i);
    puts(dir_name[0]);
    print_simple(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_simple_ar(dir_name[tem]);
    }
    return 0;
}

int my_readir_arl(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((strcmp(ptr -> d_name,".") == 0) || (strcmp(ptr -> d_name,"..") == 0))
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    bubble_sort(i);
    change_mode_t(i);
    print(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_arl(dir_name[tem]);
    }
    return 0;
}
int my_readir_rlun(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    change_mode_t(i);
    print_n(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_rl(dir_name[tem]);
    }
    return 0;
}
int my_readir_rlu(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    change_mode_t(i);
    print(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_rl(dir_name[tem]);
    }
    return 0;
}
int my_readir_rl(const char *path)
{
    DIR *dir;
    char dir_name[100][50];
    struct dirent *ptr;
    int i = 0,tem,key =0;;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    printf("----------------- %s------------------\n",path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        if((tem = (file[i].st_mode /512)) == 32)
        {
            getcwd(dir_name[key],512);
            strcat(dir_name[key],"/");
            strcat(dir_name[key], name[i]);
            key++;
        }
        i++;   
    }
    bubble_sort(i);
    change_mode_t(i);
    print(i);
    for(tem =0; tem < key; tem++)
    {
        my_readir_rl(dir_name[tem]);
    }
    return 0;
}
    
    


int my_readir_not_a(const char *path)
{
    DIR *dir;
    struct dirent *ptr;
    int i = 0;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        i++;
    }
    closedir(dir);
    return i;
}

int my_readir(const char *path)
{
    DIR *dir;
    struct dirent *ptr;
    int i = 0;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    chdir(path);
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        stat(ptr -> d_name, &file[i]);
        name[i] = ptr -> d_name;
        i++;
    }
    closedir(dir);
    return i;
}

int my_readir_simple_not_a(const char *path)
{
    DIR *dir;
    struct dirent *ptr;
    int i = 0;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        if((ptr -> d_name)[0] == '.')
        continue;
        name[i] = ptr -> d_name;
        i++;
    }
    closedir(dir);
    return i;
}
int my_readir_simple(const char *path)
{
    DIR *dir;
    struct dirent *ptr;
    int i = 0;
    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
               
    }
    while((ptr = readdir(dir)) != NULL&&i < 99)
    {
        name[i] = ptr -> d_name;
        i++;
    }
    closedir(dir);
    return i;
}

void print_simple(int len)
{
    int i;
    printf("sum is %d\n",len);
    for(i = 0; i < len; i++)
    {
        printf("%-s\t\t\t",name[i]);
        if((i+1)%5 == 0)
        printf("\n");
    }
    printf("\n");
    return;
}

    
void bubble_sort_simple(int len)
{
    int i,j;
    char temp[50];
    for(i = 0; i < 50; i++)
    temp[i] = '\0';
    for(i = 0; i < len; i++)
        for(j = 0; j < len - i - 1; j++)
        {
            if(strcmp(name[j],name[j + 1]) > 0)
            {
                strcpy(temp,name[j]);
                strcpy(name[j],name[j+1]);
                strcpy(name[j+1],temp);
                for(i = 0; i < 50; i++)
                    temp[i] = '\0';
            }
        }
    
}

void bubble_sort(int len)
{
    int i,j;
    char temp[50];
    for(i = 0; i < 50; i++)
    temp[i] = '\0';
    for(i = 0; i < len; i++)
        for(j = 0; j < len - i - 1; j++)
        {
            if(strcmp(name[j],name[j + 1]) > 0)
            {
                strcpy(temp,name[j]);
                strcpy(name[j],name[j+1]);
                strcpy(name[j+1],temp);
                tem = file[j];
                file[j] = file[j+1];
                file[j+1] = tem;
                for(i = 0; i < 50; i++)
                    temp[i] = '\0';
            }
        }
}
void change_mode_t(int len)
{
    int mode_o,mode_g,mode_u,i;
    for(i = 0; i < len; i++)
    {
        mode_o = file[i].st_mode % 8;
        file[i].st_mode /= 8;
        mode_g = file[i].st_mode % 8;
        file[i].st_mode /= 8;
        mode_u = file[i].st_mode % 8;
        file[i].st_mode /= 8;
        switch(mode_o)
        {
            case 7:mode[i][7] = 'r';mode[i][8] = 'w';mode[i][9] = 'x';break;
            case 6:mode[i][7] = 'r';mode[i][8] = 'w';mode[i][9] = '-';break;
            case 5:mode[i][7] = 'r';mode[i][8] = '-';mode[i][9] = 'x';break;
            case 4:mode[i][7] = 'r';mode[i][8] = '-';mode[i][9] = '-';break;
            case 3:mode[i][7] = '-';mode[i][8] = 'w';mode[i][9] = 'x';break;
            case 2:mode[i][7] = '-';mode[i][8] = 'w';mode[i][9] = '-';break;
            case 1:mode[i][7] = '-';mode[i][8] = '-';mode[i][9] = 'x';break;
            case 0:mode[i][7] = '-';mode[i][8] = '-';mode[i][9] = '-';break;
        }
        switch(mode_g)
        {
            case 7:mode[i][4] = 'r';mode[i][5] = 'w';mode[i][6] = 'x';break;
            case 6:mode[i][4] = 'r';mode[i][5] = 'w';mode[i][6] = '-';break;
            case 5:mode[i][4] = 'r';mode[i][5] = '-';mode[i][6] = 'x';break;
            case 4:mode[i][4] = 'r';mode[i][5] = '-';mode[i][6] = '-';break;
            case 3:mode[i][4] = '-';mode[i][5] = 'w';mode[i][6] = 'x';break;
            case 2:mode[i][4] = '-';mode[i][5] = 'w';mode[i][6] = '-';break;
            case 1:mode[i][4] = '-';mode[i][5] = '-';mode[i][6] = 'x';break;
            case 0:mode[i][4] = '-';mode[i][5] = '-';mode[i][6] = '-';break;
        }
        switch(mode_u)
        {
            case 7:mode[i][1] = 'r';mode[i][2] = 'w';mode[i][3] = 'x';break;
            case 6:mode[i][1] = 'r';mode[i][2] = 'w';mode[i][3] = '-';break;
            case 5:mode[i][1] = 'r';mode[i][2] = '-';mode[i][3] = 'x';break;
            case 4:mode[i][1] = 'r';mode[i][2] = '-';mode[i][3] = '-';break;
            case 3:mode[i][1] = '-';mode[i][2] = 'w';mode[i][3] = 'x';break;
            case 2:mode[i][1] = '-';mode[i][2] = 'w';mode[i][3] = '-';break;
            case 1:mode[i][1] = '-';mode[i][2] = '-';mode[i][3] = 'x';break;
            case 0:mode[i][1] = '-';mode[i][2] = '-';mode[i][3] = '-';break;
        }
        mode[i][10] ='\0';
        if(file[i].st_mode == 64)
        mode[i][0] = '-';
        else if(file[i].st_mode == 32)
            mode[i][0] = 'd';
        else mode[i][0] = '*';
    }
}
char *uid_to_name(uid_t uid)
{
    struct passwd *getpwuid(),*pw_ptr;
    static char numstr[10];
    if((pw_ptr = getpwuid(uid) ) == NULL)
    {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else return pw_ptr -> pw_name;
}
char *gid_to_name(gid_t gid)
{
    struct group *getgrgid(),*grp_ptr;
    static char numstr[10];
    if((grp_ptr = getgrgid(gid) ) == NULL)
    {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else return grp_ptr -> gr_name;
}
void print_n(int len)
{
    int i ;
    char *time_str;
    printf("sum is %d\n",len);
    for(i = 0; i < len; i++)
    {
        if(i == 0)
        printf(" ");
        time_str = (char *)malloc(sizeof(char ) * 30);
        strcpy(time_str,ctime(&(file[i].st_ctime)));
        time_str[strlen(time_str)-1] = ' ';
        printf("%s\t%lu\t%u\t%u\t%ld\t%s%s\n ",mode[i],file[i].st_nlink,file[i].st_uid,file[i].st_gid,file[i].st_size,time_str,name[i]);
        free(time_str);
    }
}

void print(int len)
{
    int i ;
    char *uid[100],*gid[100];
    char *time_str;
    printf("sum is %d\n",len);
    for(i = 0; i < len; i++)
    {
        if(i == 0)
        printf(" ");
        time_str = (char *)malloc(sizeof(char ) * 30);
        strcpy(time_str,ctime(&(file[i].st_ctime)));
        time_str[strlen(time_str)-1] = ' ';
        uid[i] = uid_to_name(file[i].st_uid);
        gid[i] = gid_to_name(file[i].st_gid);
        printf("%s\t%lu\t%s\t%s\t%ld\t%s%s\n ",mode[i],file[i].st_nlink,uid[i],gid[i],file[i].st_size,time_str,name[i]);
        free(time_str);
    }
}


int main(int argc, char *argv[])
{
    char path[PATH_MAX + 1];
    int flag = 0,i,j = 0,k = 0, m = 0, n = 0, o = 0;
    
    //判断参数个数
    if(argc > 3)
    {
        printf("参数过多\n");
        exit(1);
    }

    //无参数直接输出:
    if(argc == PARAM_NONE)
    {
        getcwd(path, 512);
        i =  my_readir_not_a(path);
       bubble_sort_simple(i);
        print_simple(i);
        return 0;
    }

    //记录参数
    if(argv[1][0] == '-')
    {
        for(i = 1; i < strlen(argv[1]); i++)
        {
            if(argv[1][i] == 'a'&& j == 0)
            {
                flag += PARAM_A;
                j++;
            }
            if(argv[1][i] == 'l'&& k == 0)
            {
                flag += PARAM_L;
                k++;
            }
            if(argv[1][i] == 'R'&& m == 0)
            {
                flag += PARAM_R;
                m++;
            }
            if(argv[1][i] == 'U'&& n == 0)
            {
                flag += PARAM_U;
                n++;
            }
            if(argv[1][i] == 'n'&& o == 0)
            {
                flag += PARAM_N;
                o++;
            }
        }
    }
    else{
        if(argc == 2)
        {
            i = my_readir_not_a(argv[1]);
            bubble_sort_simple(i);
            print_simple(i);
            return 0;
        }
        else {
            printf("参数输入错误\n");
            exit(1);
        }
    }
    if(argc == 2)
    {
        switch(flag)
        {
        case PARAM_L:
        {
            getcwd(path,512);
            i = my_readir_not_a(path);
            bubble_sort(i);
            change_mode_t(i);
            print(i);
            return 0;
        }
        case PARAM_A:
        {
            getcwd(path,512);
            i =my_readir_simple(path);
            bubble_sort_simple(i);
            print_simple(i);
            return 0;
        }
        case PARAM_R: 
        {
            getcwd(path, 512);
            my_readir_simple_r(path);
            return 0;
        }
        case PARAM_A+ PARAM_L:
        {
            getcwd(path,512);
            i = my_readir(path);
            bubble_sort(i);
            change_mode_t(i);
            print(i);
            return 0;
        }
        case PARAM_R + PARAM_L:
        {
            getcwd(path, 512);
            my_readir_rl(path);
            return 0;
        }
        case PARAM_R + PARAM_A:
        {
            getcwd(path, 512);
            my_readir_simple_ar(path); 
            return 0;
        }
        case PARAM_R + PARAM_L + PARAM_A:
        {
            getcwd(path, 512);
            my_readir_arl(path);
            return 0;
        }
        case PARAM_U:
        {
            getcwd(path, 512);
            i = my_readir_simple_not_a(path);
            change_mode_t(i);
            print_simple(i);
            return 0;
        }
        case PARAM_A + PARAM_U:
        {
            getcwd(path,512);
            i =my_readir_simple(path);
            print_simple(i);
            return 0;
        }
        case PARAM_L + PARAM_U:
        {
            getcwd(path,512);
            i = my_readir_not_a(path);
            change_mode_t(i);
            print(i);
            return 0;
        }
        case PARAM_R +PARAM_U:
        {
            getcwd(path, 512);
            my_readir_simple_ru(path); 
            return 0;
        }
        case PARAM_U + PARAM_L + PARAM_A:
        {
            getcwd(path, 512);
            i = my_readir_not_a(path);
            change_mode_t(i);
            print(i);
            return 0;
        }
        case PARAM_U + PARAM_L + PARAM_R:
        {
            getcwd(path,512);
            my_readir_rlu(path);
            return 0;
        }
        case PARAM_U + PARAM_A + PARAM_R:
        {
            getcwd(path,512);
            my_readir_simple_aru(path); 
            return 0;
        }
        case PARAM_U + PARAM_L +PARAM_A +PARAM_R:
        {
            getcwd(path,512);
            my_readir_arlu(path);  
            return 0;
        }
        case PARAM_N + PARAM_L:
        {
            getcwd(path,512);
            i = my_readir_not_a(path);
            bubble_sort(i);
            change_mode_t(i);
            print_n(i);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_A:
        { 
            getcwd(path,512);
            i =  my_readir(path);
            bubble_sort(i);
            change_mode_t(i);
            print_n(i);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_U:
        {
            getcwd(path,512);
            i = my_readir_not_a(path);
            change_mode_t(i);
            print_n(i);
            return 0;

        }
        case PARAM_N + PARAM_L + PARAM_R:
        {
            getcwd(path, 512);
            my_readir_rln(path); 
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_R + PARAM_A:
        {
            getcwd(path, 512);
            my_readir_arln(path);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_R + PARAM_U:
        {
            getcwd(path,512);
            my_readir_rlun(path);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_R + PARAM_A +PARAM_U:
        {
            getcwd(path,512);
            my_readir_arlnu(path);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_A + PARAM_U:
        {
            getcwd(path, 512);
            i = my_readir(path);
            change_mode_t(i);
            print_n(i);
            return 0;
        }

    }
    }
         
    if(argc == 3)
    {
    switch(flag)
    {
        case PARAM_L:
        {
        i = my_readir_not_a(argv[2]);
        bubble_sort(i);
        change_mode_t(i);
        print(i);
        return 0;
        }
        case PARAM_A :
        {
        i =my_readir_simple(argv[2]);
        bubble_sort_simple(i);
        print_simple(i);
        return 0;
        }
        case PARAM_A+ PARAM_L:
        {
        i = my_readir(argv[2]);
        bubble_sort(i);
        change_mode_t(i);
        print(i);
        return 0;
        }
        case PARAM_R:   
        {
        my_readir_simple_r(argv[2]); 
            return 0;
        }
        case PARAM_A + PARAM_R + PARAM_L:
        {
        my_readir_arl(argv[2]);
            return 0;
        }
        case PARAM_R + PARAM_A:
        {
        my_readir_simple_ar(argv[2]);
            return 0;
        }
        case  PARAM_R + PARAM_L:
        {
        my_readir_rl(argv[2]);
            return 0;
        } 
        case PARAM_U:
        {
            i = my_readir_simple_not_a(argv[2]);
            change_mode_t(i);
            print_simple(i);
            return 0;
        }
        case PARAM_A + PARAM_U:
        {
            i =my_readir_simple(argv[2]);
            print_simple(i);
            return 0;
        }
        case PARAM_L + PARAM_U:
        {
            i = my_readir_not_a(argv[2]);
            change_mode_t(i);
            print(i);
            return 0;
        }
        case PARAM_R +PARAM_U:
        {
            my_readir_simple_ru(argv[2]); 
            return 0;
        }
        case PARAM_U + PARAM_L + PARAM_A:
        {
            i = my_readir_not_a(argv[2]);
            change_mode_t(i);
            print(i);
            return 0;
        }
        case PARAM_U + PARAM_L + PARAM_R:
        {
            my_readir_rlu(argv[2]);
            return 0;
        }
        case PARAM_U + PARAM_A + PARAM_R:
        {
            my_readir_simple_aru(argv[2]); 
            return 0;
        }
        case PARAM_U + PARAM_L +PARAM_A +PARAM_R:
        {
            my_readir_arlu(argv[2]);  
            return 0;
        }
        case PARAM_N + PARAM_L:
        {
            i = my_readir_not_a(argv[2]);
            bubble_sort(i);
            change_mode_t(i);
            print_n(i);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_A:
        { 
            i =  my_readir(argv[2]);
            bubble_sort(i);
            change_mode_t(i);
            print_n(i);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_U:
        {
            i = my_readir_not_a(argv[2]);
            change_mode_t(i);
            print_n(i);
            return 0;

        }
        case PARAM_N + PARAM_L + PARAM_R:
        {
            my_readir_rln(argv[2]); 
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_R + PARAM_A:
        {
            my_readir_arln(argv[2]);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_R + PARAM_U:
        {
            my_readir_rlun(argv[2]);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_R + PARAM_A +PARAM_U:
        {
            my_readir_arlnu(argv[2]);
            return 0;
        }
        case PARAM_N + PARAM_L + PARAM_A + PARAM_U:
        {
            i = my_readir(argv[2]);
            change_mode_t(i);
            print_n(i);
            return 0;
        }

        default: printf("ddd");
    }
    }
        else exit(1);
}

