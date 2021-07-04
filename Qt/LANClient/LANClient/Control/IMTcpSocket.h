#ifndef IMTCPSOCKET_H
#define IMTCPSOCKET_H

#include <QTcpSocket>

class IMTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit IMTcpSocket(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IMTCPSOCKET_H
