#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include <QTextCodec>
#include <QMutex>
#include <QMainWindow>
class MyThread : public QThread
{
public:
    MyThread();
    QString outputPath;
    QString bufferPath;
    QStringList fileNames;
    QString mode;
    QString * output;
    QMutex* mutex;
    void run();
};

#endif // MYTHREAD_H
