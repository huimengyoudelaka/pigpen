#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct pigpen
    {   int number1,number3,number4; //猪圈序号以及里面的猪的数目和模拟数目
        int variety[10],number2[10],condition1[10],condition2[10],day[10],weight[10],variety0[10],condition10[10]; //依次为种类，序号，健康状态（1为是否有猪瘟，2为是否打过疫苗，饲养天数,体重）,模拟种类，模拟是否有猪瘟
        pigpen *next;
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int passtime=0,time=0,money=300000,black_quantity=0,big_quantity=0,small_quantity=0,vaccine=0,buy_quantity1=0,buy_quantity2=0,buy_quantity3=0,buy_quantity4=0;
    pigpen *create();
    int weigh1=0,weigh2=0,weigh3=0;
    float total=0.0,weigh4=0.0,weigh5=0.0,weigh6=0.0;
    pigpen *head=create();
    void show1();
    void read();
    void pay();
    void distribution();
    void pass();
    void show_time();
    void growth();
    void sale();
    void show2();
    int distribution0();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
