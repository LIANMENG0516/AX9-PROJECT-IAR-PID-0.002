#include "serialportthread.h"

#include <QDebug>

SerialPortThread::SerialPortThread(QObject *parent) : QThread(parent)
{
    serialPort = new QSerialPort;
    serialPortInfo = new QSerialPortInfo;
    connect(serialPort, &QSerialPort::readyRead, this, &SerialPortThread::readSerialPortSlot);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &SerialPortThread::sendReadVolCmdSlot);

}


QStringList SerialPortThread::scanSerialPort()
{
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();

    QStringList strList;

    for(int i=0; i<serialPortInfo.count(); i++)
    {
        strList.append(serialPortInfo.at(i).portName());
    }

    return strList;
}

bool SerialPortThread::openSerialPort(QString portNum, QString baundRate, QString dataBits, QString stopBits, QString partity, QString flowCtrl)
{
    serialPort->setPortName(portNum);

    serialPort->setBaudRate(baundRate.toLong());

    if(dataBits == "6 bit")
    {
        serialPort->setDataBits(QSerialPort::Data6);
    }
    else if(dataBits == "7 bit")
    {
        serialPort->setDataBits(QSerialPort::Data7);
    }
    else if(dataBits == "8 bit")
    {
        serialPort->setDataBits(QSerialPort::Data8);
    }
    else
    {
        serialPort->setDataBits(QSerialPort::UnknownDataBits);
    }

    if(stopBits == "1 bit")
    {
        serialPort->setStopBits(QSerialPort::OneStop);
    }
    else if(stopBits == "1.5 bit")
    {
        serialPort->setStopBits(QSerialPort::OneAndHalfStop);
    }
    else if(stopBits == "2 bit")
    {
        serialPort->setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        serialPort->setStopBits(QSerialPort::UnknownStopBits);
    }

    if(partity == "None")
    {
        serialPort->setParity(QSerialPort::NoParity);
    }
    else if(partity == "Odd")
    {
        serialPort->setParity(QSerialPort::OddParity);
    }
    else
    {
        serialPort->setParity(QSerialPort::EvenParity);
    }

    if(flowCtrl == "None")
    {
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
    }
    else if(flowCtrl == "Software")
    {
        serialPort->setFlowControl(QSerialPort::SoftwareControl);
    }
    else
    {
        serialPort->setFlowControl(QSerialPort::HardwareControl);
    }

    if(!serialPort->open(QIODevice::ReadWrite))
    {
        return false;
    }

    return true;
}

void SerialPortThread::closeSerialPort()
{
    serialPort->close();
}

void SerialPortThread::writeSerialPort(QByteArray byteArry)
{
    serialPort->write(byteArry);
}

void SerialPortThread::writeSerialPortLen(const char *data, qint64 len)
{
    serialPort->write(data, len);
}

void SerialPortThread::readSerialPortSlot()
{
    QByteArray revByteArray;

    revByteArray = serialPort->readAll();

    emit serialPortData(revByteArray);
}

void SerialPortThread::sendReadVolCmdSlot()
{
    QByteArray sendbyteArray;

    sendbyteArray[0] = 0x68;
    sendbyteArray[1] = 0x04;
    sendbyteArray[2] = 0x0E;
    sendbyteArray[3] = 0x01;
    sendbyteArray[4] = 0x00;
    sendbyteArray[5] = 0x13;
    sendbyteArray[6] = 0x16;

    serialPort->write(sendbyteArray);
    serialPort->waitForBytesWritten();
}

void SerialPortThread::startWavePlot()
{
    timer->start(20);
}

void SerialPortThread::stopWavePlot()
{
    timer->stop();
}



















