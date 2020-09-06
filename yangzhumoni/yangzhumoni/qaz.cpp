#include "qaz.h"
#include "ui_qaz.h"

qaz::qaz(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qaz)
{
    ui->setupUi(this);
}

qaz::~qaz()
{
    delete ui;
}
