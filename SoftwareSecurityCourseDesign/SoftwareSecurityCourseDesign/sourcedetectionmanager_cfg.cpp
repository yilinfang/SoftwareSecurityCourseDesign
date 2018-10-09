#include "sourcedetectionmanager_cfg.h"

sourcedetectionmanager_cfg::sourcedetectionmanager_cfg()
{
    scriptsPath = QCoreApplication::applicationDirPath() + "/scripts/";
    qDebug() << scriptsPath;
    bufferPath = QCoreApplication::applicationDirPath() + "/buffer/";
}

int sourcedetectionmanager_cfg::LoadCode(QString input)
{
    if(input.isEmpty())
    {
        return 0;
    }
    fileName.clear();
    fileName.append(input);
    qDebug() << qPrintable(fileName);
    return 1;
}

int sourcedetectionmanager_cfg::LoadLibs(QStringList input)
{
    if(input.isEmpty())
    {
        return 0;
    }
    fileNames.clear();
    QList<QString>::iterator iter = input.begin();
    for(;iter!=input.end();iter++)
    {
        fileNames.append(*iter);
    }
    return 1;
}

int sourcedetectionmanager_cfg::Compare(QString &outputBufa)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
    QString cmd = QCoreApplication::applicationDirPath() + "/cflow -T " + fileName + " -o " + bufferPath + "sdm_cfg_s_" + currentDate + ".txt";
    qDebug() << cmd;
    system(cmd.toLocal8Bit().data());
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    QFile f(bufferPath + "sdm_cfg_s_" + currentDate + ".txt");
    f.open(QIODevice::ReadOnly);
    QString str = codec->toUnicode(f.readAll());
    outputBufa.clear();
    outputBufa.append(fileName + "(CFG):\n");
    outputBufa.append(str);
    f.close();
    QList<QString>::iterator iter;
    outputBufa.append("比对结果:\n");
    for(iter = fileNames.begin(); iter != fileNames.end(); iter++)
    {
        cmd = "python " + scriptsPath + "cfg.py " + (*iter) + " " + \
                fileName + " " + \
                bufferPath + "a_" + currentDate +".txt";
        qDebug() << cmd;
        system(cmd.toLocal8Bit().data());
        QFile f1(bufferPath + "a_" + currentDate +".txt");
        f1.open(QIODevice::ReadOnly);
        str.clear();
        str = "相对于" + *(iter) + codec->toUnicode(f1.readAll());
        qDebug() << str;
        outputBufa.append(str);
        f1.close();
    }
    return 0;
}
