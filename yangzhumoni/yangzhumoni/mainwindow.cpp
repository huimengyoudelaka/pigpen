#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   ui->setupUi(this);
    setFixedSize(1600,1000);  //设置固定窗口大小
    this->setWindowIcon(QPixmap(":/tubiao.png"));
    setWindowTitle("养猪大亨");  //设置窗口标题
    connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWindow::close); //设置退出游戏按钮  
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::read); //购买确认按钮
    MainWindow::show1();
    ui->label_23->setText(QString::number(time));
    connect(ui->pushButton_2,&QPushButton::clicked,this,MainWindow::pass); //时间按钮
    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::inquire_pig); //查询某只猪按钮
    connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWindow::inquire_pigpen); //查询某猪圈按钮
    connect(ui->pushButton_6,&QPushButton::clicked,this,&MainWindow::inquire_black); //查询黑猪按钮
    connect(ui->pushButton_7,&QPushButton::clicked,this,&MainWindow::inquire_small); //查询小花猪按钮
    connect(ui->pushButton_8,&QPushButton::clicked,this,&MainWindow::inquire_big);  //查询大花白猪按钮
    connect(ui->pushButton_10,&QPushButton::clicked,this,&MainWindow::fever0); //普通模式按钮
    connect(ui->pushButton_9,&QPushButton::clicked,this,&MainWindow::fever1); //猪瘟模式按钮
    connect(ui->pushButton_11,&QPushButton::clicked,this,&MainWindow::forecast); //猪瘟模式按钮
    connect(ui->pushButton_12,&QPushButton::clicked,this,&MainWindow::inject); //注射疫苗按钮
    ui->label_57->setPixmap(QPixmap(":/pig2.png"));

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
   ui->label_93->setText(QString::number(judge1()));
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
        show1();
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
}

void MainWindow::distribution()  //分配猪圈,随机生成猪的体重,若开启猪瘟模式，随机生成瘟猪
{
    pigpen *p1=head,*p2=NULL;
    int l=10,chance;
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
            if(fever==1)
            {
                chance=qrand()%100;
                if(chance<10) {p2->condition1[l]=time; p2->condition10[l]=time;}
            }
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
               if(fever==1)
               {
                   chance=qrand()%100;
                   if(chance<10) {p2->condition1[l]=time; p2->condition10[l]=time;}
               }
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
               if(fever==1)
               {
                   chance=qrand()%100;
                   if(chance<10) {p2->condition1[l]=time; p2->condition10[l]=time;}
               }
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
       time0+=1;
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
                    if(p1->condition1[n]!=0) p1->weight[n]=0;
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
                    if(p1->condition1[n]!=0) p1->weight[n]=0;
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
                    if(p1->condition1[n]!=0) p1->weight[n]=0;
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

void MainWindow::inquire_pig()   //查询某头猪
{
    pigpen *p=head;
    int a,b,d;
    float w;
    a= ui->lineEdit_6->text().toInt();
    b= ui->lineEdit_7->text().toInt();
    for(int c=0;c<100;c++)
    {
        if(p->number1==a)  break;
        p=p->next;
    }
    w=(p->weight[b])*0.2;
    ui->label_55->setText(QString::number(w));
    d=p->day[b];
    ui->label_54->setText(QString::number(d));
    if(p->variety[b]==1) ui->label_53->setText("黑猪");
    else if(p->variety[b]==2) ui->label_53->setText("小花猪");
    else if(p->variety[b]==3) ui->label_53->setText("大花白猪");
    else if(p->variety[b]==0) ui->label_53->setText("没有猪");
    if(p->condition1[b]==0) ui->label_56->setText("无");
    else if(p->condition1[b]!=0) ui->label_56->setText("有");

}

void MainWindow::inquire_pigpen() //查询猪圈
{
   int a,black=0,small=0,big=0,d=0,e=0,f=0;
   float g,h,i;
   pigpen *p=head;
   a= ui->lineEdit_8->text().toInt();
   for(int b=0;b<100;b++)
   {
       if(p->number1==a) break;
       p=p->next;
   }
   for(int c=0;c<10;c++)
   {
       if(p->variety[c]==1) { black++; d+=p->weight[c]; }
       else if(p->variety[c]==2) { small++; e+=p->weight[c]; }
       else if(p->variety[c]==3)  { big++; f+=p->weight[c]; }

   }
   g=d*0.2;
   h=e*0.2;
   i=f*0.2;
   ui->label_63->setText(QString::number(black));
   ui->label_64->setText(QString::number(small));
   ui->label_65->setText(QString::number(big));
   ui->label_67->setText(QString::number(g));
   ui->label_68->setText(QString::number(h));
   ui->label_69->setText(QString::number(i));

}

void MainWindow::inquire_black() //查询黑猪
{
   int n1=0,n2=0,n3=0,n4=0,n5=0,w1=0,w2=0,w3=0,w4=0,w5=0;
   pigpen *p=head;
   for(int a=0;a<100;a++)
   {
       for(int b=0;b<10;b++)
       {
           if(p->variety[b]==1)
           {
               if((p->day[b])<91) n1++;
               else if((p->day[b])>90&&(p->day[b])<181) n2++;
               else if((p->day[b])>180&&(p->day[b])<271) n3++;
               else if((p->day[b])>270&&(p->day[b])<361) n4++;
               else if((p->day[b])>360) n5++;
               if(p->weight[b]<=365) w1++;
               else if(p->weight[b]>365&&p->weight[b]<=730) w2++;
               else if(p->weight[b]>730&&p->weight[b]<=1095) w3++;
               else if(p->weight[b]>1095&&p->weight[b]<=1460) w4++;
               else if(p->weight[b]>1460&&p->weight[b]<=1830) w5++;
           }
       }
       p=p->next;
   }
   ui->label_82->setText(QString::number(w1));
   ui->label_83->setText(QString::number(w2));
   ui->label_84->setText(QString::number(w3));
   ui->label_85->setText(QString::number(w4));
   ui->label_86->setText(QString::number(w5));
   ui->label_87->setText(QString::number(n1));
   ui->label_88->setText(QString::number(n2));
   ui->label_89->setText(QString::number(n3));
   ui->label_90->setText(QString::number(n4));
   ui->label_91->setText(QString::number(n5));
}

void MainWindow::inquire_big() //查询大花白猪
{
    int n1=0,n2=0,n3=0,n4=0,n5=0,w1=0,w2=0,w3=0,w4=0,w5=0;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<10;b++)
        {
            if(p->variety[b]==3)
            {
                if((p->day[b])<91) n1++;
                else if((p->day[b])>90&&(p->day[b])<181) n2++;
                else if((p->day[b])>180&&(p->day[b])<271) n3++;
                else if((p->day[b])>270&&(p->day[b])<361) n4++;
                else if((p->day[b])>360) n5++;
                if(p->weight[b]<=365) w1++;
                else if(p->weight[b]>365&&p->weight[b]<=730) w2++;
                else if(p->weight[b]>730&&p->weight[b]<=1095) w3++;
                else if(p->weight[b]>1095&&p->weight[b]<=1460) w4++;
                else if(p->weight[b]>1460&&p->weight[b]<=1830) w5++;
            }
        }
        p=p->next;
    }
    ui->label_82->setText(QString::number(w1));
    ui->label_83->setText(QString::number(w2));
    ui->label_84->setText(QString::number(w3));
    ui->label_85->setText(QString::number(w4));
    ui->label_86->setText(QString::number(w5));
    ui->label_87->setText(QString::number(n1));
    ui->label_88->setText(QString::number(n2));
    ui->label_89->setText(QString::number(n3));
    ui->label_90->setText(QString::number(n4));
    ui->label_91->setText(QString::number(n5));
}

void MainWindow::inquire_small()  //查询小花猪
{
    int n1=0,n2=0,n3=0,n4=0,n5=0,w1=0,w2=0,w3=0,w4=0,w5=0;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<10;b++)
        {
            if(p->variety[b]==2)
            {
                if((p->day[b])<91) n1++;
                else if((p->day[b])>90&&(p->day[b])<181) n2++;
                else if((p->day[b])>180&&(p->day[b])<271) n3++;
                else if((p->day[b])>270&&(p->day[b])<361) n4++;
                else if((p->day[b])>360) n5++;
                if(p->weight[b]<=365) w1++;
                else if(p->weight[b]>365&&p->weight[b]<=730) w2++;
                else if(p->weight[b]>730&&p->weight[b]<=1095) w3++;
                else if(p->weight[b]>1095&&p->weight[b]<=1460) w4++;
                else if(p->weight[b]>1460&&p->weight[b]<=1830) w5++;
            }
        }
        p=p->next;
    }
    ui->label_82->setText(QString::number(w1));
    ui->label_83->setText(QString::number(w2));
    ui->label_84->setText(QString::number(w3));
    ui->label_85->setText(QString::number(w4));
    ui->label_86->setText(QString::number(w5));
    ui->label_87->setText(QString::number(n1));
    ui->label_88->setText(QString::number(n2));
    ui->label_89->setText(QString::number(n3));
    ui->label_90->setText(QString::number(n4));
    ui->label_91->setText(QString::number(n5));
}

int MainWindow::judge1() //判断是否存在瘟猪,返还瘟猪数目
{   int j=0;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<10;b++)
        {
            if(p->condition1[b]!=0) j++;
        }
        p=p->next;
    }
    return j;
}

int MainWindow::judge10()  //模拟
{
    int j=0;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
          for(int b=0;b<10;b++)
          {
            if(p->condition10[b]!=0) j++;
          }
          p=p->next;
    }
    return j;
}

void MainWindow::judge2() //判断是否传播猪瘟
{
    int spread_number;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<10;b++)
        {
            if(p->condition1[b]!=0&&p->condition1[b]<(time+1))
            {
              if(p->number1>0&&p->number1<99)
               {
                 spread_number=p->number1-1;
                 spread_middle(spread_number);
               }
              else if(p->number1==0)
              {
                  spread_left();
              }
              else if(p->number1==99)
              {
                  spread_right();
              }
            }
        }
        p=p->next;
    }
}

void MainWindow::judge20() //模拟
{
    int spread_number;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<10;b++)
        {
            if(p->condition10[b]!=0&&p->condition10[b]<(time0+1))
            {
              if(p->number1>0&&p->number1<99)
               {
                 spread_number=p->number1-1;
                 spread_middle0(spread_number);
               }
              else if(p->number1==0)
              {
                  spread_left0();
              }
              else if(p->number1==99)
              {
                  spread_right0();
              }
            }
        }
        p=p->next;
    }
}

void MainWindow::spread_middle(int a) //1到98
{
    int chance;
    pigpen *p=head;
    for(int b=0;b<100;b++)
    {
        if(p->number1==a) break;
        p=p->next;
    }
    for(int c=0;c<10;c++)
    {
        if(p->variety[c]!=0&&p->condition1[c]==0&&p->condition2[c]==0)
        {
            chance=qrand()%100;
            if(chance<15)
            {
                p->condition1[c]=(time+1);
                p->condition10[c]=(time+1);
            }
        }
    }
    p=p->next;
    for(int c=0;c<10;c++)
    {
        if(p->variety[c]!=0&&p->condition1[c]==0&&p->condition2[c]==0)
        {
            chance=qrand()%100;
            if(chance<50)
            {
                p->condition1[c]=(time+1);
                p->condition10[c]=(time+1);
            }
        }
    }
    p=p->next;
    for(int c=0;c<10;c++)
    {
        if(p->variety[c]!=0&&p->condition1[c]==0&&p->condition2[c]==0)
        {
            chance=qrand()%100;
            if(chance<15)
            {
                p->condition1[c]=(time+1);
                p->condition10[c]=(time+1);
            }
        }
    }
}

void MainWindow::spread_left() //0
{
    int chance;
    pigpen *p=head;
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition1[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<50)
            {
                p->condition1[a]=(time+1);
                p->condition10[a]=(time+1);
            }
        }
    }
    p=p->next;
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition1[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<15)
            {
                p->condition1[a]=(time+1);
                p->condition10[a]=(time+1);
            }
        }
    }
}

void MainWindow::spread_right() //99
{
    int chance;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        if(p->number1==98) break;
        p=p->next;
    }
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition1[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<15)
             {
                p->condition1[a]=(time+1);
                p->condition10[a]=(time+1);
             }
        }
    }
    p=p->next;
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition1[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<50)
               {
                p->condition10[a]=(time+1);
                p->condition1[a]=(time+1);
               }
        }
    }
}

void MainWindow::spread_middle0(int a) //1到98模拟
{
    int chance;
    pigpen *p=head;
    for(int b=0;b<100;b++)
    {
        if(p->number1==a) break;
        p=p->next;
    }
    for(int c=0;c<10;c++)
    {
        if(p->variety[c]!=0&&p->condition10[c]==0&&p->condition2[c]==0)
        {
            chance=qrand()%100;
            if(chance<15) p->condition10[c]=(time0+1);
        }
    }
    p=p->next;
    for(int c=0;c<10;c++)
    {
        if(p->variety[c]!=0&&p->condition10[c]==0&&p->condition2[c]==0)
        {
            chance=qrand()%100;
            if(chance<50) p->condition10[c]=(time0+1);
        }
    }
    p=p->next;
    for(int c=0;c<10;c++)
    {
        if(p->variety[c]!=0&&p->condition10[c]==0&&p->condition2[c]==0)
        {
            chance=qrand()%100;
            if(chance<15) p->condition10[c]=(time0+1);
        }
    }
}

void MainWindow::spread_left0() //0模拟
{
    int chance;
    pigpen *p=head;
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition10[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<50) p->condition10[a]=(time0+1);
        }
    }
    p=p->next;
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition10[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<15) p->condition10[a]=(time0+1);
        }
    }
}

void MainWindow::spread_right0() //99模拟
{
    int chance;
    pigpen *p=head;
    for(int a=0;a<100;a++)
    {
        if(p->number1==98) break;
        p=p->next;
    }
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition10[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<15) p->condition10[a]=(time0+1);
        }
    }
    p=p->next;
    for(int a=0;a<10;a++)
    {
        if(p->variety[a]!=0&&p->condition10[a]==0&&p->condition2[a]==0)
        {
            chance=qrand()%100;
            if(chance<50) p->condition10[a]=(time0+1);
        }
    }
}

void MainWindow::recover() //复原
{
    pigpen *p=head;
    for (int a=0;a<100;a++)
    {
        for (int b=0;b<10;b++)
        {
            p->condition10[b]=p->condition1[b];
        }
        p=p->next;
    }
}


void MainWindow::fever0()  //普通模式
{
    fever=0;
}

void MainWindow::fever1()  //猪瘟模式
{
    fever=1;
}

void MainWindow::forecast()  //预测
{
    if(judge1()==0||judge3()!=0)
    {
        ui->label_45->setText("无穷");
        ui->label_93->setText(QString::number(judge1()));
    }
    else if(judge1()==(black_quantity+big_quantity+small_quantity))
    {
        ui->label_45->setText("0");
        ui->label_93->setText(QString::number(judge1()));
    }
    else if(judge1()<(black_quantity+big_quantity+small_quantity)&&judge1()>0&&judge3()==0)
    {
        for(int k=1;k>0;k++)
        {
            judge20();
            time0++;
            forecast_time++;
            if(judge10()==(black_quantity+big_quantity+small_quantity)) break;
        }
        ui->label_45->setText(QString::number(forecast_time));
        forecast_time=0;
        time0=time;
        recover();
    }

}

int MainWindow::judge3()  //判断有无猪注射疫苗，返还注射数目
{
    pigpen *p=head;
    int i=0;
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<10;b++)
        {
            if(p->condition2[b]==1) i++;
        }
    }
    return i;
}

void MainWindow::inject()   //注射疫苗
{
    pigpen *p=head;
    int a=vaccine;
    for(int b=0;b<a;b++)
    {
        if(judge1()==0) break;
        for(int c=0;c<100;c++)
        {
            for(int d=0;d<10;d++)
            {
                if(p->condition1[d]!=0)
                {
                    p->condition1[d]=0;
                    p->condition10[d]=0;
                    p->condition2[d]=1;
                    vaccine--;
                }
            }
            p=p->next;
        }
    }
    show1();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);

    paint.setPen(Qt::black);

    paint.drawLine(0,600,1600,600);
    paint.drawLine(1200,0,1200,600);

}

void MainWindow::pass()  //时间的流逝
{
    passtime= ui->lineEdit_5->text().toInt();
    for(int j=0;j<passtime;j++)
       { if(judge1()<(black_quantity+big_quantity+small_quantity)&&judge1()>0)
            judge2();
         growth();
         if((time-1)%90==0)
            sale();
       }
    show1();
}

void MainWindow::show_time()  //显示时间
{
    ui->label_23->setText(QString::number(time));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
