
/**
 * @file IMTcpSocket.h
 * @brief 单例模式实现客户端通信套接字
 */

#ifndef IMTCPSOCKET_H
#define IMTCPSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

class IMTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    static IMTcpSocket* GetInstance(void)
    {
        static IMTcpSocket instance;
        return &instance;
    }

    static QHostAddress m_hostAddress;
    static uint16_t m_hostPort;

    void ConnectToHost();
    void LinkSuccess();
    bool isConnected();
    bool isError();
    void ShowSocketError(QAbstractSocket::SocketError error);

private:
    bool m_isConnected;
    bool m_isError;
private:
    void LinkSlotAndSignal(void);

    /// 避免误操作 delete 掉实例，如果返回实例的引用则不用考虑析构的位置
    ~IMTcpSocket(){}
    IMTcpSocket(QObject *parent = nullptr);
    IMTcpSocket(const IMTcpSocket&);
    IMTcpSocket& operator =(const IMTcpSocket&);

signals:

public slots:
};

#endif // IMTCPSOCKET_H
