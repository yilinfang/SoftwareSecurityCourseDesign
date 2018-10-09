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
     QString cmd = "python " + scriptsPath + "modifier.py " + fileName + " " + \
             bufferPath + "sdm_s_m_" + currentDate +".txt";
     system(cmd.toLocal8Bit().data());
     cmd = "python " + scriptsPath + "tokenlaize.py " + bufferPath + "sdm_s_m_" + currentDate +".txt" + " " + \
             bufferPath + "sdm_s_t_" + currentDate +".txt";
     system(cmd.toLocal8Bit().data());
     QList<QString>::iterator iter;
     outputBufa.clear();
     QTextCodec *codec = QTextCodec::codecForName("GBK");
     for(iter = fileNames.begin(); iter != fileNames.end(); iter++)
     {
         cmd = "python " + scriptsPath + "modifier.py " + (*iter) + " " + \
                 bufferPath + "m_b_" + "" + currentDate +".txt";
         system(cmd.toLocal8Bit().data());
         cmd = "python " + scriptsPath + "tokenlaize.py " + \
                 bufferPath + "m_b_" + "" + currentDate +".txt" + " " + \
                 bufferPath + "t_b_" + "" + currentDate +".txt";
         system(cmd.toLocal8Bit().data());
         cmd = "python " + scriptsPath + "similarity_check_str.py " + \
                 bufferPath + "sdm_s_t_" + currentDate +".txt"+ " " + \
                 bufferPath + "t_b_" + currentDate +".txt" + " " + \
                 bufferPath + "a_b_" + currentDate +".txt";
         system(cmd.toLocal8Bit().data());
         QFile f(bufferPath + "a_b_" + "" + currentDate +".txt");
         f.open(QIODevice::ReadOnly);
         QString str = "相对于" + *(iter)  + codec->toUnicode(f.readAll());
         qDebug() << str;
         outputBufa.append(str);
         f.close();
     }
     cmd = "python " + scriptsPath + "bugfinder.py " + \
             scriptsPath + "helloworld.cpp"+ " " + \
             scriptsPath + "out.txt" + " " + \
             "2";
     system(cmd.toLocal8Bit().data());
     return 0;
}

