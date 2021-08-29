#include "qmonitorsocket.h"

QMonitorSocket::QMonitorSocket()
{
    tcpClient = new QTcpSocket(this);
    tcpClient->abort();
}

QMonitorSocket::~QMonitorSocket()
{
    tcpClient->abort();
    delete tcpClient;
}

void QMonitorSocket::ConnectServer()
{
    tcpClient->connectToHost(ip, port);
    if (tcpClient->waitForConnected(1000))
    {
        qDebug() << "connected.....";
        return;
    }
    qDebug("connect failed!");
}

void QMonitorSocket::DisconnectServer()
{
    qDebug() << "try to disconnect.....";
    tcpClient->disconnectFromHost();
    if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
    {
        qDebug() << "disconnected!";
        return;
    }
    qDebug() << "disconnect failed";
}


qint64 QMonitorSocket::SendData(const char *data, qint64 len)
{
    qDebug() << "sent data.....";
    qint64 slen = tcpClient->write(data, len);
    qDebug() << "send " << slen << " bytes";
    return slen;
}
