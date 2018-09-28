#ifndef SOURCEDETECTIONMANAGER_STRING_H
#define SOURCEDETECTIONMANAGER_STRING_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>

class SourceDetectionManager_string
{
public:
    SourceDetectionManager_string();
    ~SourceDetectionManager_string();
    int LoadCode(QString input);
    int LoadLibs(QStringList input);
    static int File2String(QString filePath, QString &string,QString &outputBufa);
    static int Dir2Stringlist(QString dirPath,QStringList &stringList, QString &outputBufa);
private:
    QString code;
    QString libs;
    int Modify(QString &input);
    int RemoveComments(QString &input);
    int RemoveComments(int _state, QChar c);
};

#endif // SOURCEDETECTIONMANAGER_STRING_H
