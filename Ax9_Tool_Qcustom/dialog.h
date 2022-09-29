#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;


protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_btnLogIn_clicked();
    void on_btnCancel_clicked();
};

#endif // DIALOG_H
