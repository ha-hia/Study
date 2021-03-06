
/**
 * @file IMTcpSocket.h
 * @brief 实现客户端通信套接字
 */

#ifndef IMTCPSOCKET_H
#define IMTCPSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

class IMTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:

    static QHostAddress m_hostAddress;
    static uint16_t m_hostPort;

    void ConnectToHost();
    void LinkSuccess();
    void Disconnect();
    bool isConnected();
    bool isError();
    void ShowSocketError(QAbstractSocket::SocketError error);
public:
    ~IMTcpSocket()
    {
        qDebug() << "~IMTcpSocket";
    }
    IMTcpSocket(QObject *parent = nullptr);
private:
    bool m_isConnected;
    bool m_isError;
private:
    void LinkSlotAndSignal(void);

signals:

public slots:
};

#endif // IMTCPSOCKET_H
