#include "mainwindow.h"
#include "ui_mainwindow.h"
string fileInAstring = "";
int key=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//Ui::MainWindow * MainWindow::getP(void){
//    return ui;
//}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->plainTextEdit->setPlainText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString filter = "All Files (*.*) ;; XML Files (*.xml)";
    QString filename = QFileDialog::getOpenFileName(this,"Open File","C://",filter);
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();

    ui->plainTextEdit->setPlainText(text);
    XML_Parser(text.toStdString(),XML_ReadFile, sizeOfXML);

    XML_original.resize(sizeOfXML*2);
    XML_FixedErrors.resize(sizeOfXML*2);
    Spaces.resize(sizeOfXML*2);
    JSON.resize(sizeOfXML*3);

    XML_FixErrors(NumOfLines, XML_original, XML_FixedErrors, XML_ReadFile , sizeOfXML);
    XML_indent(Spaces, XML_FixedErrors , NumOfLines );
    file.close();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}

/*Check For Errors button*/
void MainWindow::on_pushButton_clicked()
{
  //  cout << "-----------------------------      BEFORE FIX  WITH INDENTION     -----------------------------" << " \n \n ";
  //  Print_XML(Spaces, XML_original, NumOfLines);
    Output_File(Spaces, XML_original, NumOfLines,"Error");
    FixDialog fix;
    fix.setModal(true);
    fix.exec();
    if(fixFlag == 1)
    {
        Output_File(Spaces, XML_FixedErrors, NumOfLines,"Error");
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
//    currentFile.clear();
//    ui->plainTextEdit->setPlainText(QString());
//    QFile x("ERROR.xml");
//    if(!x.open(QIODevice::ReadOnly | QFile::Text))
//    {
//        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
//    }
//    QTextStream inx(&x);
//    QString textx = inx.readAll();
//    ui->plainTextEdit->setPlainText(textx);
//    x.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save As");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Save File : " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.close();
}

/*Format Button*/
void MainWindow::on_pushButton_2_clicked()
{
    if(fixFlag == 1)
    {
        Output_File(Spaces, XML_FixedErrors, NumOfLines,"Format");
        QFile x("Format.xml");
        if(!x.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
        }
        QTextStream inx(&x);
        QString textx = inx.readAll();
        ui->plainTextEdit->setPlainText(textx);
        x.close();
    }
    else
    {
        Output_File(Spaces, XML_ReadFile, NumOfLines,"Format");
        QFile x("Format.xml");
        if(!x.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
        }
        QTextStream inx(&x);
        QString textx = inx.readAll();
        ui->plainTextEdit->setPlainText(textx);
        x.close();
    }
}

/*MINIFY*/
void MainWindow::on_pushButton_4_clicked()
{
    if(fixFlag == 1)
    {
        XML_Minify(XML_FixedErrors,NumOfLines);
        QFile x("xml_minify.xml");
        if(!x.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
        }
        QTextStream inx(&x);
        QString textx = inx.readAll();
        ui->plainTextEdit->setPlainText(textx);
        x.close();
    }
}

/*JSON*/
void MainWindow::on_pushButton_5_clicked()
{
    xml_json(XML_FixedErrors, JSON , NumOfLines, sizeOfJSON );
    Output_File(JSON , sizeOfJSON);
    QFile x("TEXTOUTPUT.xml");
    if(!x.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
    }
    QTextStream inx(&x);
    QString textx = inx.readAll();
    ui->plainTextEdit->setPlainText(textx);
    x.close();
}

/*Compress*/
void MainWindow::on_pushButton_3_clicked()
{
    int sizeOriginal = 0;
    QFile myFile(currentFile);
    if (myFile.open(QIODevice::ReadOnly)){
        sizeOriginal = myFile.size();  //when file does open.
        myFile.close();
    }
    if(fixFlag != 1)
    {
        PrintCompressedTree(XML_ReadFile, NumOfLines);
    }
    else
    {
        PrintCompressedTree(XML_FixedErrors, NumOfLines);
    }
    int sizeCompressed = 0;
    QFile myFileComp("encodedFile.huff");
    if (myFileComp.open(QIODevice::ReadOnly)){
        sizeCompressed = myFileComp.size();  //when file does open.
        myFileComp.close();
    }
    QString namef = "encodedFile.huff";
    QMessageBox::information(this, "Compression Info" ,"Original File Size: "+QString::number(sizeOriginal)+" Byte\n"+
                             "Compressed File Size: "+QString::number(sizeCompressed)+" Byte\n"+
                             "Compressed File Name: "+namef);
}

