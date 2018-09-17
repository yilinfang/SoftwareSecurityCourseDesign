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
    QString filePath;
    filePath.clear();
    //filePath = QApplication::applicationDirPath() + '/';
    filePath = "/Users/leo/Desktop/SoftwareSecurityCourseDesign/SoftwareSecurityCourseDesign/build-SoftwareSecurityCourseDesign-Desktop_Qt_5_9_4_clang_64bit-Debug/";
    filePath += "helloworld.cpp";
    qDebug() << filePath;
    sdm_s.File2String(filePath,bufa1,bufa3);
    qDebug() << qPrintable(bufa3);
    sdm_s.Modify(bufa1,bufa2);
    qDebug() << qPrintable(bufa2);

}
