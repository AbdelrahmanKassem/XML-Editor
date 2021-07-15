#include "fixdialog.h"
#include "ui_fixdialog.h"

FixDialog::FixDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FixDialog)
{
    ui->setupUi(this);
    QFile x("ERROR.xml");
    if(!x.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
    }
    QTextStream inx(&x);
    QString textx = inx.readAll();
    ui->plainTextEdit->setPlainText(textx);
    x.close();
}

FixDialog::~FixDialog()
{
    delete ui;
}
int fixFlag = 0;
void FixDialog::on_pushButton_2_clicked()
{
    QDialog::close();
}


void FixDialog::on_pushButton_clicked()
{
    fixFlag = 1;
    QDialog::close();
}

