#ifndef QAZ_H
#define QAZ_H

#include <QMainWindow>

namespace Ui {
class qaz;
}

class qaz : public QMainWindow
{
    Q_OBJECT

public:
    explicit qaz(QWidget *parent = 0);
    ~qaz();

private:
    Ui::qaz *ui;
};

#endif // QAZ_H
