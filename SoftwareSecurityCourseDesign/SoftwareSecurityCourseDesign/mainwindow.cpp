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
    QString dir = QFileDialog::getOpenFileName(this,tr("Open Directory"),"/home","*.*");
    qDebug() << dir;
    if(SourceDetectionManager_string::File2String(dir,bufa1,bufa2))
    {
        ui->label_filePath_tab1->setText(qPrintable(dir));
    }
    ui->statusBar->showMessage(bufa2);
    sdm_s.LoadCode(bufa1);
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
}

