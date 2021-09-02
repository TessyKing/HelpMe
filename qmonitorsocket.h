#ifndef QMONITORSOCKET_H
#define QMONITORSOCKET_H

#include <QObject>
#include <QWidget>
#include<QTcpSocket>
#include<QHostAddress>
#include<sqlpatientsmgr.h>

class QMonitorSocket : public QTcpSocket
{
    Q_OBJECT
public:
    QMonitorSocket();
    QTcpSocket *tcpClient;
    ~QMonitorSocket();
    QHostAddress ip;
    qint16 port;
    void ConnectServer();
    void SendData(PatientData data);
    void DisconnectServer();
    PatientData RecvData(QByteArray ba);
};

#endif // QMONITORSOCKET_H
