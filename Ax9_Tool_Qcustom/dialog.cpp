#include "dialog.h"
#include "ui_dialog.h"

#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);      //启用样式背景绘制
    setAttribute(Qt::WA_TranslucentBackground); //背景透明

    setStyleSheet(
                  "QPushButton{"
                  "color:white;"
                  "background-color:green;"
                  "border-radius:5px;"
                  "}"

                  "QPushButton:pressed{"
                  "background-color:red;"
                  "}");

    ui->btnCancel->setStyleSheet("QPushButton{"
                                 "background-color:blue;"
                                 "border-radius:3px;"
                                  "}"

                                  "QPushButton:pressed{"
                                  "background-color:black;"
                                  "}");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pixmap;

    pixmap.load(":/image/r7.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    pixmap.load(":/image/r4.png");
    painter.drawPixmap(110, 40, 80, 80, pixmap);
}

void Dialog::on_btnLogIn_clicked()
{
    this->accept();
}


void Dialog::on_btnCancel_clicked()
{
    this->reject();
}
