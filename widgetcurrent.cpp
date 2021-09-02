#include "widgetcurrent.h"
#include "ui_widgetcurrent.h"
#include "serialreceiver.h"
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include "patient.h"
WidgetCurrent::WidgetCurrent( int comStart, QString name, QString date, QString pic_str, int age, int number, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::WidgetCurrent)
{
    //主UI设计
    ui->setupUi(this);
    this->setStyleSheet("background-color: black");
    this->setWindowFlag( Qt::FramelessWindowHint );

    //UI对应信息显示
    QImage *img = new QImage();
    img->load(pic_str);
    ui->photo->setPixmap( QPixmap::fromImage(*img));
    ui->photo->setScaledContents(true);
    ui->photo->resize( ui->photo->width(), ui->photo->height());
    ui->name->setText( "姓名：" + name );
    ui->date->setText( "入院日期：" + date );
    ui->age->setText( "年龄：" + QString::number(age, 10) );
    ui->number->setText( "住院号：" + QString::number(number, 10) );


    //ECG
    //发送和接受串口
    senderECG = new SerialSender( 1, "COM" + QString::number(comStart,10), nullptr );//发送数据用的串口
    receiverECG = new SerialReceiver( "COM" + QString::number(comStart+1,10), nullptr );//接收数据用的串口
    //对应三个波形ECG、SpO2、RESP
    drawECG = new DrawWave( ui->ECGWave, QColor("#7FFF00"), QColor("#808080") );//绘制波形
    showECG = new ShowData( ui->ECGData, "#7FFF00", "#808080" );//实时数值
    //连接波形和串口
    connect( receiverECG, &SerialReceiver::Signal_ECG_Received, drawECG, &DrawWave::Slot_Data_Handle );//每秒实时波形数据
    connect( receiverECG, &SerialReceiver::Signal_BPM_Received, showECG, &ShowData::Slot_Data_Handle );//每分钟心率


    //SpO2
    senderSpO2 = new SerialSender( 2, "COM" + QString::number(comStart+2,10), nullptr );
    receiverSpO2 = new SerialReceiver( "COM" + QString::number(comStart+3,10), nullptr );//接收数据用的串口
    drawSpO2 = new DrawWave( ui->SpO2Wave, QColor("#FFFF00"), QColor("#778899") );
    showSpO2 = new ShowData( ui->SpO2Data, "#FFFF00", "#778899" );
    connect( receiverSpO2, &SerialReceiver::Signal_ECG_Received, drawSpO2, &DrawWave::Slot_Data_Handle );//每秒实时波形数据
    connect( receiverSpO2, &SerialReceiver::Signal_BPM_Received, showSpO2, &ShowData::Slot_Data_Handle );//每分钟心率

    //RESP
    senderRESP = new SerialSender( 3, "COM" + QString::number(comStart+4,10), nullptr );
    receiverRESP = new SerialReceiver( "COM" + QString::number(comStart+5,10), nullptr );//接收数据用的串口
    drawRESP = new DrawWave( ui->RESPWave, QColor("#7FFF00"), QColor("#808080") );
    showRESP = new ShowData( ui->RESPData, "#7FFF00", "#808080" );
    connect( receiverRESP, &SerialReceiver::Signal_ECG_Received, drawRESP, &DrawWave::Slot_Data_Handle );//每秒实时波形数据
    connect( receiverRESP, &SerialReceiver::Signal_BPM_Received, showRESP, &ShowData::Slot_Data_Handle );//每分钟心率

    //右上角时钟
    LCDClock_Display( this );

    //对应历史界面
    widgetHistory = new WidgetHistory( comStart,  name,  date, pic_str, age, number, parent);
    connect( widgetHistory, &WidgetHistory::Signal_History_To_Current, this, &WidgetCurrent::Slot_History_To_Current);//进入历史界面

}

WidgetCurrent::~WidgetCurrent()
{
    delete ui;
}

void WidgetCurrent::LCDClock_Display(QWidget *widget)//时钟显示
{
    QTimer *timer = new QTimer( widget );
    timer->start( 1000 );
    connect( timer, &QTimer::timeout, this, &WidgetCurrent::LCDClock_Refresh );

}

void WidgetCurrent::LCDClock_Refresh()//时钟更新
{
    QDateTime dataTime = QDateTime::currentDateTime();
    ui->dateClock->setDigitCount(10);
    ui->dateClock->display( dataTime.toString( "yyyy-MM-dd" ) );
    ui->timeClock->setDigitCount(8);
    ui->timeClock->display( dataTime.toString( "hh:mm:ss" ));
}


void WidgetCurrent::Slot_History_To_Current()//历史界面到当前界面
{
    widgetHistory->hide();
    this->show();
}


//void WidgetCurrent::Slot_Draw_Wave( int data )//从串口接受波形发送给波形绘制函数DrawWave
//{
//    emit Signal_Draw( data );
//}

//void WidgetCurrent::Slot_Show_Data( int data )//从串口接受数值发送给数值显示函数ShowData
//{
//    emit Signal_Show( data );
//}


void WidgetCurrent::on_backButton_clicked()//返回按钮
{
    emit Signal_Current_To_Select();
}


void WidgetCurrent::on_historyButton_clicked()//历史界面按钮
{
    this->hide();
    widgetHistory->show();
}
