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
    QString bufa1,bufa2,bufa3;
    bufa1.clear();
    bufa2.clear();
    bufa3.clear();
    QString dir = QFileDialog::getOpenFileName(this,tr("Open Directory"),"/home","*.*");
    qDebug() << dir;
    File2String(dir,bufa2,bufa3);
    qDebug() << qPrintable(bufa3);
    sdm_s.LoadCode(bufa2);
}

void MainWindow::on_pushButton_getFilePath_tab1_clicked()
{
    QString dirName;
    dirName.clear();
    dirName = QFileDialog::getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug() << dirName;
    QString bufa;
    QStringList stringList;
    Dir2Stringlist(dirName,stringList,bufa);
    qDebug() << bufa;
    sdm_s.LoadLibs(stringList);
}

int MainWindow::File2String(QString filePath, QString &string, QString &outputBufa)
{
    {
        QFile qfile(filePath);
        if(!qfile.open(QIODevice::ReadOnly))
        {
            outputBufa = "文件打开失败!";
            qfile.close();
            return 0;
        }
        QTextStream stream(&qfile);
        string = stream.readAll();
        outputBufa = "读取文件成功!";
        qfile.close();
        return 1;
    }
}

int MainWindow::Dir2Stringlist(QString dirPath, QStringList &stringList, QString &outputBufa)
{
    QDir qDir(dirPath);
    if(!qDir.exists())
    {
        stringList.clear();
        outputBufa = "文件夹打开失败!";
        return 0;
    }
    QStringList filters;
    filters << QString("*.*");
    qDir.setFilter(QDir::Files | QDir::NoSymLinks);
    qDir.setNameFilters(filters);
    if(qDir.count() <= 0)
    {
        stringList.clear();
        outputBufa = "文件夹为空!";
        return 0;
    }
    qDebug() << qDir.count();
    stringList.clear();
    for(unsigned i = 0; i < qDir.count(); i++)
    {
        QString filePath;
        filePath.clear();
        filePath.append(dirPath);
        filePath.append("/");
        filePath.append(qDir[i]);
        outputBufa = "打开文件成功!";
        QString file,bufa;
        File2String(filePath,file,bufa);
        stringList.append(file);
    }
    return 1;
}
