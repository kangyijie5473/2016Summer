/*************************************************************************
	> File Name: my_ls.h
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月22日 星期五 14时44分39秒
 ************************************************************************/

#ifndef _MY_LS_H
#define _MY_LS_H
#define PARAM_NONE 1
#define PARAM_A   2
#define PARAM_L 3
#define PARAM_R 4
#define PARAM_U 8
#define PARAM_N 13

char mode[100][11];
char *name[100];
struct stat file[100],tem;
int a = 0;


int my_readir_rln(const char *path);
int my_readir_arlnu(const char *path);
int my_readir_arln(const char *path);
int my_readir_simple_ru(const char *path);
int my_readir_simple_r(const char *path);
int my_readir_simple_aru(const char *path);
int my_readir_arlu(const char *path);
int my_readir_simple_ar(const char *path);
int my_readir_arl(const char *path);
int my_readir_rlun(const char *path);
int my_readir_rlu(const char *path);
int my_readir_rl(const char *path);
int my_readir_not_a(const char *path);
int my_readir(const char *path);
int my_readir_simple_not_a(const char *path);
int my_readir_simple(const char *path);
void print_simple(int len);
void bubble_sort_simple(int len);
void bubble_sort(int len);
void change_mode_t(int len);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void print_n(int len);
void print(int len);
#endif
