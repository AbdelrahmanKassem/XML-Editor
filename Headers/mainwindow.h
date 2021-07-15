#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QPrinter>
#include<QPrintDialog>
#include "XML_Parser.h"
#include "XML_Pretify.h"
#include "XML_Minify.h"
#include "XML_JSON.h"
#include "XML_Parser.h"
#include "main.h"
#include "fixdialog.h"
#include"XML_Compression.h"

extern string fileInAstring;
extern int key;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
  //  Ui::MainWindow * getP(void);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_pushButton_clicked();

    void on_actionSave_As_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFile;
};
#endif // MAINWINDOW_H
