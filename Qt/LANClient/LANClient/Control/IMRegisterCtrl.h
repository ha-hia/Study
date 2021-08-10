
/**
 * @file IMRegisterCtrl.h
 * @brief 注册操作类，向服务器注册账号
 */
#ifndef IMREGISTERCTRL_H
#define IMREGISTERCTRL_H

#include "Control/IMTcpSocket.h"
#include "Control/IMConstant.h"
#include <QObject>
#include <QString>

class IMRegisterCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMRegisterCtrl(QObject *parent = nullptr);
    ~IMRegisterCtrl();

    void RegisterID(UserInfor& input);
signals:
    void sigRegisterFailed();
    void sigGetRegiterRet(QString& res);
private:
    void RegisterRequest();
    void RegisterFailed();
    void RegisterResult();
private:
    /// 保存传递过来的注册信息
    UserInfor m_userInfo;
    ///
    IMTcpSocket* registerSocket;
};

#endif // IMREGISTERCTRL_H
