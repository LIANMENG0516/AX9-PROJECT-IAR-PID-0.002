#ifndef WIDGETDOWN_H
#define WIDGETDOWN_H

#include <QWidget>

#include "serialportthread.h"

namespace Ui {
class WidgetDown;
}

class WidgetDown : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDown(QWidget *parent = 0);
    ~WidgetDown();

private slots:
    void on_btnOpenFile_clicked();
    void on_btnStart_clicked();

    void on_btnClose_clicked();

private:
    Ui::WidgetDown *ui;

private:
    SerialPortThread *serialPort;
    QByteArray datByteArray;

signals:
    void startXmodemSend(QByteArray);

public:
    void changeProgressBarVal(int);
    void changeUpgradeState(QString);
};

#endif // WIDGETDOWN_H
