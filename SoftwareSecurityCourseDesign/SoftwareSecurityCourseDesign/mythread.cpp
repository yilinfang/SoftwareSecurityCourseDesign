#include "mythread.h"

MyThread::MyThread()
{

}

void MyThread::run()
{
    int n = fileNames.length();
    if(n <= 0)
    {
        return;
    }
    int i = 0;
    QList<QString>::iterator iter = fileNames.begin();
    QString cmd;
    for(;iter != fileNames.end(); iter++)
    {
        QString m;
        m.clear();
        if(mode == "1")
        {
            m.append("整数宽度溢出");
        }
        if(mode == "2")
        {
            m.append("整数符号溢出");
        }
        if(mode == "3")
        {
            m.append("缓冲区溢出");
        }
        cmd.clear();
        QString scriptsPath = QCoreApplication::applicationDirPath() + "/scripts/bugfinder.py";
        cmd = "python " + scriptsPath + " " + *(iter)  + " "\
                + outputPath + " " + mode;
        qDebug() << cmd;
        system(cmd.toLocal8Bit().data());
        mutex->lock();
        output->clear();
        output->append("("+ m + "分析进程" +")" + *(iter) + "分析完成(" + QString::number(++i) + "," + QString::number(n) + ")\n");
        mutex->unlock();
    }
}
