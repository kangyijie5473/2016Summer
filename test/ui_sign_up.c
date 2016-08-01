/*************************************************************************
	> File Name: gtk3.c
	> Author: Jack Kang
	> Mail: xiyoulinux.kangyijie@gmail.com
	> Created Time: 2016年08月01日 星期一 20时52分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h>
int main(int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *button_no;
    GtkWidget *button_yes;
    GtkWidget *sep;
    GtkWidget *box,*box1,*box2,*box3,*box4;
    GtkWidget *label_user,*label_passwd,*label_passwd2;
    GtkWidget *label,*entry_user,*entry_passwd,*entry_passwd2;

    gtk_init(&argc,&argv);  // 初始化 

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);// 生成一个window 顶级
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_set_usize(GTK_WINDOW(window),350,440);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//设置位置
    gtk_window_set_title(GTK_WINDOW(window),"注册账号"); // 设置标题
    gtk_container_set_border_width(GTK_CONTAINER(window),40);//设置边界

    button_yes = gtk_button_new_with_label("确认");
    button_no = gtk_button_new_with_label("取消");

    entry_user = gtk_entry_new();
    entry_passwd = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_passwd),FALSE);
    entry_passwd2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_passwd2),FALSE);

    g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(gtk_main_quit),NULL); 
    g_signal_connect(G_OBJECT(button_no),"clicked",G_CALLBACK(gtk_widget_destroy),window);

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
    gtk_main();
}
