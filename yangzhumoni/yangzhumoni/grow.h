#ifndef GROW_H
#define GROW_H

#include <QObject>

class grow : public QObject
{
    Q_OBJECT
public:
    explicit grow(QObject *parent = nullptr);

signals:

public slots:
     void growth();
};

#endif // GROW_H
