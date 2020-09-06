#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   ui->setupUi(this);
    setFixedSize(1200,700);  //设置固定窗口大小
    setWindowTitle("养猪模拟器");  //设置窗口标题
    connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWindow::close); //设置退出游戏按钮  
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::read); //购买确认按钮
    MainWindow::show1();
    ui->label_23->setText(QString::number(time));    
    connect(ui->pushButton_2,&QPushButton::clicked,this,MainWindow::pass); //时间按钮
}
MainWindow::pigpen *MainWindow::create()     //创建猪圈的链表，且一开始猪圈中没有猪
{   pigpen *p1,*p2,*head=NULL;
    p1=new pigpen;
    head=p1;
    for(int q=0;q<100;q++)
     {  for(int p=0;p<10;p++)
         { p1->number2[p]=p;
           p1->condition1[p]=0; //0代表无猪瘟，1代表有猪瘟
           p1->condition10[p]=0;
           p1->variety[p]=0;
           p1->variety0[p]=0;//0,1,2,3分别代表没有猪，黑猪，小花猪，大花白猪
           p1->condition2[p]=0; //0代表未打疫苗，1代表打过疫苗
           p1->weight[p]=0;
          }
        p2=p1;
        p1->number1=q;
        p1->number3=0;
        p1->number4=0;
        if(q<99) {p1=new pigpen; p2->next=p1;}
        if(q==99) p1->next=NULL;
     }
    return head;
}

void MainWindow::show1()   //显示右侧部分数值
{
   ui->label_18->setText(QString::number(money));
   ui->label_19->setText(QString::number(black_quantity));
   ui->label_21->setText(QString::number(big_quantity));
   ui->label_20->setText(QString::number(small_quantity));
   ui->label_22->setText(QString::number(vaccine));
}

void MainWindow::read()  //读取购买清单
{
    buy_quantity1 = ui->lineEdit_2->text().toInt();
    buy_quantity2 = ui->lineEdit_3->text().toInt();
    buy_quantity3 = ui->lineEdit_4->text().toInt();
    buy_quantity4 = ui->lineEdit->text().toInt();    
    if(distribution0()==0)
    {
        black_quantity+=buy_quantity1;
        big_quantity+=buy_quantity2;
        small_quantity+=buy_quantity3;
        vaccine+=buy_quantity4;
        pay();
        distribution();
    }
    else
    {
       QMessageBox::critical(this,"警告","猪圈位置不够了！");
    }
    buy_quantity1=0;
    buy_quantity2=0;
    buy_quantity3=0;
    buy_quantity4=0;
}

void MainWindow::pay()   //支付
{
    money-=(buy_quantity1*800+buy_quantity2*400+buy_quantity3*600+buy_quantity4*500);
    show1();
}

void MainWindow::distribution()  //分配猪圈,随机生成猪的体重
{
    pigpen *p1=head,*p2=NULL;
    int l=10;
    for(int j=0;j<buy_quantity1;j++)
      {
        for(int k=0;k<100;k++)
          {  if(p1->variety[0]==0||p1->variety[0]==1)
             { if(p1->number3<l)
                {   l=p1->number3;    p2=p1;       }
             }
             if(k<99) p1=p1->next;
          }
        if(p2!=NULL)
         {  p2->variety[l]=1;
            p2->variety0[l]=1;
            p2->weight[l]=200+qrand()%301;
            p2->number3++;
            p2->number4++;
         }
        p1=head;
        p2=NULL;
        l=10;
      }
    for(int j=0;j<buy_quantity2;j++)
      {
        for(int k=0;k<100;k++)
          {  if(p1->variety[0]!=1)
             {
               if(p1->number3<l)
                {   l=p1->number3;    p2=p1;       }
             }
             if(k<99) p1=p1->next;
          }
        if(p2!=NULL)
             { p2->variety[l]=3;
               p2->variety0[l]=3;
               p2->weight[l]=200+qrand()%301;
               p2->number3++;
               p2->number4++;
             }
        p1=head;
        p2=NULL;
        l=10;
      }
    for(int j=0;j<buy_quantity3;j++)
      {
        for(int k=0;k<100;k++)
          {  if(p1->variety[0]!=1)
             {
               if(p1->number3<l)
                {   l=p1->number3;    p2=p1;       }
             }
             if(k<99) p1=p1->next;
          }
        if(p2!=NULL)
             { p2->variety[l]=2;
               p2->variety0[l]=2;
               p2->weight[l]=200+qrand()%301;
               p2->number3++;
               p2->number4++;
             }
        p1=head;
        p2=NULL;
        l=10;
     }
}

void MainWindow::growth()  //猪的生长以及游戏时长的增长
{
    pigpen *p1;
       p1=head;
       for(int n=0;n<100;n++)
         {  if(p1->number3!=0)
                for(int m=0;m<10;m++)
                {
                  if(p1->variety[m]!=0)   { p1->weight[m]+=qrand()%13;( p1->day[m])++;}
                  if(p1->variety[m]==0)    break;
                }
            if(n<99) p1=p1->next;
         }
       time+=1;
       show_time();
}

void MainWindow::sale()   //出售猪
{   pigpen *p1=head;
    int r;
    for(int m=0;m<100;m++)
    {
        for(int n=0;n<10;n++)
        {
            if(p1->weight[n]>750||p1->day[n]>360)
            {
                if(p1->variety[n]==1)
                {   black_quantity--;
                    weigh1+=p1->weight[n];
                    p1->number3--;
                    p1->number4--;
                    r=p1->number3;
                    for(int k=n;k<r;k++)
                     {  p1->condition1[k]=p1->condition1[k+1];
                        p1->condition2[k]=p1->condition2[k+1];
                        p1->day[k]=p1->day[k+1];
                        p1->variety[k]=p1->variety[k+1];
                        p1->weight[k]=p1->weight[k+1];
                        p1->variety0[k]=p1->variety0[k+1];
                        p1->condition10[k]=p1->condition10[k+1];
                     }
                    p1->condition1[r]=0;
                    p1->condition2[r]=0;
                    p1->day[r]=0;
                    p1->variety[r]=0;
                    p1->weight[r]=0;
                    p1->variety0[r]=0;
                    p1->condition10[r]=0;
                }
                else if(p1->variety[n]==2)
                {   small_quantity--;
                    weigh2+=p1->weight[n];
                    p1->number3--;
                    p1->number4--;
                    r=p1->number3;
                    for(int k=n;k<r;k++)
                     {  p1->condition1[k]=p1->condition1[k+1];
                        p1->condition2[k]=p1->condition2[k+1];
                        p1->day[k]=p1->day[k+1];
                        p1->variety[k]=p1->variety[k+1];
                        p1->weight[k]=p1->weight[k+1];
                        p1->variety0[k]=p1->variety0[k+1];
                        p1->condition10[k]=p1->condition10[k+1];
                     }
                    p1->condition1[r]=0;
                    p1->condition2[r]=0;
                    p1->day[r]=0;
                    p1->variety[r]=0;
                    p1->weight[r]=0;
                    p1->variety0[r]=0;
                    p1->condition10[r]=0;
                }
                else if(p1->variety[n]==3)
                {   big_quantity--;
                    weigh3+=p1->weight[n];
                    p1->number3--;
                    p1->number4--;
                    r=p1->number3;
                    for(int k=n;k<r;k++)
                     {  p1->condition1[k]=p1->condition1[k+1];
                        p1->condition2[k]=p1->condition2[k+1];
                        p1->day[k]=p1->day[k+1];
                        p1->variety[k]=p1->variety[k+1];
                        p1->weight[k]=p1->weight[k+1];
                        p1->variety0[k]=p1->variety0[k+1];
                        p1->condition10[k]=p1->condition10[k+1];
                     }
                    p1->condition1[r]=0;
                    p1->condition2[r]=0;
                    p1->day[r]=0;
                    p1->variety[r]=0;
                    p1->weight[r]=0;
                    p1->variety0[r]=0;
                    p1->condition10[r]=0;
                }
                n--;
            }
        }
        if(m<99) p1=p1->next;
    }
    total=weigh1*3+weigh2*1.4+weigh3*1.2;
    weigh4=weigh1*0.2;
    weigh5=weigh2*0.2;
    weigh6=weigh3*0.2;
    if(money<0&&(-100000)<money) money*=1.1;
    else if(money>(-500000)&&(-100000)>=money) money*=1.08;
    else if(money>(-100000)&&(-500000)>=money) money*=1.05;
    else if((-1000000)>=money) money*=1.01;
    money+=total;
    show1();
    show2();
    total=0.0;
    weigh1=0;
    weigh2=0;
    weigh3=0;
}

void MainWindow::show2()        //显示出售的各类猪的总重量以及总收益
{
    ui->label_39->setText(QString::number(weigh4));
    ui->label_40->setText(QString::number(weigh5));
    ui->label_41->setText(QString::number(weigh6));
    ui->label_42->setText(QString::number(total));
}

int MainWindow::distribution0()   //模拟分配
{
    pigpen *p1=head,*p2=NULL;
    int l=10,s=0;
    for(int j=0;j<buy_quantity1;j++)
      {
        for(int k=0;k<100;k++)
          {  if(p1->variety0[0]==0||p1->variety0[0]==1)
             { if((p1->number4)<l)
                {   l=p1->number4;    p2=p1;       }
             }
             if(k<99) p1=p1->next;
          }
        if(p2!=NULL)
           { p2->variety0[l]=1; (p2->number4)++;}
        if(p2==NULL)
            s++;
        p1=head;
        p2=NULL;
        l=10;
      }
    for(int x=0;x<buy_quantity2;x++)
      {
        for(int y=0;y<100;y++)
          {  if(p1->variety0[0]!=1)
             {
               if((p1->number4)<l)
                {   l=p1->number4;    p2=p1;       }
             }
             if(y<99) p1=p1->next;
          }
        if(p2!=NULL)
           { p2->variety0[l]=3; (p2->number4)++;}
        if(p2==NULL)
            s++;
        p1=head;
        p2=NULL;
        l=10;
      }
    for(int m=0;m<buy_quantity3;m++)
      {
        for(int n=0;n<100;n++)
          {  if(p1->variety0[0]!=1)
             {
               if((p1->number4)<l)
                {   l=p1->number4;    p2=p1;       }
             }
             if(n<99) p1=p1->next;
          }
        if(p2!=NULL)
          { p2->variety0[l]=2;  (p2->number4)++;}
        if(p2==NULL)
           s++;
        p1=head;
        p2=NULL;
        l=10;
     }
    for(int w=0;w<100;w++)
     {
        for(int d=0;d<10;d++)
        {
            p1->variety0[d]=p1->variety[d];
        }
        p1->number4=p1->number3;
        if(w<99) p1=p1->next;
     }
    return s;
}

void MainWindow::pass()  //时间的流逝
{
    passtime= ui->lineEdit_5->text().toInt();
    for(int j=0;j<passtime;j++)
       { growth();
         if(time%90==0)
            sale();
       }
}

void MainWindow::show_time()  //显示时间
{
    ui->label_23->setText(QString::number(time));
}
MainWindow::~MainWindow()
{
    delete ui;
}

