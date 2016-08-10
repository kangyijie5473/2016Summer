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
#include<sys/stat.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<gtk/gtk.h>
#include<time.h>
#include<pthread.h>
#include<wait.h>
#include<fcntl.h>
#include"demo/chatroom.h"
void select_file(GtkWidget *widget , void * pointer);
void chat_single(GtkWidget *widget , void *pointer);
void *recv_single();
void *recv_all(void *arg);
void send_file(GtkWidget *w, void *pointer);
void show_history(GtkWidget *w, void *pointer);

void send_entry(GtkWidget *w, void *entry);
void chat_all(GtkWidget *widget , void *pointer);
void escape(GtkWidget *widget,gpointer a );
void sign_up(GtkWidget *widget1, void *pointer);
void ftp(GtkWidget *widget1, void *pointer);
void feather(GtkWidget widget1, void *pointer);
int  go();
void fresh_file(GtkWidget *w,void *pointer);
void down_file(GtkWidget *w, void * pointer);
const int lenMessage = sizeof(message);
const int lenUserClient = sizeof(userClient) ;
GtkWidget *window_main;
GtkWidget *entry_user;
GtkWidget *entry_password;
GtkTextBuffer *text_buffer_all,*text_buffer_single, *file_buffer, *down_buffer, *history_buffer;
GtkWidget *scrolli_left_single,*text_view_left_single;
GtkWidget *scrolli_right_single,*text_view_right_single;
GtkWidget *scrolli_left_all,*text_view_left_all;
GtkWidget *scrolli_right_all,*text_view_right_all;
GtkWidget *filew;
GtkWidget *scrolli_down, *text_view_down;
GtkWidget *scrolli_history, *text_view_history;
GtkWidget *entry_on;
int socket_fd; // client 唯一对应socket_fd
const char *name;
const char *passwd;
char username[20];
char filename[100];


/* 文件选择框退出*/
void select_file_quit(GtkWidget *a, void *p)
{
    gtk_widget_show(p);
    gtk_widget_destroy(filew);
}
/*显示隐藏的控件*/
void show(GtkWidget *a, void *p)
{
    gtk_widget_show(p);
}
/*ftp功能窗口退出*/
void ftp_quit(GtkWidget *w,void *pointer)
{
    userClient *p;
    p = (userClient *)malloc(lenUserClient);
    p -> flag = _FAIL;
    gtk_widget_show(pointer);
    write(socket_fd, p, lenUserClient);
    free(p);
    return ;
    
}
/**/
void fun_quit(GtkWidget *w,void *pointer)
{
    gtk_widget_show(pointer);
    message *m;
    m = (message * )malloc(lenMessage);
    strcpy(m -> text, "quit");
    write(socket_fd, m, lenMessage);
    
}

void close2(GtkWidget *w, void *p)
{
    gtk_widget_show(window_main);
    gtk_widget_destroy((GtkWidget *)p);
}

/*主功能窗口退出&client退出*/
void feather_quit(GtkWidget *w, void *pointer)
{
    userClient *p;
    p = (userClient *)malloc(lenUserClient);
    p -> flag = _FAIL;
    write(socket_fd, p, lenUserClient);
    gtk_main_quit();
    
}
/*注册窗口*/
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
    
}

/*退出前确认框*/
void escape(GtkWidget *widget,gpointer a )
{

    GtkWidget *window_test;
    GtkWidget *button_no;
    GtkWidget *button_yes;
    GtkWidget *sep;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *label1;

    gtk_widget_hide(widget);
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
    
    g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(gtk_main_quit),NULL); // 将退出信号连接
    g_signal_connect(G_OBJECT(button_no), "clicked",G_CALLBACK(close2),window_test);
    g_signal_connect(G_OBJECT(window_test), "destroy",G_CALLBACK(close2),window_test);
    gtk_widget_show_all(window_test);
    
}
/*登录界面*/
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

    g_signal_connect(G_OBJECT(button_signin),"clicked",G_CALLBACK(feather),window_main); 
    
    g_signal_connect(G_OBJECT(button_signup),"clicked",G_CALLBACK(sign_up),window_main); 
    g_signal_connect(G_OBJECT(window_main),"delete_event",G_CALLBACK(escape),NULL); // 弹出一个确认框 



    //显示window_main及其包含的控件
    gtk_widget_show_all(window_main);
    //主循环
    gtk_main();
}
/*主功能选择界面*/    
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

    g_signal_connect(G_OBJECT(button3),"clicked",G_CALLBACK(ftp),window);
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(chat_all),window);
    g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(chat_single),window);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(feather_quit),NULL);
    
    gtk_container_add(GTK_CONTAINER(window), box);
    if((socket_fd = go()) != 0){
        gtk_widget_destroy(window_main);
        gtk_widget_show_all(window);
        
    }else {
        exit(1);
    }
}


/*ftp功能选择界面*/
void ftp(GtkWidget *widget1, void *pointer)
{
    GtkWidget *window,*button1,*button2,*button3, *button4;
    GtkWidget *box,*sep,*label,*picture,*label2,*sep2,*box2,*sep3;
    GtkWidget *label_on,*label_dowm;

    gtk_widget_hide(pointer);

    button2 = gtk_button_new_with_label("查看服务器上的资源");
    button1 = gtk_button_new_with_label("确认下载");
    button3 = gtk_button_new_with_label("请选择你要上传的文件");

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
    scrolli_down = gtk_scrolled_window_new(NULL, NULL);
    text_view_down = gtk_text_view_new();

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_down), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolli_down,400,100);

    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),scrolli_down,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),entry_on,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),button3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),sep3,FALSE,FALSE,10);

    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),picture,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(scrolli_down),text_view_down);
    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(fresh_file),NULL);
    g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(down_file),entry_on); // entry bu yiding
    g_signal_connect(G_OBJECT(button3), "clicked",G_CALLBACK(select_file),window);
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(ftp_quit),pointer);
    
    userClient *p;
    p = (userClient *)malloc(lenUserClient);
    p -> flag = FTP;
    write(socket_fd, p, lenUserClient);
    
    gtk_widget_show_all(window);
}
/*下载文件到本地*/
void down_file(GtkWidget *w, void * pointer)
{
    const char *down_file_name;
    FILE *fp;
    userClient *p;
    message *m;
    char *mm;
    int i;
    p = (userClient *)malloc(lenUserClient);
    down_file_name = gtk_entry_get_text(GTK_ENTRY(pointer));
    strcpy(p -> name, down_file_name);
    p -> flag = DOWNFILE;
    write(socket_fd, p, lenUserClient);
    fp = fopen(down_file_name,"w+");
    m = (message *)malloc(lenMessage);
    do{
        memset(m,0,lenMessage);
        i = recv(socket_fd, m ,lenMessage,0);
        printf("%s\n",m -> text);
        fwrite(m ->text,strlen(m -> text),1,fp);
        printf("%d\n",i);
        if(strcmp(m -> name,"no file") == 0){
            printf("no such file \n");
            fclose(fp);
            return;
        }
        if(strcmp(m -> name, "finish") == 0){
            fclose(fp);
            return;
        }
    }while(1);
}
/*刷新 显示服务器可供下载的文件*/
void fresh_file(GtkWidget *w,void *pointer)
{
    userClient *p;
    GtkTextIter start,end;
    message *m;
    char *key;
    int i;
    char *PP;
    p = (userClient *)malloc(lenUserClient);
    m = (message *)malloc(lenMessage);
    p -> flag = FRESHFILE;
    write(socket_fd, p, lenUserClient);
    i = read(socket_fd, m , lenMessage);
    key = m -> text;
    
    for(i = 0; i < sizeof(m -> text); i++){
        key++;
        if(*key != 0)
        break;
    }
    down_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view_down));
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(down_buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(down_buffer),&end,key,strlen(key));
    free(m);
    free(p);
    return ;

}


/*选择要上传的文件&文件选择界面*/
void select_file(GtkWidget *widget , void * pointer)
{
    filew = gtk_file_selection_new("选择要上传的文件");
    gtk_widget_hide(pointer);
    g_signal_connect(G_OBJECT(filew), "destroy", G_CALLBACK(show),pointer);
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(filew) -> cancel_button), "clicked", G_CALLBACK(select_file_quit),pointer);
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(filew) -> ok_button),"clicked",G_CALLBACK(send_file),pointer);
    gtk_widget_show(filew);
}
/*上传文件至服务器*/
void send_file(GtkWidget *w, void *pointer)
{
    GtkTextIter start,end;
    const char *temp;
    const char *k;
    int fd,num;
    message *m;
    userClient *p;
    p = (userClient *)malloc(lenUserClient);
    temp = gtk_file_selection_get_filename(GTK_FILE_SELECTION(filew));
    strcpy(filename,temp);
    k = &temp[strlen(temp) - 1];
    while(*(--k) != '/'); 
    strcpy(p -> name,k+1);
    p -> flag = UPFILE;
    printf("%s\n",p -> name);
    write(socket_fd, p , lenUserClient);
    fd = open(filename,O_RDONLY);
    m = (message *)malloc(lenMessage);
    while(1){
        memset(m, 0, lenMessage);
        if((num = read(fd, m -> text, sizeof(m -> text))) == 0){
            break;
        }
        strcpy(m -> name, " ");
        printf("%s",m -> text);
        write(socket_fd, m , lenMessage);
    }
    memset(m, 0, lenMessage);
    strcpy(m -> name, "finish");
    write(socket_fd, m , lenMessage);
    free(m);

    gtk_widget_destroy(filew);
    gtk_widget_show(pointer);
}
/*群聊 接受并显示消息*/
void *recv_all(void *arg)
{
    message *m;
    GtkTextIter start,end;
    m = (message *)malloc(lenMessage);
    while(1){
        memset(m, 0, lenMessage);
        recv(socket_fd, m, lenMessage,0);
        text_buffer_all = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view_left_all));
        gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(text_buffer_all),&start,&end);
        m -> text[strlen(m -> text)] == '\0';

        gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_buffer_all),&end,m->time,strlen(m -> time));
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_buffer_all),&end,m-> name,strlen(m -> name));
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_buffer_all),&end,m->text,strlen(m -> text));
        printf("server: %s\n",m -> text);
    }
    free(m);
    return;
}
/*群聊 界面*/
void chat_all(GtkWidget *widget , void *pointer)
{
    GtkWidget *window,*button_history,*button_yes,*button_fresh;
    GtkWidget *box,*sep,*label,*picture,*box4,*box2,*box3;
    GtkWidget *box5, *box6;
    GtkWidget *entry;
    GtkWidget *scrolli_left,*text_view_left;
    GtkWidget *scrolli_right,*text_view_right;
    pthread_t pthid;

    gtk_widget_hide(pointer);

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
    scrolli_left_all = gtk_scrolled_window_new(NULL, NULL);
    text_view_left_all = gtk_text_view_new();
    scrolli_right_all = gtk_scrolled_window_new(NULL, NULL);
    text_view_right_all = gtk_text_view_new();


    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_left_all), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_right_all), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolli_left_all), text_view_left_all);
    gtk_container_add(GTK_CONTAINER(scrolli_right_all), text_view_right_all);
    gtk_widget_set_size_request(scrolli_left_all,500,400);
    gtk_widget_set_size_request(scrolli_right_all,200,350);
    gtk_widget_set_size_request(button_yes,100,50);
    gtk_widget_set_size_request(entry,250,70);



    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box6,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),sep,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box3),box2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box3),picture,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box4),scrolli_left_all,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box4),box5,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box5),button_history,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),button_fresh,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),scrolli_right_all,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box6),entry,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box6),button_yes,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(show), pointer);
    g_signal_connect(G_OBJECT(button_yes), "clicked" ,G_CALLBACK(send_entry), entry);
    g_signal_connect(G_OBJECT(button_history), "clicked", G_CALLBACK(show_history), pointer);
    g_signal_connect(G_OBJECT(button_fresh), "clicked" ,G_CALLBACK(show), pointer);



    userClient *p;
    p = (userClient *)malloc(lenUserClient);
    p -> flag = CHAT_ALL;
    write(socket_fd, p, lenUserClient);

    pthread_create(&pthid,NULL,recv_all,NULL);

    gtk_widget_show_all(window);
}
/*群聊 显示历史信息*/
void show_history(GtkWidget *w, void *pointer)
{
    GtkWidget *window;
    GtkTextIter start,end;
    message *m;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"历史记录");
    gtk_widget_set_usize(GTK_WIDGET(window),700,700);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),40);
    
    scrolli_history = gtk_scrolled_window_new(NULL, NULL);
    text_view_history  = gtk_text_view_new();
    history_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view_history));
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(history_buffer),&start,&end);

    m = (message *)malloc(lenMessage);
    strcpy(m -> text, "history");
    write(socket_fd, m ,lenMessage);
    while(1){
        memset(m, 0, lenMessage);
        read(socket_fd, m ,lenMessage);
        m -> text[strlen(m -> text)] == '\0';
        if(strcmp(m -> text, "finish") == 0)
            break;
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(history_buffer),&end,m->time,strlen(m -> time));
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(history_buffer),&end,m-> name,strlen(m -> name));
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(history_buffer),&end,m->text,strlen(m -> text));
        printf("server:%s\n",m -> text);
    }
    


    gtk_container_add(GTK_CONTAINER(scrolli_history),text_view_history);
    gtk_container_add(GTK_CONTAINER(window),scrolli_history);
    gtk_widget_show_all(window);
}

/*发送聊天消息*/
void send_entry(GtkWidget *w, void *entry)
{
    const char *a;
    message *m;
    m = (message *)malloc(lenMessage);
    a = gtk_entry_get_text(entry);
    strcpy(m -> text, a);
    printf("%s\n",m -> text);
    strcpy(m ->name,username);
    write(socket_fd, m, lenMessage);
    free(m);
    gtk_entry_set_text(GTK_ENTRY(entry), " ");
    return;
}
/*私聊界面*/
void chat_single(GtkWidget *widget , void *pointer)
{
    pthread_t pthid;
    GtkWidget *window,*button_history,*button_yes,*button_fresh, *button_add;
    GtkWidget *box,*sep,*label,*picture,*box4,*box2,*box3;
    GtkWidget *box5, *box6;
    GtkWidget *entry, *entry_add;

    gtk_widget_hide(pointer);

    button_yes = gtk_button_new_with_label("确认");
    button_history = gtk_button_new_with_label("历史记录");
    button_fresh  = gtk_button_new_with_label("刷新");
    button_add = gtk_button_new_with_label("添加好友来撩");


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"个人聊天室");
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
    label = gtk_label_new("                               享受open的聊天吧！                              ");
    picture = gtk_image_new_from_file("linux4.jpg");
    entry = gtk_entry_new_with_max_length(256);
    entry_add = gtk_entry_new_with_max_length(256);
    scrolli_left_single = gtk_scrolled_window_new(NULL, NULL);
    text_view_left_single = gtk_text_view_new();
    scrolli_right_single = gtk_scrolled_window_new(NULL, NULL);
    text_view_right_single = gtk_text_view_new();

 
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_left_single), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolli_right_single), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolli_left_single), text_view_left_single);
    gtk_container_add(GTK_CONTAINER(scrolli_right_single), text_view_right_single);
    gtk_widget_set_size_request(scrolli_left_single,500,400);
    gtk_widget_set_size_request(scrolli_right_single,200,250);
    gtk_widget_set_size_request(button_yes,100,50);
    gtk_widget_set_size_request(entry,250,70);



    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box6,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),sep,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box3),box2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box3),picture,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box4),scrolli_left_single,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box4),box5,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box5),button_history,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),button_fresh,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),scrolli_right_single,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),entry_add,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box5),button_add,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box6),entry,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box6),button_yes,FALSE,FALSE,10);

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(fun_quit), pointer);
    g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(send_entry), entry);

    gtk_container_add(GTK_CONTAINER(window), box);

    userClient *p;
    p = (userClient *)malloc(lenUserClient);
    p -> flag = CHAT_ONE;
    write(socket_fd, p, lenUserClient);

    pthread_create(&pthid,NULL,recv_single,NULL);
    
    gtk_widget_show_all(window);
}

void *recv_single(void *arg)
{
    message *m;
    GtkTextIter start,end;
        text_buffer_single = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view_left_single));
        gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(text_buffer_single),&start,&end);
        m = (message *)malloc(lenMessage);
    while(1){
        memset(m, 0, lenMessage);
        recv(socket_fd, m, lenMessage,0);
        m -> text[strlen(m -> text)] == '\0';

        //gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_buffer_single),&end,m->time,strlen(m -> time));
       // gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_buffer_single),&end,m-> name,strlen(m -> name));
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_buffer_single),&end,m->text,strlen(m -> text));
        printf("server:%s\n",m -> text);
    }
    free(m);
}
   
int  go(void)
{
    int temp;
    pid_t pid;
    char buffer[32] = "123.206.65.225", send_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];
    //char buffer[32] = "127.0.0.1", send_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];
    unsigned long int address = 0;
    struct sockaddr_in server_addr;
    struct in_addr in;
    userClient *p;
    char serverFlag[20];
    GtkWidget *p1;
    
    name = gtk_entry_get_text(GTK_ENTRY(entry_user));
    passwd = gtk_entry_get_text(GTK_ENTRY(entry_password));
    p = (userClient *)malloc(lenUserClient);
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
                if((temp = send(socket_fd, p,lenUserClient, 0) )< 0){
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
                if(send(socket_fd, p,lenUserClient, 0) < 0){
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
                         strcpy(username,"kang");
                         break;
                     }
                     return 0;
            }
    }
     //   printf("%d",temp);
    return socket_fd ;
    }
}
