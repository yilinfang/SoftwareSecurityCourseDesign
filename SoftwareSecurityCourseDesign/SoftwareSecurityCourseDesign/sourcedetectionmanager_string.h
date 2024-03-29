#ifndef SOURCEDETECTIONMANAGER_STRING_H
#define SOURCEDETECTIONMANAGER_STRING_H
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

class SourceDetectionManager_string
{
public:
    SourceDetectionManager_string();
    ~SourceDetectionManager_string();
    int LoadCode(QString input);
    int LoadLibs(QStringList input);
    static int File2String(QString filePath, QString &string,QString &outputBufa);
    static int Dir2Stringlist(QString dirPath,QStringList &stringList, QString &outputBufa);
    int Compare(QString &outputBufa);
private:
    QString fileName;
    QString scriptsPath;
    QString bufferPath;
    QStringList fileNames;
};

#endif // SOURCEDETECTIONMANAGER_STRING_H
