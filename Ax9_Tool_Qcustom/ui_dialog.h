/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnLogIn;
    QPushButton *btnCancel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(302, 422);
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 190, 142, 31));
        lineEdit->setMinimumSize(QSize(0, 31));
        lineEdit->setStyleSheet(QLatin1String("QLineEdit {  \n"
"\n"
"border-width: 1px;\n"
"border-style: Ridge; \n"
" \n"
"border-radius:3px;  \n"
"\n"
"} "));
        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(80, 280, 142, 31));
        lineEdit_2->setMinimumSize(QSize(0, 31));
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit {  \n"
"\n"
"border-width: 1px;\n"
"border-style: Ridge; \n"
" \n"
"border-radius:3px;  \n"
"\n"
"} "));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 150, 60, 22));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 240, 60, 22));
        label_2->setFont(font);
        btnLogIn = new QPushButton(Dialog);
        btnLogIn->setObjectName(QStringLiteral("btnLogIn"));
        btnLogIn->setGeometry(QRect(30, 350, 101, 31));
        btnLogIn->setFont(font);
        btnCancel = new QPushButton(Dialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(170, 350, 101, 31));
        btnCancel->setFont(font);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "\345\257\206    \347\240\201", Q_NULLPTR));
        btnLogIn->setText(QApplication::translate("Dialog", "\347\231\273\345\275\225", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
