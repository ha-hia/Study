
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

    void RegisterID(UserInfor& input);
signals:
    void SigUiRegisterAgain();
private:
    void RegisterRequest();
    void UiRegisterAgain();

private:
    /// 保存传递过来的注册信息
    UserInfor m_userInfo;
    /// 单例，无需 delete，程序结束系统自动回收
    IMTcpSocket* registerSocket;
};

#endif // IMREGISTERCTRL_H
