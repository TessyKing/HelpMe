#include "qmonitorsocket.h"
#include<sqlpatientsmgr.h>
#include<QByteArray>
#include<QBuffer>
#include<QTcpSocket>

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

void QMonitorSocket::SendData(PatientData data)
{
    qDebug() << "send data.....";
    QByteArray ba;
    ba.append((char*)&data, sizeof(data));
    tcpClient->write(ba);
}

PatientData QMonitorSocket::RecvData(QByteArray ba)
{
    qDebug() << "recv data.....";
    PatientData *data = (PatientData*)ba.data();
    return *data;
}
