#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Ax9 Tool");
    //this->setFixedSize(1770, 952);
    this->setPalette(QPalette(Qt::gray));
    this->setAutoFillBackground(true);

    timerPlot = new QTimer;
    connect(timerPlot, &QTimer::timeout, this, &Widget::realTimeCruvePlot);

    initUiserialPort();
    iniUiWavePlot();

    serialPortThread = new SerialPortThread(this);
    connect(serialPortThread, &SerialPortThread::serialPortData, this, &Widget::serialPortDataSlot);

    widgetDown = new WidgetDown;
    connect(widgetDown, &WidgetDown::startXmodemSend, this, &Widget::startXmodemSlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUiserialPort()
{
    QStringList rateList = QStringList() << "4800" << "9600" << "38400" << "115200" << "320400" << "256000";
    ui->boxBadRate->addItems(rateList);
    ui->boxBadRate->setCurrentText("115200");

    QStringList dataBitList;
    dataBitList << "6 bit" << "7 bit" << "8 bit";
    ui->boxDatBits->addItems(dataBitList);
    ui->boxDatBits->setCurrentText("8 bit");

    QStringList stopBitList = {"1 bit", "1.5 bit", "2 bit"};
    ui->boxStpBits->addItems(stopBitList);
    ui->boxStpBits->setCurrentText("1 bit");

    QStringList partityList = {"None", "Odd", "Even"};
    ui->boxPartity->addItems(partityList);
    ui->boxPartity->setCurrentText("None");

    QStringList flowCtrlList = {"None", "Software", "Hardware"};
    ui->boxFlwCtrl->addItems(flowCtrlList);
    ui->boxFlwCtrl->setCurrentText("None");
}

void Widget::on_btnScan_clicked()
{
    QStringList strList;

    ui->boxPortNum->clear();

    strList = serialPortThread->scanSerialPort();

    for(int i=0; i<strList.count(); i++)
    {
        ui->boxPortNum->addItem(strList.at(i));
    }
}

void Widget::on_btnOpen_clicked()
{

    QString portNum = ui->boxPortNum->currentText();
    QString badRate = ui->boxBadRate->currentText();
    QString datBits = ui->boxDatBits->currentText();
    QString stpBits = ui->boxStpBits->currentText();
    QString partity = ui->boxPartity->currentText();
    QString flwCtrl = ui->boxFlwCtrl->currentText();

    bool openResult = serialPortThread->openSerialPort(portNum, badRate, datBits, stpBits, partity, flwCtrl);

    if(openResult == false)
    {
        QMessageBox::warning(this, "警告", "串口打开失败", QMessageBox::Ok);
    }
    else
    {
        ui->boxPortNum->setEnabled(0);
        ui->boxBadRate->setEnabled(0);
        ui->boxDatBits->setEnabled(0);
        ui->boxStpBits->setEnabled(0);
        ui->boxPartity->setEnabled(0);
        ui->boxFlwCtrl->setEnabled(0);
        ui->btnOpen->setEnabled(0);
        ui->btnClos->setEnabled(1);
        ui->btnSend->setEnabled(1);
    }

}

void Widget::on_btnClos_clicked()
{
    serialPortThread->closeSerialPort();

    ui->boxPortNum->setEnabled(1);
    ui->boxBadRate->setEnabled(1);
    ui->boxDatBits->setEnabled(1);
    ui->boxStpBits->setEnabled(1);
    ui->boxPartity->setEnabled(1);
    ui->boxFlwCtrl->setEnabled(1);
    ui->btnOpen->setEnabled(1);
    ui->btnClos->setEnabled(0);
    ui->btnSend->setEnabled(0);
}


void Widget::on_btnSend_clicked()
{
    QString sendStr;

    QByteArray sendbyteArray;

    sendStr = ui->textEditSend->toPlainText();

    if(ui->radioSendHex->isChecked())
    {
        sendbyteArray = QByteArray::fromHex(sendStr.toUtf8());
    }
    else
    {
        sendbyteArray = sendStr.toUtf8();
    }

    if(ui->chkNewLine->isChecked())
    {
        sendbyteArray.append("\r\n");
    }

    if(ui->chkSendRepeat->isChecked())
    {
        QTimer::singleShot(ui->spinRepatTime->value(), this, on_btnSend_clicked);
    }

    if(ui->chkRevDisplayTime->isChecked())
    {
        ui->textEditRev->appendPlainText(QDateTime::currentDateTime().toString("[hh:mm:ss:zzz]->"));

        if(ui->radioSendHex->isChecked())
        {
            QByteArray byteArray;
            byteArray = QByteArray::fromHex(sendStr.toUtf8().data());

            for(int i=0; i<byteArray.count(); i++)
            {
                quint8 data = (quint8)byteArray.at(i);
                ui->textEditRev->insertPlainText(QString("%1 ").arg(data, 2, 16, QLatin1Char('0')));
            }
        }
        else
        {
            ui->textEditRev->insertPlainText(sendStr);
        }
    }

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::serialPortDataSlot(QByteArray byteArray)
{
    QString str;
    QByteArray revByteArray = byteArray;


    if(!mWavePlotState && !xmodemFlag)
    {
        if(ui->radioRevHex->isChecked())
        {
            str = revByteArray.toHex(' ').data();
        }
        else
        {
            str = QString(revByteArray);
        }

        if(ui->chkRevDisplayTime->isChecked())
        {
            ui->textEditRev->appendPlainText(QDateTime::currentDateTime().toString("[hh:mm:ss:zzz]<-"));
        }

        ui->textEditRev->insertPlainText(str);
    }

    if(xmodemFlag == true)
    {
        static quint16 val = 0;
        static quint16 packNum = 0;

        switch(xmodemRevDataAnalysis(byteArray))
        {
            case beginTransimt:
            case runTransimt:
            {
                if(byteArrayFile.size() == 0)
                {
                    static int i = 0;

                    if(i == 0)
                    {
                        i++;
                        QByteArray byteFinish;
                        byteFinish.append(EOT);
                        serialPortThread->writeSerialPort(byteFinish);         //发送EOT

                        ui->textEditRev->appendPlainText("->");
                        ui->textEditRev->insertPlainText(QString("%1 ").arg(EOT, 2, 16, QLatin1Char('0')));
                    }
                    else
                    {
                        i--;
                        QByteArray byteQuery;
                        byteQuery.append(0x68);
                        byteQuery.append(0x11);
                        byteQuery.append(0x04);
                        byteQuery.append(0x01);
                        byteQuery.append(0xC0);
                        byteQuery.append(0x16);
                        serialPortThread->writeSerialPort(byteQuery);         //发送升级完成查询命令

                        ui->textEditRev->appendPlainText("->");
                        ui->textEditRev->insertPlainText(byteQuery.toHex(' ').data());
                    }

                    val = 0;
                }
                else
                {
                    qDebug() << byteArrayFile.count();

                    if(val <= 95)
                    {
                        widgetDown->changeProgressBarVal(val++);
                    }

                    if(packNum == 255)
                    {
                        packNum = 0;
                    }

                    xmod.Head = 0x01;
                    xmod.packNum = ++packNum;
                    xmod.numPack = 255 - packNum;

                    if(byteArrayFile.size() >= 128)
                    {
                        for(int i=0; i<128; i++)
                        {
                            xmod.data[i] = byteArrayFile[i];
                        }

                        byteArrayFile = byteArrayFile.right(byteArrayFile.size() - 128);
                    }
                    else
                    {
                        for(int i=0; i<128; i++)
                        {
                            if(i < byteArrayFile.size())
                            {
                                xmod.data[i] = byteArrayFile[i];
                            }
                            else
                            {
                                xmod.data[i] = 0x1A;
                            }
                        }

                        byteArrayFile.clear();
                    }

                    qint16 check = xmodemCalcrc(&xmod.data[0], 128);

                    xmod.chkHigh = check >> 8;
                    xmod.chkLow = check;

                    QByteArray byteArraySend;


                    byteArraySend.append(xmod.Head);
                    byteArraySend.append(xmod.packNum);
                    byteArraySend.append(xmod.numPack);
                    for(int i=0; i<128; i++)
                    {
                        byteArraySend.append(xmod.data[i]);
                    }
                    byteArraySend.append(xmod.chkHigh);
                    byteArraySend.append(xmod.chkLow);

                    serialPortThread->writeSerialPort(byteArraySend);
                    ui->textEditRev->appendPlainText("->");
                    ui->textEditRev->insertPlainText(byteArraySend.toHex().data());
                }

            }
            break;

            case repeatTransimt:                                        //接收到NAK, 重新传输
            {
                char *data = new char[133];
                memset(data, 0, sizeof(xmod));
                memcpy(data, &xmod ,sizeof(xmod));
                serialPortThread->writeSerialPortLen(data, 133);
                delete [] data;
            }
            break;

            case stopTransimt:                                          //接收到CAN，取消发送
            {
                byteArrayFile.clear();

            }
            break;

            case finishTransimt:                                        //接收到Finish，发送结束
            {
                byteArrayFile.clear();

                QByteArray byteRestart;
                byteRestart[0] = 0x68;
                byteRestart[1] = 0x04;
                byteRestart[2] = 0x07;
                byteRestart[3] = 0x01;
                byteRestart[4] = 0x00;
                byteRestart[5] = 0x0C;
                byteRestart[6] = 0x16;
                serialPortThread->writeSerialPort(byteRestart);           //发送MCU复位命令

                ui->textEditRev->appendPlainText("->");
                ui->textEditRev->insertPlainText(byteRestart.toHex(' ').data());

                widgetDown->changeProgressBarVal(100);
                widgetDown->changeUpgradeState("升级完成");

                xmodemFlag = false;
            }
            break;
        }
    }

    //数据解析
    if(revByteArray.at(0) == 0x68 && revByteArray.at(1) == 0x04 && revByteArray.length() <=106)
    {
        revFrameCmd.Header =  revByteArray.at(0);
        revFrameCmd.Id     =  revByteArray.at(1);
        revFrameCmd.Cid    =  revByteArray.at(2);
        revFrameCmd.Len    =  revByteArray.at(3);

        for(qint8 i=0; i<revFrameCmd.Len; i++)
        {
            revFrameCmd.Data[i] = revByteArray.at(4 + i);
        }

        revFrameCmd.Chk    =  revByteArray.at(revByteArray.length() - 2);
        revFrameCmd.Tail   =  revByteArray.at(revByteArray.length() - 1);

        if(revFrameCmd.Cid == 0x01)
        {
            QString str;

            str += QString("%1").arg((revFrameCmd.Data[0] >> 4) & 0x07);
            str += ".";
            str += QString("%1").arg((revFrameCmd.Data[0]) & 0x0F);
            str += QString("%1").arg((revFrameCmd.Data[1] >> 4) & 0x0F);

            if((revFrameCmd.Data[0] >> 7) == 0x01)
            {
                str.prepend("正式版:V");
            }
            else
            {
                str.prepend("测试版:V");
                str += QString("%1").arg((revFrameCmd.Data[1]) & 0x0F);
            }

            ui->lineEditFwVersion->setText(str);
        }

        if(revFrameCmd.Cid == 0x02)
        {
            QString str;

            for(int i=0; i<revFrameCmd.Len; i++)
            {
                str += QString(revFrameCmd.Data[i]);

                if(i==10)
                {
                    str += " ";
                }
            }

            ui->lineEditCompInfo->setText(str);
        }

        if(revFrameCmd.Cid == 0x09)
        {
            QString str;

            str += "Ac Insert:" + QString("%1").arg(revFrameCmd.Data[0]) + " ";

            str += "Bat1 Insert:" + QString("%1").arg(revFrameCmd.Data[1]) + " ";
            str += "Bat1 Power:" + QString("%1").arg(revFrameCmd.Data[2]) + " ";
            str += "Bat1 State:" + QString("%1").arg(revFrameCmd.Data[3]) + " ";
            str += "Bat2 Insert:" + QString("%1").arg(revFrameCmd.Data[4]) + " ";
            str += "Bat2 Power:" + QString("%1").arg(revFrameCmd.Data[5]) + " ";
            str += "Bat2 State:" + QString("%1").arg(revFrameCmd.Data[6]) + " ";

            ui->lineEditPowerInfo->setText(str);
        }

        if(revFrameCmd.Cid == 0x0A)
        {
            QString str;

            str += "Fan1:" + QString("%1").arg((revFrameCmd.Data[0] << 8) + revFrameCmd.Data[1]) + " ";
            str += "Fan2:" + QString("%1").arg((revFrameCmd.Data[2] << 8) + revFrameCmd.Data[3]) + " ";
            str += "Fan3:" + QString("%1").arg((revFrameCmd.Data[4] << 8) + revFrameCmd.Data[5]) + " ";
            str += "Fan4:" + QString("%1").arg((revFrameCmd.Data[6] << 8) + revFrameCmd.Data[7]) + " ";
            str += "Fan5:" + QString("%1").arg((revFrameCmd.Data[8] << 8) + revFrameCmd.Data[9]) + " ";

            ui->lineEditFanInfo->setText(str);
        }

        if(revFrameCmd.Cid == 0x0B)
        {
            QString str;

            str = "Bat1 Temp: " + QString("%1").arg(revFrameCmd.Data[0]&0x7F) + " Bat2 Temp: " + QString("%1").arg(revFrameCmd.Data[1]&0x7F);

            ui->lineEditTempInfo->setText(str);
        }

        if(revFrameCmd.Cid == 0x0E)
        {
            vPP1 = (revFrameCmd.Data[0] << 8 | revFrameCmd.Data[1]) / 100.0;
            vNN1 = (revFrameCmd.Data[2] << 8 | revFrameCmd.Data[3]) / 100.0;
            vPP2 = (revFrameCmd.Data[4] << 8 | revFrameCmd.Data[5]) / 100.0;
            vNN2 = (revFrameCmd.Data[6] << 8 | revFrameCmd.Data[7]) / 100.0;

            ui->spinBoxGetVpp1->setValue(vPP1);
            ui->spinBoxGetVnn1->setValue(vNN1);
            ui->spinBoxGetVpp2->setValue(vPP2);
            ui->spinBoxGetVnn2->setValue(vNN2);
        }
    }
}

void Widget::on_btnClearRev_clicked()
{
    ui->textEditRev->clear();
}

void Widget::on_btnClearSend_clicked()
{
    ui->textEditSend->clear();
}






void Widget::iniUiWavePlot()
{
    ui->wave->legend->setVisible(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->wave->xAxis->setTicker(timeTicker);
    ui->wave->yAxis->setRange(-80, 80);

    QPen pen;
    pen.setWidth(2);

    pen.setColor(Qt::red);
    ui->wave->addGraph();
    ui->wave->graph(0)->setPen(pen);
    ui->wave->graph(0)->setName("VPP1");

    pen.setColor(Qt::green);
    ui->wave->addGraph();
    ui->wave->graph(1)->setPen(pen);
    ui->wave->graph(1)->setName("VNN1");

    pen.setColor(Qt::blue);
    ui->wave->addGraph();
    ui->wave->graph(2)->setPen(pen);
    ui->wave->graph(2)->setName("VPP2");

    pen.setColor(Qt::yellow);
    ui->wave->addGraph();
    ui->wave->graph(3)->setPen(pen);
    ui->wave->graph(3)->setName("VNN2");
}

void Widget::on_btnWaveStart_clicked()
{
    serialPortThread->startWavePlot();

    //开启示波器
    timerPlot->start(0);
    mWavePlotState = true;
}

void Widget::on_btnWaveStop_clicked()
{
    serialPortThread->stopWavePlot();

    //关闭示波器
    timerPlot->stop();
    mWavePlotState = false;
}

void Widget::realTimeCruvePlot()
{
    static QTime timeStart = QTime::currentTime();

    double key = timeStart.msecsTo(QTime::currentTime()) / 1000.0;

    static double lastPointKey = 0;

    if(key - lastPointKey > 0.002)
    {
        lastPointKey = key;

        ui->wave->graph(0)->addData(key, +vPP1);
        ui->wave->graph(1)->addData(key, -vNN1);
        ui->wave->graph(2)->addData(key, +vPP2);
        ui->wave->graph(3)->addData(key, -vNN2);
    }

    ui->wave->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->wave->replot();
}

void Widget::on_btnGetVol_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x0E;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x13;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnSetHv_clicked()
{
    qint16 vpp1, vnn1, vpp2, vnn2;

    vpp1 = ui->spinBoxSetVpp1->value() * 100;
    vnn1 = ui->spinBoxSetVnn1->value() * 100;
    vpp2 = ui->spinBoxSetVpp2->value() * 100;
    vnn2 = ui->spinBoxSetVnn2->value() * 100;

    QByteArray sendbyteArray;

    sendbyteArray[0]  = 0x68;
    sendbyteArray[1]  = 0x04;
    sendbyteArray[2]  = 0x13;
    sendbyteArray[3]  = 0x08;
    sendbyteArray[4]  = vpp1 >> 8;
    sendbyteArray[5]  = vpp1;
    sendbyteArray[6]  = vnn1 >> 8;
    sendbyteArray[7]  = vnn1;
    sendbyteArray[8]  = vpp2 >> 8;
    sendbyteArray[9]  = vpp2;
    sendbyteArray[10] = vnn2 >> 8;
    sendbyteArray[11] = vnn2;

    uint8_t chkSum = 0;

    for(int i=0; i<11; i++)
    {
        chkSum += sendbyteArray[i+1];
    }

    sendbyteArray[12] = chkSum;
    sendbyteArray[13] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnSetCw_clicked()
{
    qint8 vpp1, vnn1, vpp2, vnn2;

    vpp1 = ui->spinBoxSetVpp1->value() * 100;
    vnn1 = ui->spinBoxSetVnn1->value() * 100;
    vpp2 = ui->spinBoxSetVpp2->value() * 100;
    vnn2 = ui->spinBoxSetVnn2->value() * 100;

    QByteArray sendbyteArray;

    sendbyteArray[0]  = 0x68;
    sendbyteArray[1]  = 0x04;
    sendbyteArray[2]  = 0x14;
    sendbyteArray[3]  = 0x08;
    sendbyteArray[4]  = vpp1 >> 8;
    sendbyteArray[5]  = vpp1;
    sendbyteArray[6]  = vnn1 >> 8;
    sendbyteArray[7]  = vnn1;
    sendbyteArray[8]  = vpp2 >> 8;
    sendbyteArray[9]  = vpp2;
    sendbyteArray[10] = vnn2 >> 8;
    sendbyteArray[11] = vnn2;

    uint8_t chkSum = 0;

    for(int i=0; i<11; i++)
    {
        chkSum += sendbyteArray[i+1];
    }

    sendbyteArray[12] = chkSum;
    sendbyteArray[13] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}


void Widget::on_btnCompileInfo_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x02;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x07;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnFwVersion_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x01;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x06;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnRdHwVersion_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x03;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x08;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnWrHwVersion_clicked()
{
    qint16 verH, verL;

    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x04;
    sendbyteArray[3] = 0x02;

    sendbyteArray[4] = verH;
    sendbyteArray[5] = verL;

    uint8_t chkSum = 0;

    for(int i=0; i<5; i++)
    {
        chkSum += sendbyteArray[i+1];
    }

    sendbyteArray[12] = chkSum;
    sendbyteArray[13] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnTempInfo_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x0B;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x10;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnPowerInfo_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x09;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x0E;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnFanInfo_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x0A;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x0F;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnSleep_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x05;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x0C;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnWeakup_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x06;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x0B;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnRestart_clicked()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x07;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x0C;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);
}

void Widget::on_btnUpgrade_clicked()
{

    widgetDown->setAttribute(Qt::WA_ShowModal, true);
    widgetDown->show();
}

void Widget::on_btnCalibration_clicked()
{

}



void Widget::startXmodemSlot(QByteArray byteArray)
{
    xmodemFlag = true;

    byteArrayFile = byteArray;

    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x08;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x0D;
    sendbyteArray[6] = 0x16;

    serialPortThread->writeSerialPort(sendbyteArray);

    ui->textEditRev->appendPlainText("->");

    ui->textEditRev->insertPlainText(sendbyteArray.toHex(' ').data());
}

qint8 Widget::xmodemRevDataAnalysis(QByteArray byteArray)
{
    ui->textEditRev->appendPlainText("<-");
    ui->textEditRev->insertPlainText(byteArray.toHex(' ').data());

    if(byteArray.size() == 1 && byteArray.at(0) == 'C')
    {
        return beginTransimt;
    }
    if(byteArray.size() == 1 && byteArray.at(0) == ACK)
    {
        return runTransimt;
    }
    if(byteArray.size() == 1 && byteArray.at(0) == NAK)
    {
        return repeatTransimt;
    }
    if(byteArray.size() == 1 && byteArray.at(0) == CAN)
    {
        return stopTransimt;
    }
    if(byteArray.at(0) == 0x68 && byteArray.at(1) == 0x11 && byteArray.at(2) == 0x04 &&
       byteArray.at(3) == 0x01 && byteArray.at(5) == 0x16)
    {
        if(byteArray.at(4) == (char)0xC4)
        {
            return finishTransimt;
        }
    }

    return errTransimt;
}

qint16 Widget::xmodemCalcrc(const qint8 *ptr, qint16 count)
{
    qint8 i;
    qint16 crc = 0;

    while(--count >= 0)
    {
        crc = crc ^ (qint8) *ptr++ << 8;

        i = 8;

        do
        {
            if(crc & 0x8000)
            {
                crc = crc << 1 ^ 0x1021;
            }
            else
            {
                crc = crc << 1;
            }

        } while(--i);
    }

    return(crc);
}





