#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sourcedetectionmanager_string.h"
#include "sourcedetectionmanager_cfg.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QTextCodec>
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
    void on_pushButton_sourceDetecter_string_clicked();
    void on_pushButton_sourceDetect_cfg_clicked();

private:
    Ui::MainWindow *ui;
    SourceDetectionManager_string sdm_s;
    sourcedetectionmanager_cfg sdm_cfg;
    QString outputBufa;
    QString bufferPath;
};

#endif // MAINWINDOW_H
