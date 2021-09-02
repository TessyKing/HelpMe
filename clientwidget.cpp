#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <qhostaddress.h>
#include <loginform.h>

#include <QByteArray>
#include <QMessageBox>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    LoginForm::Instance()->show();

    setWindowTitle("客户端");

    tcpSocket = NULL;

    //分配空间，指定父对象
    tcpSocket = new QTcpSocket(this);

    //获取服务器IP和端口
    QString ip = "10.197.114.230";
    int port = 8888;
    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
    //成功连接至服务器
    connect(tcpSocket,&QTcpSocket::connected,[=](){
        connect(LoginForm::Instance()->GetBTNLogIn(),&QPushButton::clicked,[=](){
            QString str = "login###U:" + LoginForm::Instance()->GetUserName() + "$P:" + LoginForm::Instance()->GetPassWord();
            qDebug() << str;
            ui->btnLogIn->setEnabled(false);
            tcpSocket->write(str.toUtf8().data());
        });
    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        ui->btnLogIn->setEnabled(true);
        //获取对方发送的内容
        QByteArray array = tcpSocket->readAll();
        QString str = QString(array);
        QString title = GetSocketDataTitle(str);
        QString datas = GetSocketDatas(str);
        //返回内容为登录内容
        if(title.compare("login") == 0){
            //成功登录
            if(datas.compare("true") == 0){
                LoginForm::Instance()->SucLogIn();
            }
            //用户名或密码错误
            else{
                //qDebug() << "用户名或密码错误";
                QMessageBox::critical(this,"登录错误","用户名或密码错误");
            }
        }
    });

    connect(tcpSocket,&QTcpSocket::disconnected,[=](){
        qDebug() << tcpSocket->peerAddress().toString() + "断开连接";
        tcpSocket->disconnectFromHost();
    });

    /*测试代码*/

    /*测试代码*/
}

ClientWidget::~ClientWidget()
{
    delete ui;
}
//获取信息的标题
QString ClientWidget::GetSocketDataTitle(QString str){
    return str.mid(0,str.indexOf("###"));
}
//获取信息的内容
QString ClientWidget::GetSocketDatas(QString str){
    return str.mid(3+str.indexOf("###"));
}


//void ClientWidget::on_btnSend_clicked()
//{
//    if(tcpSocket == NULL)
//        return;
//    //获取编辑框内容
//    QString str =ui->textEditWrite->toPlainText();
//    //发送数据
//    tcpSocket->write(str.toUtf8().data());
//    //清空自己的编辑区
//    ui->textEditWrite->setText("");
//}

//void ClientWidget::on_btnClose_clicked()
//{
//    if(tcpSocket == NULL)
//        return;
//    //主动和客户端断开连接
//    tcpSocket->write("客户端已断开连接");
//    ui->textEditRead->append("已与服务器断开连接");
//    tcpSocket->disconnectFromHost();
//    tcpSocket->close();
//}
