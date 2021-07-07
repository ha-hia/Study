#include "IMTcpSocket.h"

IMTcpSocket::IMTcpSocket(QObject *parent) : QTcpSocket(parent)
{
  m_isConnected = false;
  LinkSlotAndSignal();
}

void IMTcpSocket::LinkSlotAndSignal()
{
    connect(this, &IMTcpSocket::connected, this, &IMTcpSocket::LinkSuccess);
}


void IMTcpSocket::ConnectToHost()
{
    this->abort();
    this->connectToHost(this->m_hostAddress, this->m_hostPort);
}

void IMTcpSocket::LinkSuccess()
{
    m_isConnected = true;
}
