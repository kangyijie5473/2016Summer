/*************************************************************************
	> File Name: login.c
	> Author: Kangyijie 
	> Mail:Kangyijie5473@gmail.com 
	> Created Time: 2016年07月16日 星期六 20时30分34秒
 ************************************************************************/

#include<gtk/gtk.h>


void test(GtkWidget *widget,gpointer a )
{

    GtkWidget *window;
    GtkWidget *button_no;
    GtkWidget *button_yes;
    GtkWidget *sep;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *label1;

   // gtk_init(&a,&b);  // 初始化 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);// 生成一个window 顶级
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_set_usize(GTK_WINDOW(window),320,200);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//设置位置
    gtk_container_set_border_width(GTK_CONTAINER(window),50);//设置边界
    button_yes = gtk_button_new_with_label("确认");
    button_no = gtk_button_new_with_label("取消");
    g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(gtk_main_quit),NULL); 
    g_signal_connect(G_OBJECT(button_no),"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_window_set_title(GTK_WINDOW(window),"确认框"); // 设置标题
    sep = gtk_hseparator_new();
    box = gtk_vbox_new(FALSE, 0);
    box1 = gtk_hbox_new(FALSE, 20);
    label1 = gtk_label_new("确认退出？");
    gtk_box_pack_start(GTK_BOX(box),label1,FALSE,FALSE,10);
    
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,10);
    gtk_container_add(GTK_CONTAINER(box1),button_yes);
    gtk_container_add(GTK_CONTAINER(box1),button_no);
    gtk_container_add(GTK_CONTAINER(window),box);//将box添加到window
    //gtk_container_add(GTK_CONTAINER(window),box1);//将box添加到window

    //g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL); // 将退出信号连接

    gtk_widget_show_all(window);
    
    //主循环
    gtk_main();
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *entry_user;
    GtkWidget *entry_password;
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
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);// 生成一个window 顶级
    gtk_window_set_title(GTK_WINDOW(window),"撩撩客户端"); // 设置标题
    gtk_container_set_border_width(GTK_CONTAINER(window),50);//设置边界
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//设置位置
    gtk_widget_set_usize(GTK_WINDOW(window),380,234);

    box = gtk_vbox_new(FALSE,0);//一个box v表示垂直
    box1 = gtk_hbox_new(FALSE,20);// 一个box1 h表示水平
    box2 = gtk_hbox_new(FALSE,20);//同box1
    box3 = gtk_hbox_new(FALSE,30);
    
    sep = gtk_hseparator_new();//设置条分割线
    
    button_signup = gtk_button_new_with_label("注册");
    button_signin = gtk_button_new_with_label("登陆");
    
    label_user = gtk_label_new("账  号:");//设置一个标签
    entry_user = gtk_entry_new();//设置一个输入框
    label_password = gtk_label_new("密  码:");
    entry_password = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_password),FALSE);
    
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);//将box1放到box里
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),label_user,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),entry_user,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),label_password,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),entry_password,FALSE,FALSE,5);
    
    gtk_container_add(GTK_CONTAINER(window),box);//将box添加到window
    gtk_container_add(GTK_CONTAINER(box3),button_signup);
    gtk_container_add(GTK_CONTAINER(box3),button_signin);

    g_signal_connect(G_OBJECT(button_signin),"clicked",G_CALLBACK(gtk_main_quit),NULL); 
    //g_signal_connect_swapped(G_OBJECT(button_signup),"clicked",G_CALLBACK(test),NULL); 
    //g_signal_connect(G_OBJECT(button_signup),"clicked",G_CALLBACK(),NULL); 
   // g_signal_connect(G_OBJECT(button_signin),"clicked",G_CALLBACK(test),NULL); // 将退出信号连接
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(test),NULL); // 



    //显示window及其包含的控件
    gtk_widget_show_all(window);
    //主循环
    gtk_main();
}
    
