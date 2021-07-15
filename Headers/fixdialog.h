#ifndef FIXDIALOG_H
#define FIXDIALOG_H

#include <QDialog>
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QMessageBox>

extern int fixFlag;

namespace Ui {
class FixDialog;
}

class FixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FixDialog(QWidget *parent = nullptr);
    ~FixDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::FixDialog *ui;
};

#endif // FIXDIALOG_H
