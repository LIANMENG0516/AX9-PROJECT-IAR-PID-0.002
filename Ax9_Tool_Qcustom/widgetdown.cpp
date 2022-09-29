#include "widgetdown.h"
#include "ui_widgetdown.h"

#include <QFileDialog>
#include <QDataStream>
#include <QDebug>


WidgetDown::WidgetDown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDown)
{
    ui->setupUi(this);
    this->setWindowTitle("firmware upgrade");
    this->setFixedSize(473, 179);
}

WidgetDown::~WidgetDown()
{
    delete ui;
}

void WidgetDown::on_btnOpenFile_clicked()
{
    QString curPath;
    QString filePath = QDir::currentPath();
    curPath = QFileDialog::getOpenFileName(this, "选择文件", filePath);
    ui->lineFeilPath->setText(curPath);
}

void WidgetDown::on_btnStart_clicked()
{
    ui->labUpgradeState->setText("正在升级...");
    ui->progressBar->setValue(0);

    QFile aFile(ui->lineFeilPath->text());
    aFile.open(QIODevice::ReadOnly);
    datByteArray = aFile.readAll();
    aFile.close();

    emit startXmodemSend(datByteArray);
}

void WidgetDown::changeProgressBarVal(int val)
{
    ui->progressBar->setValue(val);
}

void WidgetDown::changeUpgradeState(QString str)
{
    ui->labUpgradeState->setText(str);
}

void WidgetDown::on_btnClose_clicked()
{
    ui->labUpgradeState->setText("准备升级...");
    ui->progressBar->setValue(0);
    ui->lineFeilPath->clear();
    this->close();
}









