#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

#include <QThread>

#include <QTimer>
#include <QMutex>

#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPortThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialPortThread(QObject *parent = nullptr);

signals:
    void serialPortData(QByteArray);

public slots:
    void readSerialPortSlot(void);
    void sendReadVolCmdSlot(void);

public:
    QStringList scanSerialPort(void);
    bool openSerialPort(QString portNum, QString baundRate, QString dataBits, QString stopBits, QString partity, QString flowCtrl);
    void closeSerialPort(void);
    void writeSerialPort(QByteArray byteArry);
    void writeSerialPortLen(const char *data, qint64 len);

    void startWavePlot(void);
    void stopWavePlot(void);


    void quitSerialPortThread(void);

private:
    QSerialPort *serialPort;
    QSerialPortInfo *serialPortInfo;

    QTimer *timer;

    quint8 mCid;







};

#endif // SERIALPORTTHREAD_H
