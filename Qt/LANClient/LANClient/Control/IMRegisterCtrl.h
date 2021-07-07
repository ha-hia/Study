
/**
 * @file IMRegisterCtrl.h
 * @brief 注册操作类，向服务器注册账号
 */
#ifndef IMREGISTERCTRL_H
#define IMREGISTERCTRL_H

#include "Control/IMTcpSocket.h"
#include "Control/IMConstant.h"
#include <QObject>

class IMRegisterCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMRegisterCtrl(QObject *parent = nullptr);

    void RegisterID(UserInfor* input);
signals:

public slots:

private:

};

#endif // IMREGISTERCTRL_H
