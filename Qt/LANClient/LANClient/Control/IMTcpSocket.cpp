#include "IMTcpSocket.h"
#include <QMessageBox>

QHostAddress IMTcpSocket::m_hostAddress = QHostAddress::Any;
uint16_t IMTcpSocket::m_hostPort = 0;

IMTcpSocket::IMTcpSocket(QObject *parent) : QTcpSocket(parent)
{
  m_isConnected = false;
  m_isError = false;
  LinkSlotAndSignal();
}

void IMTcpSocket::LinkSlotAndSignal()
{
    connect(this, &IMTcpSocket::connected, this, &IMTcpSocket::LinkSuccess);

    /// 信号重载，使用函数指针指定
    void(QAbstractSocket::*ptr)(QAbstractSocket::SocketError) = &QAbstractSocket::error;
    connect(this, ptr, this, &IMTcpSocket::ShowSocketError);
//    connect(this, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
//          this, &IMTcpSocket::ShowSocketError);

}

/**
 * @brief 放弃当前网络连接，向服务器发起连接
 * @param 客户端在注册、登录时根据extand窗口的输入决定服务器的地址
 */
void IMTcpSocket::ConnectToHost()
{
    this->abort();
    this->connectToHost(this->m_hostAddress, this->m_hostPort);
//    qDebug() << this->error();
}

void IMTcpSocket::LinkSuccess()
{
    qDebug() << __FILE__ << "," << __LINE__ << "LinkSuccess";
    m_isConnected = true;
}

bool IMTcpSocket::isConnected()
{
    return m_isConnected;
}

bool IMTcpSocket::isError()
{
    return m_isError;
}

void IMTcpSocket::ShowSocketError(QAbstractSocket::SocketError error)
{
    m_isConnected = false;
    m_isError = true;
//    qDebug() << this->error();
//    QMessageBox::information(nullptr, tr("IM Client"),
//                             tr("Error occurred: %1.")
//                             .arg(errorString()));

    switch (error)
    {
    case QAbstractSocket::RemoteHostClosedError:
        //emit showConnectionStatus(tr("链接失败.可能是因为服务器关闭."));
        QMessageBox::information(nullptr, tr("IM Client"),
                                 tr("The remote host closed the connection.") );
        break;
    case QAbstractSocket::HostNotFoundError:
        //emit showConnectionStatus(tr("链接失败.可能是因为找不到服务器"));
        QMessageBox::information(nullptr, tr("IM Client"),
                                 tr("This host was not found.Please check the"
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        //emit showConnectionStatus(tr("链接失败.可能是因为连接被拒绝"));
        QMessageBox::information(nullptr, tr("IM Client"),
                                 tr("The connection was refused by the peer."
                                    "Make sure the IM server is running,"
                                    "and check that the host name and port"
                                    "settings are correct."));
        break;
    default:
        //emit showConnectionStatus(tr("链接失败: %1.").arg(errorString()));
        QMessageBox::information(nullptr, tr("IM Client"),
                                 tr("The following errot occurred: %1.")
                                 .arg(errorString()));
    }
}
