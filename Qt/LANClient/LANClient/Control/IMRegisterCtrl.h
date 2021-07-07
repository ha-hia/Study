#ifndef IMREGISTERCTRL_H
#define IMREGISTERCTRL_H

#include <QObject>

class IMRegisterCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMRegisterCtrl(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IMREGISTERCTRL_H