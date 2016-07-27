/*************************************************************************
	> File Name: fun-arrow.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月27日 星期三 16时38分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double add(double a, double b){
    return a+b;    
}
double sub(double a,double b){
    return a-b;
}
double mul(double a, double b){
    return a*b;    
}
double my_div(double a, double b){
    return a/b;
}

double (*oper_fun[])(double a, double b) = {add, sub, mul, my_div};

int main(void){
    
    double a,b,result;
    char opera;
    int i;
    
    scanf("%lf%c%lf",&a,&opera,&b);
    
    for(i = 0; "+-*/"[i] != opera && i < strlen("+-*/"); i++);
    
    if(i == strlen("+-*/")){
        printf("error\n");
        return 0;
    }

    result = oper_fun[i](a,b);
    
    printf("%lf %c %lf = %lf\n",a,opera,b,result);
    return 0;
}
