#include "widget.h"
#include "serialsender.h"
#include "serialreceiver.h"
#include "widgetselect.h"
#include "chooseform.h"
#include <loginform.h>
#include <clientwidget.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    ChooseForm *chooseWidget = new ChooseForm();
//    //选择界面
//    //显示页面
//    chooseWidget->show();
//    //隐藏界面
//    chooseWidget->hide();
    ClientWidget *cw = new ClientWidget();

    return a.exec();
}
