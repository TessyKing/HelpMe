#include "loginform.h"
#include "ui_loginform.h"

#include "chooseform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

QString LoginForm::GetUserName(){
    return ui->lineEditUserName->text();
}

QString LoginForm::GetPassWord(){
    return  ui->lineEditPassWord->text();
}

void LoginForm::SucLogIn(){
        ChooseForm *chooseWidget = new ChooseForm();
        //选择界面
        //显示页面
        chooseWidget->show();
        //隐藏界面
        LoginForm::Instance()->hide();
}
QPushButton* LoginForm::GetBTNLogIn(){
    return ui->btnLogin;
}


LoginForm* LoginForm::m_pInstance = NULL;
