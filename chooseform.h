#ifndef CHOOSEFORM_H
#define CHOOSEFORM_H
#include "widgetselect.h"
#include <QWidget>

namespace Ui {
class ChooseForm;
}

class ChooseForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseForm(QWidget *parent = nullptr);
    ~ChooseForm();
    WidgetSelect *widgetSelect;
private slots:
    void on_Check_clicked();
    void Slot_Select_To_Main();
    void on_Quit_clicked();

private:
    Ui::ChooseForm *ui;
};

#endif // CHOOSEFORM_H
