#ifndef PATIENT_H
#define PATIENT_H
#include "patientform.h"
#include "widgetcurrent.h"
#include <QWidget>

class Patient : public QWidget
{
    Q_OBJECT
public:
    explicit Patient( int comStart, QString name = "ssh", QString date = "feb", QString pic_str = ":/picture/P1.jpg", int age = 32, int number = 34, QWidget *parent = nullptr );
    PatientForm *patientForm;
    WidgetCurrent *widgetCurrent;
//    SerialReceiver *receiverECG;
//    SerialReceiver *receiverSpO2;
//    SerialReceiver *receiverRESP;
//    SerialSender *senderECG;
//    SerialSender *senderSpO2;
//    SerialSender *senderRESP;
signals:
    void Signal_Select_To_Current( Patient *patient );
    void Signal_Current_To_Select( Patient *patient );
private slots:
    void Slot_Select_To_Current();
    void Slot_Current_To_Select();
};

#endif // PATIENT_H
