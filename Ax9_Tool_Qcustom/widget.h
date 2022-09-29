#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "serialportthread.h"
#include "widgetdown.h"

#define beginTransimt    1
#define runTransimt      2
#define repeatTransimt   3
#define stopTransimt     4
#define finishTransimt   5
#define errTransimt      6

#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15
#define CAN 0x18

typedef struct {

    uint8_t Header;
    uint8_t Id;
    uint8_t Cid;
    uint8_t Len;
    uint8_t Data[100];
    uint8_t Chk;
    uint8_t Tail;
}CmdFrameStr;

typedef struct {

    qint8 Head;
    qint8 packNum;
    qint8 numPack;
    qint8 data[128];
    qint8 chkHigh;
    qint8 chkLow;
}Xmodem;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    Ui::Widget *ui;

private slots:
    void startXmodemSlot(QByteArray);

    void realTimeCruvePlot(void);

    void serialPortDataSlot(QByteArray);

    void on_btnScan_clicked();

    void on_btnOpen_clicked();

    void on_btnClos_clicked();

    void on_btnSend_clicked();

    void on_btnClearRev_clicked();

    void on_btnClearSend_clicked();

    void on_btnWaveStart_clicked();

    void on_btnWaveStop_clicked();

    void on_btnGetVol_clicked();

    void on_btnSetHv_clicked();

    void on_btnSetCw_clicked();

    void on_btnCompileInfo_clicked();

    void on_btnFwVersion_clicked();

    void on_btnRdHwVersion_clicked();

    void on_btnWrHwVersion_clicked();

    void on_btnTempInfo_clicked();

    void on_btnPowerInfo_clicked();

    void on_btnFanInfo_clicked();

    void on_btnSleep_clicked();

    void on_btnWeakup_clicked();

    void on_btnRestart_clicked();

    void on_btnUpgrade_clicked();

    void on_btnCalibration_clicked();

private:
    SerialPortThread *serialPortThread;

    void initUiserialPort();
    void iniUiWavePlot();

    QTimer *timerPlot;

    bool mWavePlotState = false;

    double vPP1 = 0.0;
    double vNN1 = 0.0;
    double vPP2 = 0.0;
    double vNN2 = 0.0;

    CmdFrameStr revFrameCmd;


    WidgetDown *widgetDown;
    QByteArray byteArrayFile;

    Xmodem xmod;
    bool xmodemFlag = false;

    qint8 xmodemRevDataAnalysis(QByteArray byteArray);
    qint16 xmodemCalcrc(const qint8 *ptr, qint16 count);

    int *dat1;



};

#endif // WIDGET_H













