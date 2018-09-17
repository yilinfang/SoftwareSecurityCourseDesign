#include "sourcedetectionmanager_string.h"

SourceDetectionManager_string::SourceDetectionManager_string()
{

}

int SourceDetectionManager_string::Modify(QString input, QString &output)
{
    int len = input.length();
    for(int i = 0;i < len;i++)
    {
        if(input[i] == ' ' || input[i] == '\n' || input[i] == '\t'|| input[i] == '\r' )
        {
            continue;
        }
        output.append(input[i]);
    }
    return 1;
}

int SourceDetectionManager_string::File2String(QString filePath, QString &string,QString &outputBufa)
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
    return 1;
}
