/********************************************************************************
** Form generated from reading UI file 'widgetdown.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETDOWN_H
#define UI_WIDGETDOWN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetDown
{
public:
    QGridLayout *gridLayout;
    QLabel *labUpgradeState;
    QLineEdit *lineFeilPath;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpenFile;
    QPushButton *btnStart;
    QPushButton *btnClose;

    void setupUi(QWidget *WidgetDown)
    {
        if (WidgetDown->objectName().isEmpty())
            WidgetDown->setObjectName(QStringLiteral("WidgetDown"));
        WidgetDown->resize(473, 190);
        WidgetDown->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(WidgetDown);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labUpgradeState = new QLabel(WidgetDown);
        labUpgradeState->setObjectName(QStringLiteral("labUpgradeState"));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        labUpgradeState->setFont(font);
        labUpgradeState->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labUpgradeState, 0, 0, 1, 1);

        lineFeilPath = new QLineEdit(WidgetDown);
        lineFeilPath->setObjectName(QStringLiteral("lineFeilPath"));
        lineFeilPath->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(lineFeilPath, 1, 0, 1, 1);

        progressBar = new QProgressBar(WidgetDown);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setKerning(true);
        progressBar->setFont(font1);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        gridLayout->addWidget(progressBar, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnOpenFile = new QPushButton(WidgetDown);
        btnOpenFile->setObjectName(QStringLiteral("btnOpenFile"));
        btnOpenFile->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnOpenFile);

        btnStart = new QPushButton(WidgetDown);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnStart);

        btnClose = new QPushButton(WidgetDown);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnClose);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(WidgetDown);

        QMetaObject::connectSlotsByName(WidgetDown);
    } // setupUi

    void retranslateUi(QWidget *WidgetDown)
    {
        WidgetDown->setWindowTitle(QApplication::translate("WidgetDown", "Form", Q_NULLPTR));
        labUpgradeState->setText(QApplication::translate("WidgetDown", "\345\207\206\345\244\207\344\270\213\350\275\275", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        progressBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        progressBar->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        progressBar->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        progressBar->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        progressBar->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        progressBar->setFormat(QApplication::translate("WidgetDown", "%p%", Q_NULLPTR));
        btnOpenFile->setText(QApplication::translate("WidgetDown", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        btnStart->setText(QApplication::translate("WidgetDown", "\345\274\200\345\247\213\344\270\213\350\275\275", Q_NULLPTR));
        btnClose->setText(QApplication::translate("WidgetDown", "\345\205\263\351\227\255\347\252\227\345\217\243", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WidgetDown: public Ui_WidgetDown {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETDOWN_H
