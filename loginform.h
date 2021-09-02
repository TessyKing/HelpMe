#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    static LoginForm* Instance()
    {
        if (m_pInstance == NULL)
        {
            m_pInstance = new LoginForm();
        }
        return m_pInstance;
    }

    //获得用户名文本内容
    QString GetUserName();
    //获得密码文本内容
    QString GetPassWord();
    //成功登录时调用，进入操作页面
    void SucLogIn();
    //获取登录按钮
    QPushButton* GetBTNLogIn();


private:
    Ui::LoginForm *ui;

    explicit LoginForm(QWidget *parent = nullptr);

    ~LoginForm();
    static LoginForm* m_pInstance;
};

#endif // LOGINFORM_H
