
#include "Control/IMTcpSocket.h"
#include "IMRegisterCtrl.h"

#include <QAbstractSocket>


IMRegisterCtrl::IMRegisterCtrl(QObject *parent)
    : QObject(parent)
{
    registerSocket = IMTcpSocket::GetInstance();

    /// 成功连接，则向服务器发送注册请求
    connect(this->registerSocket, &IMTcpSocket::connected, this, &IMRegisterCtrl::RegisterRequest);

    /// 当连接出现错误，则再次显示注册界面
    void(QAbstractSocket::*ptr)(QAbstractSocket::SocketError) = &QAbstractSocket::error;
    connect(this->registerSocket, ptr, this, &IMRegisterCtrl::UiRegisterAgain);

}
/**
 * @brief 根据输入的 input 信息，向服务器注册账号 m
 */
void IMRegisterCtrl::RegisterID(UserInfor& input)
{
    m_userInfo = input;

    if(false == registerSocket->isConnected())
    {
        registerSocket->ConnectToHost();
    }
    else {
        RegisterRequest();
    }
}
/**
 * @brief 请求服务器注册
 */
void IMRegisterCtrl::RegisterRequest()
{
    qDebug() << "register to server...";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint16(0);
    out << int(REGISTER);
    out << m_userInfo;
    out.device()->seek(0);
    qDebug() << block.size();
    qDebug() << sizeof(quint16);
    out << quint16(block.size() - sizeof(quint16));

    registerSocket->write(block);
}

/**
 * @brief 发送信号，再次显示注册界面
 */
void IMRegisterCtrl::UiRegisterAgain()
{
    emit SigUiRegisterAgain();
}


