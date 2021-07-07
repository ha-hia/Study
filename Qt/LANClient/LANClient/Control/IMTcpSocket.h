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

private:
    bool m_isConnected;
private:
    void LinkSlotAndSignal(void);
    IMTcpSocket(QObject *parent = nullptr);
    IMTcpSocket(const IMTcpSocket&);
    IMTcpSocket& operator =(const IMTcpSocket&);

signals:

public slots:
};

QHostAddress IMTcpSocket::m_hostAddress = QHostAddress::Any;
uint16_t IMTcpSocket::m_hostPort = 0;

#endif // IMTCPSOCKET_H
