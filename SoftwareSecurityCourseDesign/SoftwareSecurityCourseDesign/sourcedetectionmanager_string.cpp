#include "sourcedetectionmanager_string.h"

SourceDetectionManager_string::SourceDetectionManager_string()
{

}

SourceDetectionManager_string::~SourceDetectionManager_string()
{

}

int SourceDetectionManager_string::Modify(QString &input)
{
    int len = input.length();
    if(len <= 0)
    {
        return 0;
    }
    QString output;
    output.clear();
    for(int i = 0;i < len;i++)
    {
        if(input[i] == ' ' || input[i] == '\n' || input[i] == '\t' || input[i] == '\r')
        {
            continue;
        }
        output.append(input[i]);
    }
    input.clear();
    input.append(output);
    return 1;
}

int SourceDetectionManager_string::RemoveComments(QString &input)
{
    QString output;
    output.clear();
    int len = input.length();
    int state = 0;
    for(int i = 0;i < len;i++)
    {
        QString bufa;
        bufa.clear();
        bufa.append(input[i]);
        if(input[i] == '\n')
        {
            break;
        }
    }
}

int SourceDetectionManager_string::RemoveComments(int  _state, QChar c)
{
    int state;
    switch (_state) {
    case 0:
        if(c == '/')
        {
            state = 1;
        }
        break;
    default:
        break;
    }
    return state;
}

int SourceDetectionManager_string::LoadCode(QString input)
{
    if(input.isEmpty())
    {
        return 0;
    }
    code.clear();
    code.append(input);
    qDebug() << qPrintable(code);
    return 1;
}

int SourceDetectionManager_string::LoadLibs(QStringList input)
{
    if(input.isEmpty())
    {
        return 0;
    }
    libs.clear();
    QList<QString>::iterator iter = input.begin();
    for(;iter!=input.end();iter++)
    {
        libs.append(*iter);
    }
    qDebug() << qPrintable(libs);
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
        outputBufa = "打开文件夹成功!";
        QString file,bufa;
        File2String(filePath,file,bufa);
        stringList.append(file);
    }
    return 1;
}

