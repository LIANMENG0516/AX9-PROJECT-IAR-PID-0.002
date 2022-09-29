/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *groupBox_7;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QPlainTextEdit *textEditSend;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_6;
    QPushButton *btnSend;
    QPushButton *btnClearRev;
    QPushButton *btnClearSend;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPlainTextEdit *textEditRev;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QRadioButton *radioSendHex;
    QRadioButton *radioSendAssic;
    QCheckBox *chkSendRepeat;
    QSpinBox *spinRepatTime;
    QCheckBox *chkNewLine;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QGridLayout *gridLayout;
    QComboBox *boxDatBits;
    QComboBox *boxPortNum;
    QComboBox *boxBadRate;
    QComboBox *boxStpBits;
    QComboBox *boxPartity;
    QComboBox *boxFlwCtrl;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpen;
    QPushButton *btnClos;
    QPushButton *btnScan;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QRadioButton *radioRevHex;
    QRadioButton *radioRevAssic;
    QCheckBox *chkRevDisplayTime;
    QGroupBox *groupBox_9;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_14;
    QPushButton *btnWaveCapture;
    QPushButton *btnWaveStop;
    QPushButton *btnWaveStart;
    QGroupBox *groupBox_8;
    QCustomPlot *wave;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QDoubleSpinBox *spinBoxGetVpp1;
    QLabel *label_9;
    QDoubleSpinBox *spinBoxGetVnn1;
    QLabel *label_10;
    QDoubleSpinBox *spinBoxGetVpp2;
    QLabel *label_13;
    QDoubleSpinBox *spinBoxGetVnn2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_14;
    QDoubleSpinBox *spinBoxSetVpp1;
    QLabel *label_15;
    QDoubleSpinBox *spinBoxSetVnn1;
    QLabel *label_16;
    QDoubleSpinBox *spinBoxSetVpp2;
    QLabel *label_17;
    QDoubleSpinBox *spinBoxSetVnn2;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btnGetVol;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnSetHv;
    QPushButton *btnSetCw;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_10;
    QPushButton *btnFwVersion;
    QPushButton *btnWrHwVersion;
    QPushButton *btnFanInfo;
    QPushButton *btnRdHwVersion;
    QPushButton *btnPowerInfo;
    QPushButton *btnTempInfo;
    QPushButton *btnCompileInfo;
    QGridLayout *gridLayout_11;
    QLineEdit *lineEditWrHwVersion;
    QLineEdit *lineEditCompInfo;
    QLineEdit *lineEditRdHwVersion;
    QLineEdit *lineEditFwVersion;
    QLineEdit *lineEditPowerInfo;
    QLineEdit *lineEditTempInfo;
    QLineEdit *lineEditFanInfo;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_12;
    QPushButton *btnSleep;
    QPushButton *btnUpgrade;
    QPushButton *btnRestart;
    QPushButton *btnWeakup;
    QPushButton *btnCalibration;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1472, 829);
        groupBox_7 = new QGroupBox(Widget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 10, 661, 811));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox_7->setFont(font);
        groupBox_5 = new QGroupBox(groupBox_7);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(240, 590, 411, 151));
        groupBox_5->setMaximumSize(QSize(16777215, 200));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        groupBox_5->setFont(font1);
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        textEditSend = new QPlainTextEdit(groupBox_5);
        textEditSend->setObjectName(QStringLiteral("textEditSend"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        textEditSend->setFont(font2);

        gridLayout_5->addWidget(textEditSend, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_7);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(240, 750, 411, 51));
        QFont font3;
        font3.setPointSize(9);
        groupBox_6->setFont(font3);
        gridLayout_6 = new QGridLayout(groupBox_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        btnSend = new QPushButton(groupBox_6);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setFont(font2);

        gridLayout_6->addWidget(btnSend, 0, 0, 1, 1);

        btnClearRev = new QPushButton(groupBox_6);
        btnClearRev->setObjectName(QStringLiteral("btnClearRev"));
        btnClearRev->setFont(font2);

        gridLayout_6->addWidget(btnClearRev, 0, 1, 1, 1);

        btnClearSend = new QPushButton(groupBox_6);
        btnClearSend->setObjectName(QStringLiteral("btnClearSend"));
        btnClearSend->setFont(font2);

        gridLayout_6->addWidget(btnClearSend, 0, 2, 1, 1);

        groupBox_4 = new QGroupBox(groupBox_7);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(240, 20, 411, 561));
        groupBox_4->setFont(font1);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        textEditRev = new QPlainTextEdit(groupBox_4);
        textEditRev->setObjectName(QStringLiteral("textEditRev"));
        textEditRev->setFont(font2);
        textEditRev->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditRev->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        textEditRev->setLineWrapMode(QPlainTextEdit::NoWrap);
        textEditRev->setOverwriteMode(false);
        textEditRev->setBackgroundVisible(false);
        textEditRev->setCenterOnScroll(false);

        gridLayout_4->addWidget(textEditRev, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_7);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 410, 221, 114));
        groupBox_3->setMaximumSize(QSize(16777215, 259));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setWeight(50);
        groupBox_3->setFont(font4);
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        radioSendHex = new QRadioButton(groupBox_3);
        radioSendHex->setObjectName(QStringLiteral("radioSendHex"));
        radioSendHex->setFont(font1);

        gridLayout_7->addWidget(radioSendHex, 0, 0, 1, 1);

        radioSendAssic = new QRadioButton(groupBox_3);
        radioSendAssic->setObjectName(QStringLiteral("radioSendAssic"));
        radioSendAssic->setFont(font1);
        radioSendAssic->setChecked(true);

        gridLayout_7->addWidget(radioSendAssic, 0, 1, 1, 1);

        chkSendRepeat = new QCheckBox(groupBox_3);
        chkSendRepeat->setObjectName(QStringLiteral("chkSendRepeat"));
        chkSendRepeat->setFont(font1);

        gridLayout_7->addWidget(chkSendRepeat, 1, 0, 1, 1);

        spinRepatTime = new QSpinBox(groupBox_3);
        spinRepatTime->setObjectName(QStringLiteral("spinRepatTime"));
        spinRepatTime->setFont(font1);
        spinRepatTime->setMaximum(10000);
        spinRepatTime->setValue(1);

        gridLayout_7->addWidget(spinRepatTime, 1, 1, 1, 1);

        chkNewLine = new QCheckBox(groupBox_3);
        chkNewLine->setObjectName(QStringLiteral("chkNewLine"));
        chkNewLine->setFont(font1);

        gridLayout_7->addWidget(chkNewLine, 2, 0, 1, 1);

        groupBox = new QGroupBox(groupBox_7);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 221, 280));
        groupBox->setMaximumSize(QSize(16777215, 280));
        groupBox->setFont(font1);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);


        horizontalLayout_5->addLayout(verticalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        boxDatBits = new QComboBox(groupBox);
        boxDatBits->setObjectName(QStringLiteral("boxDatBits"));
        boxDatBits->setFont(font2);

        gridLayout->addWidget(boxDatBits, 2, 0, 1, 1);

        boxPortNum = new QComboBox(groupBox);
        boxPortNum->setObjectName(QStringLiteral("boxPortNum"));
        boxPortNum->setFont(font2);

        gridLayout->addWidget(boxPortNum, 0, 0, 1, 1);

        boxBadRate = new QComboBox(groupBox);
        boxBadRate->setObjectName(QStringLiteral("boxBadRate"));
        boxBadRate->setFont(font2);

        gridLayout->addWidget(boxBadRate, 1, 0, 1, 1);

        boxStpBits = new QComboBox(groupBox);
        boxStpBits->setObjectName(QStringLiteral("boxStpBits"));
        boxStpBits->setFont(font2);

        gridLayout->addWidget(boxStpBits, 3, 0, 1, 1);

        boxPartity = new QComboBox(groupBox);
        boxPartity->setObjectName(QStringLiteral("boxPartity"));
        boxPartity->setFont(font2);

        gridLayout->addWidget(boxPartity, 4, 0, 1, 1);

        boxFlwCtrl = new QComboBox(groupBox);
        boxFlwCtrl->setObjectName(QStringLiteral("boxFlwCtrl"));
        boxFlwCtrl->setFont(font2);

        gridLayout->addWidget(boxFlwCtrl, 5, 0, 1, 1);


        horizontalLayout_5->addLayout(gridLayout);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnOpen = new QPushButton(groupBox);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setEnabled(true);
        btnOpen->setFont(font2);

        horizontalLayout->addWidget(btnOpen);

        btnClos = new QPushButton(groupBox);
        btnClos->setObjectName(QStringLiteral("btnClos"));
        btnClos->setEnabled(true);
        btnClos->setFont(font2);

        horizontalLayout->addWidget(btnClos);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        btnScan = new QPushButton(groupBox);
        btnScan->setObjectName(QStringLiteral("btnScan"));
        btnScan->setFont(font2);

        gridLayout_2->addWidget(btnScan, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_7);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 310, 221, 91));
        groupBox_2->setFont(font1);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        radioRevHex = new QRadioButton(groupBox_2);
        radioRevHex->setObjectName(QStringLiteral("radioRevHex"));
        radioRevHex->setFont(font2);

        gridLayout_3->addWidget(radioRevHex, 0, 0, 1, 1);

        radioRevAssic = new QRadioButton(groupBox_2);
        radioRevAssic->setObjectName(QStringLiteral("radioRevAssic"));
        radioRevAssic->setFont(font2);
        radioRevAssic->setChecked(true);

        gridLayout_3->addWidget(radioRevAssic, 0, 1, 1, 1);

        chkRevDisplayTime = new QCheckBox(groupBox_2);
        chkRevDisplayTime->setObjectName(QStringLiteral("chkRevDisplayTime"));
        chkRevDisplayTime->setFont(font2);

        gridLayout_3->addWidget(chkRevDisplayTime, 1, 0, 1, 2);

        groupBox_9 = new QGroupBox(Widget);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(680, 10, 781, 481));
        groupBox_9->setFont(font);
        groupBox_13 = new QGroupBox(groupBox_9);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(10, 420, 761, 52));
        groupBox_13->setFont(font3);
        gridLayout_14 = new QGridLayout(groupBox_13);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        btnWaveCapture = new QPushButton(groupBox_13);
        btnWaveCapture->setObjectName(QStringLiteral("btnWaveCapture"));
        btnWaveCapture->setFont(font2);

        gridLayout_14->addWidget(btnWaveCapture, 0, 2, 1, 1);

        btnWaveStop = new QPushButton(groupBox_13);
        btnWaveStop->setObjectName(QStringLiteral("btnWaveStop"));
        btnWaveStop->setFont(font2);

        gridLayout_14->addWidget(btnWaveStop, 0, 1, 1, 1);

        btnWaveStart = new QPushButton(groupBox_13);
        btnWaveStart->setObjectName(QStringLiteral("btnWaveStart"));
        btnWaveStart->setFont(font2);

        gridLayout_14->addWidget(btnWaveStart, 0, 0, 1, 1);

        groupBox_8 = new QGroupBox(groupBox_9);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 27, 761, 381));
        groupBox_8->setFont(font2);
        wave = new QCustomPlot(groupBox_8);
        wave->setObjectName(QStringLiteral("wave"));
        wave->setGeometry(QRect(10, 20, 741, 351));
        groupBox_12 = new QGroupBox(Widget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(680, 500, 781, 91));
        groupBox_12->setMaximumSize(QSize(16777215, 259));
        groupBox_12->setFont(font2);
        gridLayout_9 = new QGridLayout(groupBox_12);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(groupBox_12);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font2);

        horizontalLayout_3->addWidget(label_7);

        spinBoxGetVpp1 = new QDoubleSpinBox(groupBox_12);
        spinBoxGetVpp1->setObjectName(QStringLiteral("spinBoxGetVpp1"));
        spinBoxGetVpp1->setMinimumSize(QSize(84, 0));

        horizontalLayout_3->addWidget(spinBoxGetVpp1);

        label_9 = new QLabel(groupBox_12);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font2);

        horizontalLayout_3->addWidget(label_9);

        spinBoxGetVnn1 = new QDoubleSpinBox(groupBox_12);
        spinBoxGetVnn1->setObjectName(QStringLiteral("spinBoxGetVnn1"));
        spinBoxGetVnn1->setMinimumSize(QSize(84, 0));

        horizontalLayout_3->addWidget(spinBoxGetVnn1);

        label_10 = new QLabel(groupBox_12);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font2);

        horizontalLayout_3->addWidget(label_10);

        spinBoxGetVpp2 = new QDoubleSpinBox(groupBox_12);
        spinBoxGetVpp2->setObjectName(QStringLiteral("spinBoxGetVpp2"));
        spinBoxGetVpp2->setMinimumSize(QSize(84, 0));

        horizontalLayout_3->addWidget(spinBoxGetVpp2);

        label_13 = new QLabel(groupBox_12);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font2);

        horizontalLayout_3->addWidget(label_13);

        spinBoxGetVnn2 = new QDoubleSpinBox(groupBox_12);
        spinBoxGetVnn2->setObjectName(QStringLiteral("spinBoxGetVnn2"));
        spinBoxGetVnn2->setMinimumSize(QSize(84, 0));

        horizontalLayout_3->addWidget(spinBoxGetVnn2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_14 = new QLabel(groupBox_12);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font2);

        horizontalLayout_4->addWidget(label_14);

        spinBoxSetVpp1 = new QDoubleSpinBox(groupBox_12);
        spinBoxSetVpp1->setObjectName(QStringLiteral("spinBoxSetVpp1"));
        spinBoxSetVpp1->setMinimumSize(QSize(84, 0));

        horizontalLayout_4->addWidget(spinBoxSetVpp1);

        label_15 = new QLabel(groupBox_12);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font2);

        horizontalLayout_4->addWidget(label_15);

        spinBoxSetVnn1 = new QDoubleSpinBox(groupBox_12);
        spinBoxSetVnn1->setObjectName(QStringLiteral("spinBoxSetVnn1"));
        spinBoxSetVnn1->setMinimumSize(QSize(84, 0));

        horizontalLayout_4->addWidget(spinBoxSetVnn1);

        label_16 = new QLabel(groupBox_12);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setFont(font2);

        horizontalLayout_4->addWidget(label_16);

        spinBoxSetVpp2 = new QDoubleSpinBox(groupBox_12);
        spinBoxSetVpp2->setObjectName(QStringLiteral("spinBoxSetVpp2"));
        spinBoxSetVpp2->setMinimumSize(QSize(84, 0));

        horizontalLayout_4->addWidget(spinBoxSetVpp2);

        label_17 = new QLabel(groupBox_12);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setFont(font2);

        horizontalLayout_4->addWidget(label_17);

        spinBoxSetVnn2 = new QDoubleSpinBox(groupBox_12);
        spinBoxSetVnn2->setObjectName(QStringLiteral("spinBoxSetVnn2"));
        spinBoxSetVnn2->setMinimumSize(QSize(84, 0));

        horizontalLayout_4->addWidget(spinBoxSetVnn2);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout_9->addLayout(verticalLayout_4, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        btnGetVol = new QPushButton(groupBox_12);
        btnGetVol->setObjectName(QStringLiteral("btnGetVol"));
        btnGetVol->setFont(font2);

        verticalLayout_6->addWidget(btnGetVol);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btnSetHv = new QPushButton(groupBox_12);
        btnSetHv->setObjectName(QStringLiteral("btnSetHv"));
        btnSetHv->setFont(font2);

        horizontalLayout_6->addWidget(btnSetHv);

        btnSetCw = new QPushButton(groupBox_12);
        btnSetCw->setObjectName(QStringLiteral("btnSetCw"));
        btnSetCw->setFont(font2);

        horizontalLayout_6->addWidget(btnSetCw);


        verticalLayout_6->addLayout(horizontalLayout_6);


        gridLayout_9->addLayout(verticalLayout_6, 0, 1, 1, 1);

        groupBox_11 = new QGroupBox(Widget);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(680, 600, 651, 221));
        groupBox_11->setMaximumSize(QSize(16777215, 259));
        groupBox_11->setFont(font2);
        gridLayout_8 = new QGridLayout(groupBox_11);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        btnFwVersion = new QPushButton(groupBox_11);
        btnFwVersion->setObjectName(QStringLiteral("btnFwVersion"));
        btnFwVersion->setFont(font2);

        gridLayout_10->addWidget(btnFwVersion, 1, 0, 1, 1);

        btnWrHwVersion = new QPushButton(groupBox_11);
        btnWrHwVersion->setObjectName(QStringLiteral("btnWrHwVersion"));
        btnWrHwVersion->setFont(font2);

        gridLayout_10->addWidget(btnWrHwVersion, 3, 0, 1, 1);

        btnFanInfo = new QPushButton(groupBox_11);
        btnFanInfo->setObjectName(QStringLiteral("btnFanInfo"));
        btnFanInfo->setFont(font2);

        gridLayout_10->addWidget(btnFanInfo, 6, 0, 1, 1);

        btnRdHwVersion = new QPushButton(groupBox_11);
        btnRdHwVersion->setObjectName(QStringLiteral("btnRdHwVersion"));
        btnRdHwVersion->setFont(font2);

        gridLayout_10->addWidget(btnRdHwVersion, 2, 0, 1, 1);

        btnPowerInfo = new QPushButton(groupBox_11);
        btnPowerInfo->setObjectName(QStringLiteral("btnPowerInfo"));
        btnPowerInfo->setFont(font2);

        gridLayout_10->addWidget(btnPowerInfo, 5, 0, 1, 1);

        btnTempInfo = new QPushButton(groupBox_11);
        btnTempInfo->setObjectName(QStringLiteral("btnTempInfo"));
        btnTempInfo->setFont(font2);

        gridLayout_10->addWidget(btnTempInfo, 4, 0, 1, 1);

        btnCompileInfo = new QPushButton(groupBox_11);
        btnCompileInfo->setObjectName(QStringLiteral("btnCompileInfo"));
        btnCompileInfo->setFont(font2);

        gridLayout_10->addWidget(btnCompileInfo, 0, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_10, 0, 0, 1, 1);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        lineEditWrHwVersion = new QLineEdit(groupBox_11);
        lineEditWrHwVersion->setObjectName(QStringLiteral("lineEditWrHwVersion"));
        lineEditWrHwVersion->setFont(font2);

        gridLayout_11->addWidget(lineEditWrHwVersion, 3, 0, 1, 1);

        lineEditCompInfo = new QLineEdit(groupBox_11);
        lineEditCompInfo->setObjectName(QStringLiteral("lineEditCompInfo"));
        lineEditCompInfo->setFont(font2);

        gridLayout_11->addWidget(lineEditCompInfo, 0, 0, 1, 1);

        lineEditRdHwVersion = new QLineEdit(groupBox_11);
        lineEditRdHwVersion->setObjectName(QStringLiteral("lineEditRdHwVersion"));
        lineEditRdHwVersion->setFont(font2);

        gridLayout_11->addWidget(lineEditRdHwVersion, 2, 0, 1, 1);

        lineEditFwVersion = new QLineEdit(groupBox_11);
        lineEditFwVersion->setObjectName(QStringLiteral("lineEditFwVersion"));
        lineEditFwVersion->setFont(font2);

        gridLayout_11->addWidget(lineEditFwVersion, 1, 0, 1, 1);

        lineEditPowerInfo = new QLineEdit(groupBox_11);
        lineEditPowerInfo->setObjectName(QStringLiteral("lineEditPowerInfo"));
        lineEditPowerInfo->setFont(font2);

        gridLayout_11->addWidget(lineEditPowerInfo, 5, 0, 1, 1);

        lineEditTempInfo = new QLineEdit(groupBox_11);
        lineEditTempInfo->setObjectName(QStringLiteral("lineEditTempInfo"));
        lineEditTempInfo->setFont(font2);

        gridLayout_11->addWidget(lineEditTempInfo, 4, 0, 1, 1);

        lineEditFanInfo = new QLineEdit(groupBox_11);
        lineEditFanInfo->setObjectName(QStringLiteral("lineEditFanInfo"));
        lineEditFanInfo->setFont(font2);
        lineEditFanInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_11->addWidget(lineEditFanInfo, 6, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_11, 0, 1, 1, 1);

        groupBox_10 = new QGroupBox(Widget);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(1340, 600, 121, 221));
        gridLayout_12 = new QGridLayout(groupBox_10);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        btnSleep = new QPushButton(groupBox_10);
        btnSleep->setObjectName(QStringLiteral("btnSleep"));
        btnSleep->setFont(font2);

        gridLayout_12->addWidget(btnSleep, 0, 0, 1, 1);

        btnUpgrade = new QPushButton(groupBox_10);
        btnUpgrade->setObjectName(QStringLiteral("btnUpgrade"));
        btnUpgrade->setFont(font2);

        gridLayout_12->addWidget(btnUpgrade, 1, 0, 1, 1);

        btnRestart = new QPushButton(groupBox_10);
        btnRestart->setObjectName(QStringLiteral("btnRestart"));
        btnRestart->setFont(font2);

        gridLayout_12->addWidget(btnRestart, 2, 0, 1, 1);

        btnWeakup = new QPushButton(groupBox_10);
        btnWeakup->setObjectName(QStringLiteral("btnWeakup"));
        btnWeakup->setFont(font2);

        gridLayout_12->addWidget(btnWeakup, 3, 0, 1, 1);

        btnCalibration = new QPushButton(groupBox_10);
        btnCalibration->setObjectName(QStringLiteral("btnCalibration"));

        gridLayout_12->addWidget(btnCalibration, 4, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("Widget", "Basic Debug Area", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("Widget", "Send", Q_NULLPTR));
        groupBox_6->setTitle(QString());
        btnSend->setText(QApplication::translate("Widget", "Send", Q_NULLPTR));
        btnClearRev->setText(QApplication::translate("Widget", "Receive Area Clear", Q_NULLPTR));
        btnClearSend->setText(QApplication::translate("Widget", "Send Area Clear", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Widget", "Receive", Q_NULLPTR));
        textEditRev->setPlaceholderText(QString());
        groupBox_3->setTitle(QApplication::translate("Widget", "Send Config", Q_NULLPTR));
        radioSendHex->setText(QApplication::translate("Widget", "Hex", Q_NULLPTR));
        radioSendAssic->setText(QApplication::translate("Widget", "Assic", Q_NULLPTR));
        chkSendRepeat->setText(QApplication::translate("Widget", "Rep Send", Q_NULLPTR));
        spinRepatTime->setSuffix(QApplication::translate("Widget", "Ms", Q_NULLPTR));
        chkNewLine->setText(QApplication::translate("Widget", "New Line", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Widget", "Port Config", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "Serial Port", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "Baund Rate", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "Data Bit", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "Stop Bit", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "Parity", Q_NULLPTR));
        label_6->setText(QApplication::translate("Widget", "Flow Ctrl", Q_NULLPTR));
        btnOpen->setText(QApplication::translate("Widget", "Open", Q_NULLPTR));
        btnClos->setText(QApplication::translate("Widget", "Close", Q_NULLPTR));
        btnScan->setText(QApplication::translate("Widget", "Scan", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Widget", "Receive Config", Q_NULLPTR));
        radioRevHex->setText(QApplication::translate("Widget", "Hex", Q_NULLPTR));
        radioRevAssic->setText(QApplication::translate("Widget", "Assic", Q_NULLPTR));
        chkRevDisplayTime->setText(QApplication::translate("Widget", "Display Time", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("Widget", "Wave Area", Q_NULLPTR));
        groupBox_13->setTitle(QString());
        btnWaveCapture->setText(QApplication::translate("Widget", "Wave Capture", Q_NULLPTR));
        btnWaveStop->setText(QApplication::translate("Widget", "Wave Stop", Q_NULLPTR));
        btnWaveStart->setText(QApplication::translate("Widget", "Wave Start", Q_NULLPTR));
        groupBox_8->setTitle(QString());
        groupBox_12->setTitle(QApplication::translate("Widget", "Adjust Voltage", Q_NULLPTR));
        label_7->setText(QApplication::translate("Widget", "VPP1", Q_NULLPTR));
        label_9->setText(QApplication::translate("Widget", "VNN1", Q_NULLPTR));
        label_10->setText(QApplication::translate("Widget", "VPP2", Q_NULLPTR));
        label_13->setText(QApplication::translate("Widget", "VNN2", Q_NULLPTR));
        label_14->setText(QApplication::translate("Widget", "VPP1", Q_NULLPTR));
        label_15->setText(QApplication::translate("Widget", "VNN1", Q_NULLPTR));
        label_16->setText(QApplication::translate("Widget", "VPP2", Q_NULLPTR));
        label_17->setText(QApplication::translate("Widget", "VNN2", Q_NULLPTR));
        btnGetVol->setText(QApplication::translate("Widget", "GET VOL", Q_NULLPTR));
        btnSetHv->setText(QApplication::translate("Widget", "SET HV", Q_NULLPTR));
        btnSetCw->setText(QApplication::translate("Widget", "SET CW", Q_NULLPTR));
        groupBox_11->setTitle(QApplication::translate("Widget", "Information", Q_NULLPTR));
        btnFwVersion->setText(QApplication::translate("Widget", "\345\233\272\344\273\266\347\211\210\346\234\254", Q_NULLPTR));
        btnWrHwVersion->setText(QApplication::translate("Widget", "\345\206\231\347\241\254\347\211\210\346\234\254", Q_NULLPTR));
        btnFanInfo->setText(QApplication::translate("Widget", "\351\243\216\346\211\207\344\277\241\346\201\257", Q_NULLPTR));
        btnRdHwVersion->setText(QApplication::translate("Widget", "\350\257\273\347\241\254\347\211\210\346\234\254", Q_NULLPTR));
        btnPowerInfo->setText(QApplication::translate("Widget", "\347\224\265\346\272\220\344\277\241\346\201\257", Q_NULLPTR));
        btnTempInfo->setText(QApplication::translate("Widget", "\346\270\251\345\272\246\344\277\241\346\201\257", Q_NULLPTR));
        btnCompileInfo->setText(QApplication::translate("Widget", "\347\274\226\350\257\221\346\227\266\351\227\264", Q_NULLPTR));
        lineEditFanInfo->setText(QString());
        groupBox_10->setTitle(QApplication::translate("Widget", "Commond", Q_NULLPTR));
        btnSleep->setText(QApplication::translate("Widget", "Sleep", Q_NULLPTR));
        btnUpgrade->setText(QApplication::translate("Widget", "Upgrade", Q_NULLPTR));
        btnRestart->setText(QApplication::translate("Widget", "Restart", Q_NULLPTR));
        btnWeakup->setText(QApplication::translate("Widget", "Weakup", Q_NULLPTR));
        btnCalibration->setText(QApplication::translate("Widget", "Calibration", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
