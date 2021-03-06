/*********************************************
File Name： IMLoginCtrl.h
Author： jet.F.R
Date： 2014.3.10
Description： 用于控制登录的类
Changes：
********************************************/

#ifndef IMLOGINCTRL_H
#define IMLOGINCTRL_H

#include <QObject>
#include "IMTcpSocket.h"
#include "IMConstant.h"

class IMTcpSocket;

/*************************************************
Class Name： IMLoginCtrl
Description: 用于控制登录的类
*************************************************/
class IMLoginCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMLoginCtrl(QObject *parent = nullptr);

    ~IMLoginCtrl();

    // 发送登录信息
    void login(const QString &id ,const QString & pwd = "",
                     const int status = ONLINE);
    // 获取密保信息
    void getQuestionAndAnswer(const QString &id);
    /// 断开连接，点击取消登陆时使用
    void AbortConnect();

signals:
    void getLoginMessgae(const QString &, bool isLogin = false, const UserInfor * me = nullptr);
    void getQuestionAndAnswerSuccess(const TempStrings & tmpStr);

public slots:
    // 改变登录信息
//    void changeLoginMessage(const QString &mes, bool isLogin);
    void ReturnSocketError(QAbstractSocket::SocketError error);


private slots:
    // 发送获取密保问题以及答案的请求
    void requestGetQuestionAndAnswer();
    // 发送登录请求
    void requestLogin();

    // 发送请求
    void sendRequest();

    // 读取信息
    void readMessage();

private:

private:
    int m_kind;

    IMTcpSocket *m_tcpSocket;
    LoginInformation m_loginInfo;
    UserInfor m_myself;
    TempStrings m_tempStr;
    QString m_id;
};

#endif // IMLOGINCTRL_H
