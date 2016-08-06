/*************************************************************************
	> File Name: gtk3.c
	> Author: Jack Kang
	> Mail: xiyoulinux.kangyijie@gmail.com
	> Created Time: 2016年08月01日 星期一 20时52分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<gtk/gtk.h>
#include<time.h>

#define BUFFERSIZE 256
#define TEXTBUFFER   256
#define ENTRYBUFFER  20

#define _SUCCESS  0
#define _FAIL     -1

#define ONLINE  10
#define ABSENCS 11
#define BAN     12

#define NORMAL  13
#define MANAGER 14

#define SIGNUP 50
#define SIGNIN 51

#define CHAT_ALL 52
#define CHST_ONE 53
#define FTP      54
#define USRMANGE 55

#define EOR_NAME 70
#define EOR_PAWD 71


typedef struct user_client{
    char name[20];
    char passwd[17];
    int flag;
}userClient;

typedef struct user_server{
    char name[20];
    short status;
    short identity;
    struct user_server *next;
}userServer;

struct user_server *pHead = NULL;

typedef struct Message{
    char name[20];
    char time[28];
    char text[TEXTBUFFER];
}message;

void get_time_message(struct Messsage *temp);

void chat_all(GtkWidget *widget , void *pointer);
void escape(GtkWidget *widget,gpointer a );
void sign_up(GtkWidget *widget1, void *pointer);
void ftp(GtkWidget *widget1, void *pointer);
void feather(GtkWidget widget1, void *pointer);
int  go();
    GtkWidget *window_main;
    GtkWidget *entry_user;
    GtkWidget *entry_password;
void show(GtkWidget *a, void *p)
{
    gtk_widget_show(p);
    //gtk_widget_destroy(window_test);
}
/*
void close1(GtkWidget *a, void *p)
{
    gtk_widget_show(p);
    gtk_widget_destroy(window_test);
}
*/
void close2(GtkWidget *w, void *p)
{
    gtk_widget_destroy((GtkWidget *)p);
}


void sign_up(GtkWidget *widget1, void *pointer)
{

    GtkWidget *window;
    GtkWidget *button_no;
    GtkWidget *button_yes;
    GtkWidget *sep;
    GtkWidget *box,*box1,*box2,*box3,*box4;
    GtkWidget *label_user,*label_passwd,*label_passwd2;
    GtkWidget *label,*entry_user,*entry_passwd,*entry_passwd2;

    gtk_widget_hide(pointer);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);// 生成一个window 顶级
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_set_usize(GTK_WIDGET(window),350,440);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//设置位置
    gtk_window_set_title(GTK_WINDOW(window),"注册账号"); // 设置标题
    gtk_container_set_border_width(GTK_CONTAINER(window),40);//设置边界

    button_yes = gtk_button_new_with_label("确认");
    button_no = gtk_button_new_with_label("取消");

    entry_user = gtk_entry_new_with_max_length(20);
    entry_passwd = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_passwd),FALSE);
    entry_passwd2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_passwd2),FALSE);

    g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(gtk_main_quit),NULL); 
    g_signal_connect(G_OBJECT(button_no),"clicked",G_CALLBACK(close2),window);
    g_signal_connect(G_OBJECT(window),"destroy", G_CALLBACK(show),pointer);

    sep = gtk_hseparator_new();
    box = gtk_vbox_new(FALSE, 0);
    box1 = gtk_hbox_new(FALSE, 10);
    box2 = gtk_hbox_new(FALSE, 10);
    box3 = gtk_hbox_new(FALSE, 10);
    box4 = gtk_hbox_new(FALSE, 20);

    label = gtk_label_new("请输入用户名和密码");
    label_user = gtk_label_new("用户名： ");
    label_passwd = gtk_label_new("密码：    ");
    label_passwd2= gtk_label_new("确认密码:");

    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,10);
    
    gtk_container_add(GTK_CONTAINER(box1),label_user);
    gtk_container_add(GTK_CONTAINER(box1),entry_user);
    gtk_container_add(GTK_CONTAINER(box2),label_passwd);
    gtk_container_add(GTK_CONTAINER(box2),entry_passwd);
    gtk_container_add(GTK_CONTAINER(box3),label_passwd2);
    gtk_container_add(GTK_CONTAINER(box3),entry_passwd2);
    gtk_container_add(GTK_CONTAINER(box4),button_yes);
    gtk_container_add(GTK_CONTAINER(box4),button_no);
    gtk_container_add(GTK_CONTAINER(window),box);

    gtk_widget_show_all(window);
    
    //主循环
}


void escape(GtkWidget *widget,gpointer a )
{

    GtkWidget *window_test;
    GtkWidget *button_no;
    GtkWidget *button_yes;
    GtkWidget *sep;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *label1;

    window_test = gtk_window_new(GTK_WINDOW_TOPLEVEL);// 生成一个window 顶级
    gtk_window_set_resizable(GTK_WINDOW(window_test),FALSE);
    gtk_widget_set_usize(GTK_WIDGET(window_test),320,200);
    gtk_window_set_position(GTK_WINDOW(window_test),GTK_WIN_POS_CENTER);//设置位置
    gtk_container_set_border_width(GTK_CONTAINER(window_test),50);//设置边界
    button_yes = gtk_button_new_with_label("确认");
    button_no = gtk_button_new_with_label("取消");
    gtk_window_set_title(GTK_WINDOW(window_test),"确认框"); // 设置标题
    sep = gtk_hseparator_new();
    box = gtk_vbox_new(FALSE, 0);
    box1 = gtk_hbox_new(FALSE, 20);
    label1 = gtk_label_new("确认退出？");
    gtk_box_pack_start(GTK_BOX(box),label1,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,10);
    gtk_container_add(GTK_CONTAINER(box1),button_yes);
    gtk_container_add(GTK_CONTAINER(box1),button_no);
    gtk_container_add(GTK_CONTAINER(window_test),box);//将box添加到window
    //gtk_container_add(GTK_CONTAINER(window),box1);//将box添加到window
    
    //gtk_widget_hide(a);
    g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(gtk_main_quit),NULL); // 将退出信号连接
    g_signal_connect(G_OBJECT(button_no), "clicked",G_CALLBACK(close2),window_test);
    g_signal_connect(G_OBJECT(window_test), "destroy",G_CALLBACK(close2),window_test);
    //g_signal_connect_swapped(G_OBJECT(button_no),"clicked",G_CALLBACK(gtk_main_quit),NULL); 
    //g_signal_connect(G_OBJECT(button_no),"clicked",G_CALLBACK(gtk_widget_destroy),&window);
    gtk_widget_show_all(window_test);
    
}
const char *name;
const char *passwd;

int main(int argc, char *argv[])
{
    GtkWidget *button_signup;
    GtkWidget *button_signin;
    GtkWidget *sep;
    GtkWidget *label_user;
    GtkWidget *label_password;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;

    gtk_init(&argc,&argv);  // 初始化 
    window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);// 生成一个window_main 顶级
    gtk_window_set_title(GTK_WINDOW(window_main),"撩撩客户端"); // 设置标题
    gtk_container_set_border_width(GTK_CONTAINER(window_main),50);//设置边界
    gtk_window_set_resizable(GTK_WINDOW(window_main),FALSE);
    gtk_window_set_position(GTK_WINDOW(window_main),GTK_WIN_POS_CENTER);//设置位置
    gtk_widget_set_usize(GTK_WIDGET(window_main),380,234);

    box = gtk_vbox_new(FALSE,0);//一个box v表示垂直
    box1 = gtk_hbox_new(FALSE,20);// 一个box1 h表示水平
    box2 = gtk_hbox_new(FALSE,20);//同box1
    box3 = gtk_hbox_new(FALSE,30);
    
    sep = gtk_hseparator_new();//设置条分割线
    
    button_signup = gtk_button_new_with_label("注册");
    button_signin = gtk_button_new_with_label("登陆");
    
    label_user = gtk_label_new("账  号:");//设置一个标签
    entry_user = gtk_entry_new_with_max_length(20);
    label_password = gtk_label_new("密  码:");
    entry_password = gtk_entry_new_with_max_length(20);
    gtk_entry_set_visibility(GTK_ENTRY(entry_password),FALSE);
    
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);//将box1放到box里
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),label_user,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),entry_user,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),label_password,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),entry_password,FALSE,FALSE,5);
    
    gtk_container_add(GTK_CONTAINER(window_main),box);//将box添加到window_main
    gtk_container_add(GTK_CONTAINER(box3),button_signup);
    gtk_container_add(GTK_CONTAINER(box3),button_signin);

    g_signal_connect(G_OBJECT(button_signin),"clicked",G_CALLBACK(ftp),window_main); 
    
   // g_signal_connect(G_OBJECT(button_signup),"clicked",G_CALLBACK(sign_up),window_main); 
   // g_signal_connect(G_OBJECT(button_signin),"clicked",G_CALLBACK(test),NULL); // 将退出信号连接
    g_signal_connect(G_OBJECT(window_main),"delete_event",G_CALLBACK(escape),NULL); // 弹出一个确认框 



    //显示window_main及其包含的控件
    gtk_widget_show_all(window_main);
    //主循环
    gtk_main();
}
    
void feather(GtkWidget widget1, void *pointer)
{
    GtkWidget *window,*button1,*button2,*button3, *button4;
    GtkWidget *box,*sep,*label,*picture,*label2,*sep2;
    int socket_fd;

    button1 = gtk_button_new_with_label("进入聊天室");
    button2 = gtk_button_new_with_label("发起私聊");
    button3 = gtk_button_new_with_label("FTP");
    button4 = gtk_button_new_with_label("用户管理");

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"功能选择");
    gtk_widget_set_usize(GTK_WIDGET(window),300,650);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),40);

    box = gtk_vbox_new(FALSE, 0); 
    sep = gtk_hseparator_new();
    sep2 = gtk_hseparator_new();
    label = gtk_label_new("欢迎来撩，快去撩撩吧");
    picture = gtk_image_new_from_file("linux3.jpg");
    label2 = gtk_label_new("designed by Jack Kang ");

    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button4,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),picture,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),label2,FALSE,FALSE,10);

    g_signal_connect(G_OBJECT(button3),"clicked",G_CALLBACK(ftp),NULL);
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(chat_all),NULL);
    //gtk_window_set_destroy_with_parent(window,FALSE);
    ////g_signal_connect_swapped(G_OBJECT,"clicked",G_CALLBACK(gtk_))
    
    gtk_container_add(GTK_CONTAINER(window), box);
    if((socket_fd = go()) != 0){
        gtk_widget_destroy(window_main);
        gtk_widget_show_all(window);
        
    }else {
        xit(1);
    }
}



void ftp(GtkWidget *widget1, void *pointer)
{
    GtkWidget *window,*button1,*button2,*button3, *button4;
    GtkWidget *box,*sep,*label,*picture,*label2,*sep2,*box2,*sep3;
    GtkWidget *label_on,*label_dowm;
    GtkWidget *entry_on,*filew;

    button1 = gtk_button_new_with_label("确认上传");
    button2 = gtk_button_new_with_label("下载");
    button3 = gtk_button_new_with_label("请选择你要上传的文件")

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"欢迎使用FTP");
    gtk_widget_set_usize(GTK_WIDGET(window),500,650);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),40);

    box = gtk_vbox_new(FALSE, 0); 
    box2 = gtk_hbox_new(FALSE, 0);
    sep = gtk_hseparator_new();
    sep2 = gtk_hseparator_new();
    sep3 = gtk_hseparator_new();
    label = gtk_label_new("尽情share你的资源吧！");
    picture = gtk_image_new_from_file("linux4.jpg");
    label2 = gtk_label_new("\t\tdesigned by Jack Kang ");
    label_dowm = gtk_label_new("请输入要下载文件的文件名");
    entry_on = gtk_entry_new_with_max_length(256);
    filew = 


    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),entry_on,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),picture,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}

void chat_all(GtkWidget *widget , void *pointer)
{
    GtkWidget *window,*button_history,*button_yes,*button_fresh;
    GtkWidget *box,*sep,*label,*picture,*box4,*box2,*box3;
    GtkWidget *box5, *box6;
    GtkWidget *entry;
    GtkWidget *scrolli_left,*text_view_left;
    GtkWidget *scrolli_right,*text_view_right;

    button_yes = gtk_button_new_with_label("确认");
    button_history = gtk_button_new_with_label("历史记录");
    button_fresh  = gtk_button_new_with_label("刷新");

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"公共聊天室");
    gtk_widget_set_usize(GTK_WIDGET(window),800,800);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),40);

    box = gtk_vbox_new(FALSE, 0); 
    box2 = gtk_vbox_new(FALSE, 0);
    box3 = gtk_hbox_new(FALSE, 100);
    box4 = gtk_hbox_new(FALSE, 0);
    box5 = gtk_vbox_new(FALSE, 0);
    box6 = gtk_hbox_new(TRUE, 130);
    sep = gtk_hseparator_new();
    label = gtk_label_new("                               享受free的聊天吧！                              ");
    picture = gtk_image_new_from_file("linux4.jpg");
    entry = gtk_entry_new_with_max_length(256);
    scrolli_left = gtk_scrolled_window_new(NULL, NULL);
    text_view_left = gtk_text_view_new();
    scrolli_right = gtk_scrolled_window_new(NULL, NULL);
    text_view_right = gtk_text_view_new();


    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_left), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_right), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolli_left), text_view_left);
    gtk_container_add(GTK_CONTAINER(scrolli_right), text_view_right);
    gtk_widget_set_size_request(scrolli_left,500,400);
    gtk_widget_set_size_request(scrolli_right,200,350);
    gtk_widget_set_size_request(button_yes,100,50);
    gtk_widget_set_size_request(entry,250,70);



    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box6,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),sep,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box3),box2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box3),picture,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box4),scrolli_left,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box4),box5,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box5),button_history,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),button_fresh,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),scrolli_right,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box6),entry,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box6),button_yes,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}


void chat_single(GtkWidget *widget , void *pointer)
{
    GtkWidget *window,*button_history,*button_yes,*button_fresh;
    GtkWidget *box,*sep,*label,*picture,*box4,*box2,*box3;
    GtkWidget *box5, *box6;
    GtkWidget *entry;
    GtkWidget *scrolli_left,*text_view_left;
    GtkWidget *scrolli_right,*text_view_right;

    button_yes = gtk_button_new_with_label("确认");
    button_history = gtk_button_new_with_label("历史记录");
    button_fresh  = gtk_button_new_with_label("刷新");

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"公共聊天室");
    gtk_widget_set_usize(GTK_WIDGET(window),800,800);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),40);

    box = gtk_vbox_new(FALSE, 0); 
    box2 = gtk_vbox_new(FALSE, 0);
    box3 = gtk_hbox_new(FALSE, 100);
    box4 = gtk_hbox_new(FALSE, 0);
    box5 = gtk_vbox_new(FALSE, 0);
    box6 = gtk_hbox_new(TRUE, 130);
    sep = gtk_hseparator_new();
    label = gtk_label_new("                               享受free的聊天吧！                              ");
    picture = gtk_image_new_from_file("linux4.jpg");
    entry = gtk_entry_new_with_max_length(256);
    scrolli_left = gtk_scrolled_window_new(NULL, NULL);
    text_view_left = gtk_text_view_new();
    scrolli_right = gtk_scrolled_window_new(NULL, NULL);
    text_view_right = gtk_text_view_new();

 
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_left), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_right), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolli_left), text_view_left);
    gtk_container_add(GTK_CONTAINER(scrolli_right), text_view_right);
    gtk_widget_set_size_request(scrolli_left,500,400);
    gtk_widget_set_size_request(scrolli_right,200,350);
    gtk_widget_set_size_request(button_yes,100,50);
    gtk_widget_set_size_request(entry,250,70);



    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box6,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),sep,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box3),box2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box3),picture,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box4),scrolli_left,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box4),box5,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box5),button_history,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),button_fresh,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),scrolli_right,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box6),entry,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box6),button_yes,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}

int  go(void)
{
    int socket_fd,temp;
    pid_t pid;
    //char buffer[32] = "123.206.65.225", send_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];
    char buffer[32] = "127.0.0.1", send_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];
    unsigned long int address = 0;
    struct sockaddr_in server_addr;
    struct in_addr in;
    userClient *p;
    char serverFlag[20];
    GtkWidget *p1;
    
    name = gtk_entry_get_text(GTK_ENTRY(entry_user));
    passwd = gtk_entry_get_text(GTK_ENTRY(entry_password));
    p = (userClient *)malloc(sizeof(userClient));
    strcpy(p -> name, name);
    strcpy(p -> passwd,passwd);
    p -> flag = SIGNIN;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4507);
    
    //fgets(buffer, 31, stdin);
    //buffer[31] = '\0';
    //fgets(send_buffer, BUFFERSIZE, stdin);

    inet_aton(buffer, &server_addr.sin_addr);

    if((temp = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) < 0){
        printf("%d\n",temp);
        perror("connect");
        exit(1);
    }else{
        /*
                if((temp = send(socket_fd, p,sizeof(userClient), 0) )< 0){
                    printf("%d",temp);
                    perror("send");
                    exit(1);}
                   */ 
        pid = fork();
        wait(&temp);
        while(1){
            if(pid < 0){
                perror("fork");
                exit(1);
            }
            if(pid == 0){
                if(send(socket_fd, p,sizeof(userClient), 0) < 0){
                    perror("send");
                    exit(1);
                }else{
                    exit(0);
                }
            }
            if(pid > 0){
                read(socket_fd, serverFlag,20);
                printf("****%s*****\n",serverFlag);
                     if(strcmp(serverFlag,"success") == 0){
                         break;
                     }
                     return 0;
            }
    }
     //   printf("%d",temp);
    return socket_fd ;
    }
}
