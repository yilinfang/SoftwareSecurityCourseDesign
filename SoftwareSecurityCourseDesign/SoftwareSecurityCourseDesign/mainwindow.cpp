#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString bufa1,bufa2;
    bufa1.clear();
    bufa2.clear();
    QString dir = QFileDialog::getOpenFileName(this,tr("Open File"),"/home","*.*");
    qDebug() << dir;
    if(SourceDetectionManager_string::File2String(dir,bufa1,bufa2))
    {
        ui->label_filePath_tab1->setText(qPrintable(dir));
    }
    ui->statusBar->showMessage(bufa2);
    sdm_s.LoadCode(dir);
    sdm_cfg.LoadCode(dir);
}

void MainWindow::on_pushButton_getFilePath_tab1_clicked()
{
    QString dirName;
    dirName.clear();
    dirName = QFileDialog::getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug() << dirName;
    QString bufa;
    QStringList stringList;
    if(SourceDetectionManager_string::Dir2Stringlist(dirName,stringList,bufa))
    {
        ui->label_dirPath_tab1->setText(qPrintable(dirName));
    }
    ui->statusBar->showMessage(bufa);
    qDebug() << bufa;
    sdm_s.LoadLibs(stringList);
    sdm_cfg.LoadLibs(stringList);
}


void MainWindow::on_pushButton_sourceDetecter_string_clicked()
{
    sdm_s.Compare(outputBufa);
    //this->statusBar()->showMessage(outputBufa);
    this->ui->textBrowser_tab1->setText(outputBufa);
    this->ui->statusBar->showMessage("基于Token的代码同源性检测完成!");
}

void MainWindow::on_pushButton_sourceDetect_cfg_clicked()
{
    sdm_cfg.Compare(outputBufa);
    this->ui->textBrowser_tab1->setText(outputBufa);
    this->ui->statusBar->showMessage("基于CFG的代码同源性检测完成!");
}
