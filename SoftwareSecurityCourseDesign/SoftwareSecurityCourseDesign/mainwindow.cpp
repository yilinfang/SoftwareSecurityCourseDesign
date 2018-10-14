#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mutex = new QMutex();
    ui->statusBar->showMessage("使用本软件前请先仔细阅读关于标签下的所有内容!");
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
    this->ui->textBrowser_tab1->setText(outputBufa);
    this->ui->statusBar->showMessage("基于Token的代码同源性检测完成!");
}

void MainWindow::on_pushButton_sourceDetect_cfg_clicked()
{
    sdm_cfg.Compare(outputBufa);
    this->ui->textBrowser_tab1->setText(outputBufa);
    this->ui->statusBar->showMessage("基于CFG的代码同源性检测完成!");
}

void MainWindow::on_pushButton_getDirpath_tab2_clicked()
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
    MyThread* thread1 = new MyThread();
    MyThread* thread2 = new MyThread();
    MyThread* thread3 = new MyThread();
    QString output1, output2;
    output1.clear();
    output2.clear();
    QString bufferPath = QCoreApplication::applicationDirPath() + "/buffer/";
    QString currentDate = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
    thread1->mode = "1";
    thread1->outputPath = bufferPath + "out_1_" + currentDate +".txt";
    thread1->fileNames = stringList;
    thread1->output = &output1;
    thread1->mutex = mutex;
    thread1->start();
    thread2->mode = "2";
    thread2->outputPath = bufferPath + "out_2_" + currentDate +".txt";
    thread2->fileNames = stringList;
    thread2->mutex = mutex;
    thread2->output = &output1;
    thread2->start();
    thread3->mode = "3";
    thread3->outputPath = bufferPath + "out_3_" + currentDate +".txt";
    thread3->fileNames = stringList;
    thread3->output = &output1;
    thread3->mutex = mutex;
    thread3->start();
    while(thread1->isRunning() || thread2->isRunning() || thread3->isRunning())
    {
        mutex->lock();
        ui->statusBar->showMessage(output1);
        qApp->processEvents();
        mutex->unlock();
    }
    QFile f1(bufferPath + "out_1_" + currentDate +".txt");
    f1.open(QIODevice::ReadOnly);
    QFile f2(bufferPath + "out_2_" + currentDate +".txt");
    f2.open(QIODevice::ReadOnly);
    QFile f3(bufferPath + "out_3_" + currentDate +".txt");
    f3.open(QIODevice::ReadOnly);
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    output2.append("整数宽度溢出:\n");
    output2.append(codec->toUnicode(f1.readAll()));
    output2.append("--------------------------------------------------------------------------------\n");
    output2.append("整数符号溢出:\n");
    output2.append(codec->toUnicode(f2.readAll()));
    output2.append("--------------------------------------------------------------------------------\n");
    output2.append("缓冲区溢出:\n");
    output2.append(codec->toUnicode(f3.readAll()));
    //ui->textBrowser_tab1->setText(output2);
    ui->textBrowser1_tab2->setText(output2);
    f1.close();
    f2.close();
    f3.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString bufferPath = QCoreApplication::applicationDirPath() + "/buffer/";
    QDir dir(bufferPath);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())
    {
        return;
    }
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0)
    {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--)
        {
            curFile=fileList[i];
            if(curFile.isFile())
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0)
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else
                {
                    for(int j=0;j<fileList1.size();j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    ui->statusBar->showMessage("缓冲区清理完毕!");
}
