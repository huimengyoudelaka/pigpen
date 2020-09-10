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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
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
    void inquire_pig();
    void inquire_pigpen();
    void inquire_black();
    void inquire_big();
    void inquire_small();
    int judge1();
    int judge10();
    void judge2();
    void judge20();
    void spread_middle(int a);
    void spread_left();
    void spread_right();
    void spread_middle0(int a);
    void spread_left0();
    void spread_right0();
    void recover();
    void fever0();
    void fever1();
    void forecast();
    int judge3();
    void inject();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::MainWindow *ui;
    struct pigpen
    {   int number1,number3,number4; //猪圈序号以及里面的猪的数目和模拟数目
        int variety[10],number2[10],condition1[10],condition2[10],day[10],weight[10],variety0[10],condition10[10]; //依次为种类，序号，健康状态（1为是否有猪瘟，2为是否打过疫苗，饲养天数,体重）,模拟种类，模拟是否有猪瘟
        pigpen *next;
    };
    int fever=0,passtime=0,time=1,time0=1,forecast_time,money=300000,black_quantity=0,big_quantity=0,small_quantity=0,vaccine=0,buy_quantity1=0,buy_quantity2=0,buy_quantity3=0,buy_quantity4=0;
    pigpen *create();
    int weigh1=0,weigh2=0,weigh3=0; //出售的猪肉重量（转换前）
    float total=0.0,weigh4=0.0,weigh5=0.0,weigh6=0.0; //出售的猪肉重量（转换后）
    pigpen *head=create();

};

#endif // MAINWINDOW_H
