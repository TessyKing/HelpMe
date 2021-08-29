#ifndef QMONITORSOCKET_H
#define QMONITORSOCKET_H

#include <QObject>
#include <QWidget>
#include<QTcpSocket>
#include<QHostAddress>

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
    qint64 SendData(const char *data, qint64 len);
    void DisconnectServer();
};

#endif // QMONITORSOCKET_H
