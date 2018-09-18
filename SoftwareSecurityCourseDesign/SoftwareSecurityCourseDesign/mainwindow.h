#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sourcedetectionmanager_string.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_getFilePath_tab1_clicked();

private:
    Ui::MainWindow *ui;
    SourceDetectionManager_string sdm_s;

    int File2String(QString filePath, QString &string,QString &outputBufa);
    int Dir2Stringlist(QString dirPath,QStringList &stringList, QString &outputBufa);
};

#endif // MAINWINDOW_H
