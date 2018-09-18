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

int SourceDetectionManager_string::LoadCode(QString input)
{
    if(input.isEmpty())
    {
        return 0;
    }
    code.clear();
    code.append(input);
    Modify(code);
    qDebug() << code;
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
    Modify(libs);
    qDebug() << libs;
    return 1;
}

