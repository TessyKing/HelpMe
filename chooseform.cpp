#include "chooseform.h"
#include "ui_chooseform.h"

ChooseForm::ChooseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseForm)
{
    ui->setupUi(this);

    //设置背景
    QImage *img = new QImage();
    img->load(":/picture/background.jpg");
    ui->Background->setPixmap( QPixmap::fromImage(*img));
    ui->Background->setScaledContents(true);
    ui->Background->resize( ui->Background->width(), ui->Background->height());
    this->setWindowTitle("“救救我”无人值守监控系统");

    //选择界面
    widgetSelect = new WidgetSelect();
    widgetSelect->resize(1200,900);
    connect( widgetSelect, &WidgetSelect::Signal_Select_To_Main, this, &ChooseForm::Slot_Select_To_Main );
}

ChooseForm::~ChooseForm()
{
    delete ui;
}

void ChooseForm::on_Check_clicked()
{
    this->hide();
    widgetSelect->show();
}

void ChooseForm::Slot_Select_To_Main()
{
    widgetSelect->close();
    this->show();
}

void ChooseForm::on_Quit_clicked()
{
    this->close();
}
