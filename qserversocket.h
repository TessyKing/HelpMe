#ifndef QSERVERSOCKET_H
#define QSERVERSOCKET_H

#include <QObject>
#include <QWidget>
#include<QTcpSocket>
#include<QThread>
#include<QTcpServer>
#include<QNetworkInterface>
#include<QHostAddress>

class TcpSocket : public QTcpSocket
{
public:
    TcpSocket(QTcpSocket *parent = NULL): QTcpSocket(parent){}
    ~TcpSocket(){}

public slots:
    void ReadData();
    void onDisconnectedSlotThread();
    qint64 SendData(TcpSocket *socket,const char * data, qint64 len);
    QByteArray m_buffer;
};

void TcpSocket::ReadData()
{
    TcpSocket *socket = (TcpSocket*)sender();
    QByteArray buffer = socket->readAll();
    if(buffer.isEmpty())    return;
    qDebug()<<"ReadData:"<<buffer<<" in "<<QThread::currentThread();
    m_buffer.append(buffer);
    SendData(socket,buffer,buffer.size());//echo to sender
}

void TcpSocket::onDisconnectedSlotThread()
{
    qDebug()<<"onDisconnectedSlotThread.pid:"<<QThread::currentThread();
}

qint64 TcpSocket::SendData(TcpSocket* socket,const char * data, qint64 len)
{
    qint64 slen;
    slen=socket->write(data,len);
    qDebug()<<"SendData len:"<<slen<<"data:"<<data;
    return slen;
}

class QServerSocket:public QObject
{
public:
    QList<QHostAddress> localaddrs;
    QServerSocket(QWidget *parent = 0):QObject(parent)
    {
        tcpServer = new QTcpServer(this);
        localaddrs = QNetworkInterface::allAddresses();
        foreach(QHostAddress ha, localaddrs)
        {
            qDebug()<<ha.toString();
        }
        ip = "127.0.0.1";
        port = 8888;

        connect(tcpServer, &QTcpServer::newConnection, this, &QServerSocket::NewConnectionSlot);
    }

    ~QServerSocket()
    {
        delete tcpServer;
    }
public:
    QHostAddress ip;
    quint16 port;
    bool SvStart();
private:
    QTcpServer *tcpServer;

public slots:
    void NewConnectionSlot();
};
#endif // QSERVERSOCKET_H
