#include "sourcedetectionmanager_string.h"

SourceDetectionManager_string::SourceDetectionManager_string()
{
    scriptsPath = QCoreApplication::applicationDirPath() + "/scripts/";
    qDebug() << scriptsPath;
    bufferPath = QCoreApplication::applicationDirPath() + "/buffer/";
}

SourceDetectionManager_string::~SourceDetectionManager_string()
{
}

int SourceDetectionManager_string::LoadCode(QString input)
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

int SourceDetectionManager_string::LoadLibs(QStringList input)
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

int SourceDetectionManager_string::File2String(QString filePath, QString &string, QString &outputBufa)
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

int SourceDetectionManager_string::Dir2Stringlist(QString dirPath, QStringList &stringList, QString &outputBufa)
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
        qDebug() << filePath;
        stringList.append(filePath);
    }
    outputBufa = "打开文件夹成功!";
    return 1;
}

int SourceDetectionManager_string::Compare(QString &outputBufa)
{
     QString currentDate = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
     QString cmd;
     outputBufa.clear();
     QTextCodec *codec = QTextCodec::codecForName("GBK");
     QList<QString>::iterator iter;
     QString str;
     for(iter = fileNames.begin(); iter != fileNames.end(); iter++)
     {
         cmd = "python " + scriptsPath + "similarity.py " + (*iter) + " " + \
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
         qApp->processEvents();
     }
     return 0;
}

