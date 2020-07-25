#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(sendCommand()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sendCommand()
{
    quint32 fr = ui->frequency->toPlainText().toInt();

    QByteArray msg(9, 0x0);
    msg[0] = 0xFF;
    msg[1] = ui->packetLength->toPlainText().toInt();
    msg[2] = ui->bandwidth->currentIndex();
    msg[3] = ui->spreadingFactor->currentIndex();
    msg[4] = ui->codingRate->currentIndex();
    msg[8] = fr>>24 & 0xff;
    msg[7] = fr>>16 & 0xff;
    msg[6] = fr>>8 & 0xff;
    msg[5] = fr & 0xff;

    emit updateSettings(msg);
}
