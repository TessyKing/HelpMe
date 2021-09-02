#include "qserversocket.h"
#include<QIODevice>
#include<QAbstractSocket>
#include<QThread>
#include <sqlpatientsmgr.h>

void QServerSocket::NewConnectionSlot()
{
    qDebug()<<"New Connection Slot coming...";
    QTcpSocket *socket = tcpServer->nextPendingConnection();
    qDebug()<<"ip:"<<socket->peerAddress().toString()<<":"<<socket->peerPort();
    //建立新线程来处理后续数据
    TcpSocket *threadSocket= new TcpSocket();
    threadSocket->setSocketDescriptor(socket->socketDescriptor());
    QThread *thread = new QThread(threadSocket);
    connect(threadSocket, &QAbstractSocket::disconnected, thread, &QThread::quit);
    connect(threadSocket, &QAbstractSocket::disconnected, threadSocket, &TcpSocket::onDisconnectedSlotThread);
    connect(threadSocket, &QIODevice::readyRead, threadSocket, &TcpSocket::ReadData);
    threadSocket->moveToThread(thread);
    thread->start();
}

bool QServerSocket::SvStart()
{
    qDebug()<<"try to start tcpserver at"<<ip.toString()<<":"<<port;
    bool ok = tcpServer->listen(ip, port);
     if(ok)
         qDebug("tcp server started!");
     else
         qDebug("tcp server start failed!");
     return ok;
}


